use crate::{c_int, support::locale};

pub const MB_LEN_MAX: c_int = 16;

#[no_mangle]
pub extern "C" fn __oumalibc_get_mb_cur_max() -> c_int {
  unsafe { locale::ThreadLocale.ctype.mb_cur_max }
}
