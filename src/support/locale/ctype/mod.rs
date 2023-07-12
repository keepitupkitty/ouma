pub mod ascii;
pub mod utf8;

use {
  crate::{c_char, c_int, char32_t, mbstate_t, size_t, ssize_t},
  core::ptr
};

#[derive(Clone, Copy, Eq, PartialEq)]
#[repr(C)]
pub struct LocaleCtype {
  pub codeset: *const c_char,
  pub mbtoc32: Option<
    extern "C" fn(
      *mut char32_t,
      *const c_char,
      size_t,
      *mut mbstate_t
    ) -> ssize_t
  >,
  pub c32tomb:
    Option<extern "C" fn(*mut c_char, char32_t, *mut mbstate_t) -> ssize_t>,
  pub mb_cur_max: c_int
}

impl LocaleCtype {
  pub fn new() -> Self {
    Self {
      codeset: ptr::null::<c_char>(),
      mbtoc32: None,
      c32tomb: None,
      mb_cur_max: 0
    }
  }

  pub fn as_ptr(&mut self) -> *mut LocaleCtype {
    &mut *self
  }
}

struct CtypeList<'a> {
  pub name: &'a str,
  pub ctype: LocaleCtype
}

#[inline(always)]
pub fn lookup_ctype(name: &str) -> LocaleCtype {
  const AvailableCtypes: [CtypeList; 2] = [
    CtypeList { name: "US-ASCII", ctype: ascii::LOCALE_CTYPE_ASCII },
    CtypeList { name: "UTF-8", ctype: utf8::LOCALE_CTYPE_UTF8 }
  ];
  for i in 0..AvailableCtypes.len() {
    if name == AvailableCtypes[i].name {
      return AvailableCtypes[i].ctype;
    }
  }
  LocaleCtype::new()
}
