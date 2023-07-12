pub mod ctype;
pub mod numeric;
pub mod time;

use crate::{c_uint, char16_t, char32_t, locale_t, mbstate_t, LocaleStruct};

#[no_mangle]
pub static mut LOCALE_C: LocaleStruct =
  LocaleStruct { ctype: ctype::ascii::LOCALE_CTYPE_ASCII };

#[no_mangle]
pub static mut LOCALE_C_UTF8: LocaleStruct =
  LocaleStruct { ctype: ctype::utf8::LOCALE_CTYPE_UTF8 };

#[thread_local]
pub static mut ThreadLocale: LocaleStruct = unsafe { LOCALE_C };

#[inline(always)]
pub fn get_thread_locale() -> locale_t {
  unsafe { &mut ThreadLocale }
}

#[inline(always)]
pub fn set_thread_locale(locale: locale_t) {
  unsafe { ThreadLocale = *locale };
}

#[inline(always)]
pub fn mbstate_set_init(mbs: *mut mbstate_t) {
  if !mbs.is_null() {
    unsafe {
      *mbs = mbstate_t::new();
    }
  }
}

#[inline(always)]
pub fn mbstate_get_init(mbs: *const mbstate_t) -> bool {
  return unsafe {
    mbs.is_null() ||
      ((*mbs).surrogate < 0xd800 || (*mbs).surrogate > 0xdfff) &&
        (*mbs).bytesleft == 0
  };
}

#[inline(always)]
pub fn mbstate_set_multibyte(
  mbs: *mut mbstate_t,
  bytesleft: c_uint,
  partial: char32_t,
  lowerbound: char32_t
) {
  unsafe {
    (*mbs).bytesleft = bytesleft;
    (*mbs).partial = partial;
    (*mbs).lowerbound = lowerbound;
  }
}

#[inline(always)]
pub fn mbstate_get_multibyte(
  mbs: *const mbstate_t,
  bytesleft: *mut c_uint,
  partial: *mut char32_t,
  lowerbound: *mut char32_t
) {
  unsafe {
    *bytesleft = (*mbs).bytesleft;
    *partial = (*mbs).partial;
    *lowerbound = (*mbs).lowerbound;
  }
}

#[inline(always)]
pub fn mbstate_set_surrogate(
  mbs: *mut mbstate_t,
  surrogate: char16_t
) {
  assert_eq!(surrogate >= 0xd800 && surrogate <= 0xdfff, true);
  unsafe { (*mbs).surrogate = surrogate };
}

#[inline(always)]
pub fn mbstate_get_surrogate(
  mbs: *const mbstate_t,
  surrogate: *mut char16_t
) -> bool {
  unsafe {
    if (*mbs).surrogate < 0xd800 || (*mbs).surrogate > 0xdfff {
      return false;
    }
    *surrogate = (*mbs).surrogate;
  }
  return true;
}
