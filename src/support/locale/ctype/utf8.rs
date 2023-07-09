use crate::{
  c_char,
  c_int,
  c_uchar,
  c_uint,
  char32_t,
  mbstate_t,
  size_t,
  ssize_t,
  std::errno,
  support::locale
};

extern "C" fn c32tomb(
  s: *mut c_char,
  wc: char32_t,
  _: *mut mbstate_t
) -> ssize_t {
  let head: u8;
  let len: c_int;
  let mut c = wc;
  let us: *mut u8 = s as *mut u8;

  if c <= 0x7f {
    unsafe { *us = wc as u8 };
    return 1;
  } else if c <= 0x7ff {
    head = 0xc0;
    len = 2;
  } else if c <= 0xffff {
    if c >= 0xd800 && c <= 0xdfff {
      errno::set_errno(errno::EILSEQ);
      return -1;
    }
    head = 0xe0;
    len = 3;
  } else if c <= 0x10ffff {
    head = 0xf0;
    len = 4;
  } else {
    errno::set_errno(errno::EILSEQ);
    return -1;
  }

  let mut k = len - 1;
  while k > 0 {
    unsafe { *us.offset(k as isize) = (c as u8 & 0x3f) | 0x80 };
    c >>= 6;
    k -= 1;
  }

  unsafe { *us = (c as u8 & 0xff) | head };
  len as isize
}

extern "C" fn mbtoc32(
  pc32: *mut char32_t,
  s: *const c_char,
  n: size_t,
  ps: *mut mbstate_t
) -> ssize_t {
  static mut PRIV: mbstate_t = mbstate_t::new();
  let state = if !ps.is_null() {
    unsafe { &mut *ps }
  } else {
    // TODO: mutex lock
    unsafe { &mut PRIV }
  };
  let mut sb: *const c_uchar = s as *const c_uchar;
  let mut i = n;
  if i < 1 {
    return -2;
  }

  let mut bytesleft: c_uint = 0;
  let mut partial: char32_t = 0;
  let mut lowerbound: char32_t = 0;
  locale::mbstate_get_multibyte(
    state,
    &mut bytesleft,
    &mut partial,
    &mut lowerbound
  );

  if bytesleft == 0 {
    unsafe {
      if (*sb & 0x80) == 0 {
        *pc32 = *sb as char32_t;
        locale::mbstate_set_init(state);
        return 1;
      } else if (*sb & 0xe0) == 0xc0 {
        bytesleft = 1;
        let s1 = sb;
        sb = sb.wrapping_offset(1);
        partial = *s1 as char32_t & 0x1f;
        lowerbound = 0x80;
      } else if (*sb & 0xf0) == 0xe0 {
        bytesleft = 2;
        let s1 = sb;
        sb = sb.wrapping_offset(1);
        partial = *s1 as char32_t & 0xf;
        lowerbound = 0x800;
      } else if (*sb & 0xf8) == 0xf0 {
        bytesleft = 3;
        let s1 = sb;
        sb = sb.wrapping_offset(1);
        partial = *s1 as char32_t & 0x7;
        lowerbound = 0x10000;
      } else {
        errno::set_errno(errno::EILSEQ);
        return -1;
      }
    }
    i = i.wrapping_sub(1);
  }

  while i > 0 {
    unsafe {
      if (*sb & 0xc0) != 0x80 {
        errno::set_errno(errno::EILSEQ);
        return -1;
      }
    }

    let s1 = sb;
    sb = sb.wrapping_offset(1);
    partial <<= 6;
    partial |= unsafe { *s1 as char32_t & 0x3f };

    bytesleft = bytesleft.wrapping_sub(1);
    if bytesleft == 0 {
      if partial < lowerbound ||
        (partial >= 0xd800 && partial <= 0xdfff) ||
        partial > 0x10ffff
      {
        errno::set_errno(errno::EILSEQ);
        return -1;
      }
      unsafe {
        *pc32 = partial;
      }
      locale::mbstate_set_init(state);
      return unsafe { sb.offset_from(s as *const c_uchar) };
    }

    i = i.wrapping_sub(1);
  }
  locale::mbstate_set_multibyte(state, bytesleft, partial, lowerbound);
  -2
}

pub const LOCALE_CTYPE_UTF8: locale::ctype::LocaleCtype =
  locale::ctype::LocaleCtype {
    copied: "true".as_ptr() as *const c_char,
    codeset: "UTF-8".as_ptr() as *const c_char,
    mbtoc32: Some(mbtoc32),
    c32tomb: Some(c32tomb),
    mb_cur_max: 4
  };
