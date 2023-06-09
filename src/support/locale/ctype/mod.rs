pub mod ascii;
pub mod utf8;

use crate::{c_char, c_int, mbstate_t, size_t, ssize_t, wchar_t};

#[derive(Clone, Copy)]
#[repr(C)]
pub struct LocaleCtype {
  pub mbrtowc: extern "C" fn(
    *mut wchar_t,
    *const c_char,
    size_t,
    *mut mbstate_t
  ) -> ssize_t,
  pub wcrtomb: extern "C" fn(*mut c_char, wchar_t, *mut mbstate_t) -> ssize_t,
  pub mb_cur_max: c_int
}
