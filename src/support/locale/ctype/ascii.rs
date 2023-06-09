use crate::{
  c_char,
  c_schar,
  c_uchar,
  mbstate_t,
  size_t,
  ssize_t,
  std::errno,
  support::locale,
  wchar_t
};

extern "C" fn mbrtowc(
  pwc: *mut wchar_t,
  s: *const c_char,
  n: size_t,
  ps: *mut mbstate_t
) -> ssize_t {
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
  let uc: c_uchar = unsafe { *s as c_uchar };
  if uc > c_schar::max_value() as u8 {
    errno::set_errno(errno::EILSEQ);
    return -1;
  }
  unsafe { *pwc = uc as wchar_t };
  locale::mbstate_set_init(state);
  1
}

extern "C" fn wcrtomb(
  s: *mut c_char,
  wc: wchar_t,
  _: *mut mbstate_t
) -> ssize_t {
  if wc > c_schar::max_value() as wchar_t {
    errno::set_errno(errno::EILSEQ);
    return -1;
  }
  unsafe { *s = wc as c_char };
  1
}

pub const LOCALE_CTYPE_ASCII: locale::ctype::LocaleCtype =
  locale::ctype::LocaleCtype {
    mbrtowc: mbrtowc,
    wcrtomb: wcrtomb,
    mb_cur_max: 1
  };
