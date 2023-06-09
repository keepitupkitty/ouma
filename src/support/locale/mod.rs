pub mod ctype;
pub mod numeric;
pub mod time;

use crate::{locale_t, mbstate_t, LocaleStruct};

#[thread_local]
pub static mut ThreadLocale: locale_t = LOCALE_C_UTF8;

pub const LOCALE_C: locale_t =
  LocaleStruct { ctype: ctype::ascii::LOCALE_CTYPE_ASCII };

pub const LOCALE_C_UTF8: locale_t =
  LocaleStruct { ctype: ctype::utf8::LOCALE_CTYPE_UTF8 };

#[inline(always)]
pub fn mbstate_set_init(ps: *mut mbstate_t) {
  unsafe {
    (*ps).surrogate = 0;
    (*ps).seq = [0; 4];
  }
}
