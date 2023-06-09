use crate::{
  c_char,
  char16_t,
  char32_t,
  mbstate_t,
  size_t,
  std::{errno, stdlib},
  support::locale,
  wchar_t
};

#[no_mangle]
pub extern "C" fn ouma_c16rtomb(
  s: *mut c_char,
  c16: char16_t,
  ps: *mut mbstate_t
) -> size_t {
  let mut buf: [c_char; stdlib::MB_LEN_MAX as usize] =
    [0; stdlib::MB_LEN_MAX as usize];
  let (s, c16) = if s.is_null() { (buf.as_mut_ptr(), 0) } else { (s, c16) };

  let wc: wchar_t;
  unsafe {
    if (*ps).surrogate >= 0xd800 && (*ps).surrogate <= 0xdbff {
      if c16 < 0xdc00 || c16 > 0xdfff {
        errno::set_errno(errno::EILSEQ);
        return -1isize as usize;
      }
      wc =
        0x10000 + (((*ps).surrogate & 0x3ff) << 10 | (c16 & 0x3ff)) as wchar_t;
    } else if c16 >= 0xd800 && c16 <= 0xdbff {
      (*ps).surrogate = c16;
      return 0;
    } else {
      wc = c16 as wchar_t;
    }
  }

  let l = unsafe { (locale::ThreadLocale.ctype.wcrtomb)(s, wc, ps) };
  if l >= 0 {
    locale::mbstate_set_init(ps);
  }
  l as size_t
}

#[no_mangle]
pub extern "C" fn ouma_c32rtomb(
  s: *mut c_char,
  c32: char32_t,
  ps: *mut mbstate_t
) -> size_t {
  let mut buf: [c_char; stdlib::MB_LEN_MAX as usize] =
    [0; stdlib::MB_LEN_MAX as usize];
  let (s, c32) = if s.is_null() { (buf.as_mut_ptr(), 0) } else { (s, c32) };
  let l =
    unsafe { (locale::ThreadLocale.ctype.wcrtomb)(s, c32 as wchar_t, ps) };
  l as size_t
}

#[no_mangle]
pub extern "C" fn ouma_mbrtoc16(
  pc16: *mut char16_t,
  s: *const c_char,
  n: size_t,
  ps: *mut mbstate_t
) -> size_t {
  static mut PRIVATE: mbstate_t = mbstate_t { seq: [0; 4], surrogate: 0 };
  let state = if !ps.is_null() {
    unsafe { &mut *ps }
  } else {
    // TODO: use mutex locking
    unsafe { &mut PRIVATE }
  };

  let (pc16, s, n) = if s.is_null() {
    (pc16, b"\0" as *const u8 as *const c_char, 1)
  } else {
    (pc16, s, n)
  };

  if (*state).surrogate >= 0xdc00 && (*state).surrogate <= 0xdfff {
    unsafe { *pc16 = (*state).surrogate };
    locale::mbstate_set_init(state);
    return -3isize as usize;
  }
  if n == 0 {
    locale::mbstate_set_init(state);
    return -2isize as usize;
  }

  let mut wc: wchar_t = 0;
  let len = unsafe {
    (locale::ThreadLocale.ctype.mbrtowc)(&mut wc, s, n, state) as usize
  };
  if len > 0 {
    if wc < 0x10000 {
      unsafe { *pc16 = wc as char16_t };
    } else {
      wc -= 0x10000;
      unsafe { *pc16 = (0xd800 | wc >> 10) as char16_t };
      (*state).surrogate = 0xdc00 | (wc as char16_t & 0x3ff);
    }
  }
  len as usize
}

#[no_mangle]
pub extern "C" fn ouma_mbrtoc32(
  pc32: *mut char32_t,
  s: *const c_char,
  n: size_t,
  ps: *mut mbstate_t
) -> size_t {
  let (pc32, s, n) = if s.is_null() {
    (pc32, b"\0" as *const u8 as *const c_char, 1)
  } else {
    (pc32, s, n)
  };
  let l = unsafe {
    (locale::ThreadLocale.ctype.mbrtowc)(pc32 as *mut wchar_t, s, n, ps)
  };
  unsafe {
    if l >= 0 && *pc32 == '\0' as char32_t {
      return 0;
    }
  }
  l as size_t
}
