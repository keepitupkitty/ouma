use crate::{
  c_char,
  c_int,
  c_uchar,
  char32_t,
  locale_t,
  mbstate_t,
  std::wctype,
  support::locale,
  wctrans_t,
  wctype_t,
  wint_t
};

#[inline(always)]
fn isctype_l(
  c: c_int,
  wctype: wctype_t,
  locale: locale_t
) -> c_int {
  if c < 0 || c > c_uchar::max_value() as c_int {
    return 0;
  }

  let (loc, mut buf, mut c32, mut ps) =
    (unsafe { *locale }, c as c_char, 0 as char32_t, mbstate_t::new());

  locale::mbstate_set_init(&mut ps);
  if (loc.ctype.mbtoc32).unwrap()(&mut c32, &mut buf, 1, &mut ps) != 1 {
    return 0;
  }
  wctype::ouma_iswctype_l(c32 as wint_t, wctype, locale)
}

#[inline(always)]
fn totrans_l(
  c: c_int,
  wctrans: wctrans_t,
  locale: locale_t
) -> c_int {
  if c < 0 || c > c_uchar::max_value() as c_int {
    return c;
  }

  let (loc, mut buf, mut c32, mut ps) =
    (unsafe { *locale }, c as c_char, 0 as char32_t, mbstate_t::new());

  locale::mbstate_set_init(&mut ps);
  if (loc.ctype.mbtoc32).unwrap()(&mut c32, &mut buf, 1, &mut ps) != 1 {
    return c as c_int;
  }
  wctype::ouma_towctrans_l(c32 as wint_t, wctrans, locale) as c_int
}

#[no_mangle]
pub extern "C" fn ouma_isalnum(c: c_int) -> c_int {
  ouma_isalnum_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isalnum_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_ALNUM, locale)
}

#[no_mangle]
pub extern "C" fn ouma_isalpha(c: c_int) -> c_int {
  ouma_isalpha_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isalpha_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_ALPHA, locale)
}

#[no_mangle]
pub extern "C" fn ouma_isascii(c: c_int) -> c_int {
  c_int::from(c >= 0 && c <= 127)
}

#[no_mangle]
pub extern "C" fn ouma_isblank(c: c_int) -> c_int {
  ouma_isblank_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isblank_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_BLANK, locale)
}

#[no_mangle]
pub extern "C" fn ouma_iscntrl(c: c_int) -> c_int {
  ouma_iscntrl_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_iscntrl_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_CNTRL, locale)
}

#[no_mangle]
pub extern "C" fn ouma_isdigit(c: c_int) -> c_int {
  ouma_isdigit_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isdigit_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_DIGIT, locale)
}

#[no_mangle]
pub extern "C" fn ouma_isgraph(c: c_int) -> c_int {
  ouma_isgraph_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isgraph_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_GRAPH, locale)
}

#[no_mangle]
pub extern "C" fn ouma_islower(c: c_int) -> c_int {
  ouma_islower_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_islower_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_LOWER, locale)
}

#[no_mangle]
pub extern "C" fn ouma_isprint(c: c_int) -> c_int {
  ouma_isprint_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isprint_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_PRINT, locale)
}

#[no_mangle]
pub extern "C" fn ouma_ispunct(c: c_int) -> c_int {
  ouma_ispunct_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_ispunct_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_PUNCT, locale)
}

#[no_mangle]
pub extern "C" fn ouma_isspace(c: c_int) -> c_int {
  ouma_isspace_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isspace_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_SPACE, locale)
}

#[no_mangle]
pub extern "C" fn ouma_isupper(c: c_int) -> c_int {
  ouma_isupper_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isupper_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_UPPER, locale)
}

#[no_mangle]
pub extern "C" fn ouma_isxdigit(c: c_int) -> c_int {
  ouma_isxdigit_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_isxdigit_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  isctype_l(c, wctype::WCTYPE_XDIGIT, locale)
}

#[no_mangle]
pub extern "C" fn ouma_toascii(c: c_int) -> c_int {
  c_int::(c & 0x7F)
}

#[no_mangle]
pub extern "C" fn ouma_tolower(c: c_int) -> c_int {
  ouma_tolower_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_tolower_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  totrans_l(c, wctype::WCTRANS_TOLOWER, locale)
}

#[no_mangle]
pub extern "C" fn ouma_toupper(c: c_int) -> c_int {
  ouma_toupper_l(c, locale::get_thread_locale())
}

#[no_mangle]
pub extern "C" fn ouma_toupper_l(
  c: c_int,
  locale: locale_t
) -> c_int {
  totrans_l(c, wctype::WCTRANS_TOUPPER, locale)
}
