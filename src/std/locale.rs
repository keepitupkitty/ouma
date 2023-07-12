use {
  crate::{
    c_char,
    c_int,
    locale_t,
    std::{errno, string},
    support::locale,
    LocaleStruct
  },
  core::{ffi, ptr}
};

pub const LC_CTYPE: c_int = 0;
pub const LC_NUMERIC: c_int = 1;
pub const LC_TIME: c_int = 2;
pub const LC_COLLATE: c_int = 3;
pub const LC_MONETARY: c_int = 4;
pub const LC_MESSAGES: c_int = 5;
pub const LC_ALL: c_int = 6;
pub const LC_PAPER: c_int = 7;
pub const LC_NAME: c_int = 8;
pub const LC_ADDRESS: c_int = 9;
pub const LC_TELEPHONE: c_int = 10;
pub const LC_MEASUREMENT: c_int = 11;
pub const LC_IDENTIFICATION: c_int = 12;

pub const LC_CTYPE_MASK: c_int = 1 << LC_CTYPE;
pub const LC_NUMERIC_MASK: c_int = 1 << LC_NUMERIC;
pub const LC_TIME_MASK: c_int = 1 << LC_TIME;
pub const LC_COLLATE_MASK: c_int = 1 << LC_COLLATE;
pub const LC_MONETARY_MASK: c_int = 1 << LC_MONETARY;
pub const LC_MESSAGES_MASK: c_int = 1 << LC_MESSAGES;
pub const LC_PAPER_MASK: c_int = 1 << LC_PAPER;
pub const LC_NAME_MASK: c_int = 1 << LC_NAME;
pub const LC_ADDRESS_MASK: c_int = 1 << LC_ADDRESS;
pub const LC_TELEPHONE_MASK: c_int = 1 << LC_TELEPHONE;
pub const LC_MEASUREMENT_MASK: c_int = 1 << LC_MEASUREMENT;
pub const LC_IDENTIFICATION_MASK: c_int = 1 << LC_IDENTIFICATION;

pub const LC_ALL_MASK: c_int = LC_CTYPE_MASK |
  LC_NUMERIC_MASK |
  LC_TIME_MASK |
  LC_COLLATE_MASK |
  LC_MONETARY_MASK |
  LC_MESSAGES_MASK |
  LC_PAPER_MASK |
  LC_NAME_MASK |
  LC_ADDRESS_MASK |
  LC_TELEPHONE_MASK |
  LC_MEASUREMENT_MASK |
  LC_IDENTIFICATION_MASK;

#[repr(C)]
pub struct lconv {
  decimal_point: *mut c_char,
  thousands_sep: *mut c_char,
  grouping: *mut c_char,
  int_curr_symbol: *mut c_char,
  currency_symbol: *mut c_char,
  mon_decimal_point: *mut c_char,
  mon_thousands_sep: *mut c_char,
  mon_grouping: *mut c_char,
  positive_sign: *mut c_char,
  negative_sign: *mut c_char,
  int_frac_digits: c_char,
  frac_digits: c_char,
  p_cs_precedes: c_char,
  p_sep_by_space: c_char,
  n_cs_precedes: c_char,
  n_sep_by_space: c_char,
  p_sign_posn: c_char,
  n_sign_posn: c_char,
  int_p_cs_precedes: c_char,
  int_p_sep_by_space: c_char,
  int_n_cs_precedes: c_char,
  int_n_sep_by_space: c_char,
  int_p_sign_posn: c_char,
  int_n_sign_posn: c_char
}

