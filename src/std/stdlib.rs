use crate::{c_int, support::locale};

pub const MB_LEN_MAX: c_int = 16;

#[no_mangle]
pub extern "C" fn __oumalibc_get_mb_cur_max() -> c_int {
  let loc = unsafe { *locale::get_thread_locale() };
  loc.ctype.mb_cur_max
}
