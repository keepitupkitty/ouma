use crate::{
  c_char,
  c_schar,
  c_uchar,
  char32_t,
  mbstate_t,
  size_t,
  ssize_t,
  std::errno,
  support::locale
};

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
  if n < 1 {
    return -2;
  }
  let uc: c_uchar = unsafe { *s as c_uchar };
  if uc > c_schar::max_value() as u8 {
    errno::set_errno(errno::EILSEQ);
    return -1;
  }
  unsafe { *pc32 = uc as char32_t };
  locale::mbstate_set_init(state);
  1
}

extern "C" fn c32tomb(
  s: *mut c_char,
  wc: char32_t,
  _: *mut mbstate_t
) -> ssize_t {
  if wc > c_schar::max_value() as char32_t {
    errno::set_errno(errno::EILSEQ);
    return -1;
  }
  unsafe { *s = wc as c_char };
  1
}

pub const LOCALE_CTYPE_ASCII: locale::ctype::LocaleCtype =
  locale::ctype::LocaleCtype {
    copied: "true".as_ptr() as *const c_char,
    codeset: "US-ASCII".as_ptr() as *const c_char,
    mbtoc32: Some(mbtoc32),
    c32tomb: Some(c32tomb),
    mb_cur_max: 1
  };
