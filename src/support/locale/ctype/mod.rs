pub mod ascii;
pub mod utf8;

use crate::{c_char, c_int, char32_t, mbstate_t, size_t, ssize_t};

#[derive(Clone, Copy)]
#[repr(C)]
pub struct LocaleCtype {
  pub mbtoc32: extern "C" fn(
    *mut char32_t,
    *const c_char,
    size_t,
    *mut mbstate_t
  ) -> ssize_t,
  pub c32tomb: extern "C" fn(*mut c_char, char32_t, *mut mbstate_t) -> ssize_t,
  pub mb_cur_max: c_int
}