#[no_mangle]
pub extern "C" fn ouma_localeconv() -> *mut lconv {
  // TODO: export values from locale thread
  static mut lconv: lconv = lconv {
    decimal_point: ".".as_ptr() as *mut c_char,
    thousands_sep: "".as_ptr() as *mut c_char,
    grouping: "".as_ptr() as *mut c_char,
    int_curr_symbol: "".as_ptr() as *mut c_char,
    currency_symbol: "".as_ptr() as *mut c_char,
    mon_decimal_point: "".as_ptr() as *mut c_char,
    mon_thousands_sep: "".as_ptr() as *mut c_char,
    mon_grouping: "".as_ptr() as *mut c_char,
    positive_sign: "".as_ptr() as *mut c_char,
    negative_sign: "".as_ptr() as *mut c_char,
    int_frac_digits: c_char::max_value(),
    frac_digits: c_char::max_value(),
    p_cs_precedes: c_char::max_value(),
    p_sep_by_space: c_char::max_value(),
    n_cs_precedes: c_char::max_value(),
    n_sep_by_space: c_char::max_value(),
    p_sign_posn: c_char::max_value(),
    n_sign_posn: c_char::max_value(),
    int_p_cs_precedes: c_char::max_value(),
    int_p_sep_by_space: c_char::max_value(),
    int_n_cs_precedes: c_char::max_value(),
    int_n_sep_by_space: c_char::max_value(),
    int_p_sign_posn: c_char::max_value(),
    int_n_sign_posn: c_char::max_value()
  };
  unsafe { &mut lconv }
}

#[no_mangle]
pub extern "C" fn ouma_freelocale(_: locale_t) {
  // Nothing to do
}

#[no_mangle]
pub extern "C" fn ouma_duplocale(base: locale_t) -> locale_t {
  base
}

#[no_mangle]
pub extern "C" fn ouma_newlocale(
  mask: c_int,
  locale: *const c_char,
  base: locale_t
) -> locale_t {
  let loc = unsafe { ffi::CStr::from_ptr(locale).to_str().unwrap() };
  let mut rbase = base;
  let mut newlocale: LocaleStruct = LocaleStruct::new();

  if loc.is_empty() || loc == "C" || loc == "POSIX" || mask == 0 {
    errno::set_errno(errno::EINVAL);
    return -1isize as locale_t;
  } else {
    if (mask & !LC_ALL_MASK) != 0 {
      errno::set_errno(errno::EINVAL);
      return -1isize as locale_t;
    }
    // TODO: parse locales from environment
    //let mut parts = if getenv_locale().is_some() {
    //  getenv_locale().unwrap().split('.')
    //} else {
    //  loc.split('.')
    //};
    let mut parts = loc.split('.');
    if let Some(_lang) = parts.next() {
      // TODO: process languages
      // Return C locale if locale is not present in the list
    }
    if let Some(ctype) = parts.next() {
      newlocale.ctype = locale::ctype::lookup_ctype(ctype);
    }
  }

  if rbase.is_null() {
    unsafe { rbase = &mut locale::LOCALE_C };
  }

  let mut different = false;
  macro_rules! update_category {
    ($name:ident, $bit:expr) => {
      unsafe {
        if (mask & $bit) == 0 {
          newlocale.$name = (*rbase).$name;
        } else if newlocale.$name != (*rbase).$name {
          different = true;
          let $name = newlocale.$name.as_ptr();
          if !$name.is_null() {
            errno::set_errno(errno::ENOENT);
            return ptr::null_mut();
          }
        }
      }
    };
  }
  update_category!(ctype, LC_CTYPE_MASK);

  if !different {
    return rbase;
  }

  &mut newlocale
}

#[no_mangle]
pub extern "C" fn ouma_uselocale(new: locale_t) -> locale_t {
  let old = locale::get_thread_locale();
  if new.is_null() {
    errno::set_errno(errno::EINVAL);
    return -1isize as locale_t;
  }
  if new == -1isize as locale_t {
    return new;
  }
  locale::set_thread_locale(new);
  return if !old.is_null() { old } else { -1isize as locale_t };
}

#[no_mangle]
pub extern "C" fn ouma_setlocale(
  _mask: c_int,
  locale: *const c_char
) -> *mut c_char {
  unsafe {
    if locale.is_null() ||
      *locale == b'\0' as c_char ||
      string::ouma_strcmp(locale, "C".as_ptr() as _) == 0 ||
      string::ouma_strcmp(locale, "POSIX".as_ptr() as _) == 0
    {
      return "C".as_ptr() as *mut _;
    }
  }
  // TODO: scan environment for locale if available, create new locale
  // and patch it's value, if locale is not in the list then return null and
  // set errno to EINVAL
  ptr::null_mut()
}
