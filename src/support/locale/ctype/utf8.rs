use {
  crate::{
    c_char,
    c_int,
    mbstate_t,
    size_t,
    ssize_t,
    std::errno,
    support::locale,
    wchar_t
  },
  core::cmp
};

extern "C" fn wcrtomb(
  s: *mut c_char,
  wc: wchar_t,
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

extern "C" fn mbrtowc(
  pwc: *mut wchar_t,
  s: *const c_char,
  n: size_t,
  ps: *mut mbstate_t
) -> ssize_t {
  let mut s1 = s;
  static mut PRIVATE: mbstate_t = mbstate_t { seq: [0; 4], surrogate: 0 };
  let state = if !ps.is_null() {
    unsafe { &mut *ps }
  } else {
    // TODO: use mutex locking
    unsafe { &mut PRIVATE }
  };

  if n == 0 {
    return -2;
  }
  let mut ch: u8 = unsafe { *s1 as u8 };
  if (*state).seq == [0; 4] && (ch & !0x7f) == 0 {
    if !pwc.is_null() {
      unsafe { *pwc = ch as wchar_t };
    }
    if ch != 0 {
      return 1;
    } else {
      return 0;
    }
  }

  let length: usize;
  let mask;
  let lowerbound: wchar_t;
  let bytesleft: usize = if (*state).seq[2] != 0 {
    3
  } else if (*state).seq[1] != 0 {
    2
  } else if (*state).seq[0] != 0 {
    1
  } else {
    0
  };
  ch = if bytesleft > 0 { (*state).seq[0] } else { unsafe { *s1 as u8 } };
  if (ch & 0xe0) == 0xc0 {
    mask = 0x1f;
    length = 2;
    lowerbound = 0x80;
  } else if (ch & 0xf0) == 0xe0 {
    mask = 0x0f;
    length = 3;
    lowerbound = 0x800;
  } else if (ch & 0xf8) == 0xf0 {
    mask = 0x07;
    length = 4;
    lowerbound = 0x10000;
  } else {
    (*state).seq = [0; 4];
    errno::set_errno(errno::EILSEQ);
    return -1;
  }

  let byteswanted: usize = length - bytesleft;
  let mut i = 0;
  while i < cmp::min(byteswanted, n) {
    unsafe {
      if (*state).seq != [0; 4] && ((*s1 as u8 & 0xc0) != 0x80) {
        locale::mbstate_set_init(state);
        errno::set_errno(errno::EILSEQ);
        return -1;
      }
    }
    let s2 = s1;
    s1 = s1.wrapping_offset(1);
    unsafe { (*state).seq[bytesleft.wrapping_add(i)] = *s2 as u8 };

    i += 1;
  }
  if i < byteswanted {
    return -2;
  }

  let mut c32: wchar_t = ((*state).seq[0] & mask) as wchar_t;
  i = 1;
  while i < length {
    c32 <<= 6;
    c32 |= ((*state).seq[i] & 0x3f) as wchar_t;
    i += 1;
  }

  if c32 < lowerbound {
    locale::mbstate_set_init(state);
    errno::set_errno(errno::EILSEQ);
    return -1;
  }
  if (c32 >= 0xd800 && c32 <= 0xdfff) || (c32 > 0x10ffff) {
    locale::mbstate_set_init(state);
    errno::set_errno(errno::EILSEQ);
    return -1;
  }

  if !pwc.is_null() {
    unsafe { *pwc = c32 };
  }
  if c32 == 0 {
    locale::mbstate_set_init(state);
    return 0;
  } else {
    locale::mbstate_set_init(state);
    return byteswanted as isize;
  }
}

pub const LOCALE_CTYPE_UTF8: locale::ctype::LocaleCtype =
  locale::ctype::LocaleCtype {
    mbrtowc: mbrtowc,
    wcrtomb: wcrtomb,
    mb_cur_max: 4
  };
