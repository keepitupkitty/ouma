use {
  crate::{c_int, dlmalloc, size_t, support::locale},
  core::ffi::c_void
};

pub const MB_LEN_MAX: c_int = 16;

#[no_mangle]
pub extern "C" fn __oumalibc_get_mb_cur_max() -> c_int {
  // TODO: implement get_locale()
  unsafe { locale::ThreadLocale.ctype.mb_cur_max }
}

#[no_mangle]
pub extern "C" fn ouma_calloc(
  n: size_t,
  l: size_t
) -> *mut c_void {
  unsafe { dlmalloc::dlcalloc(n, l) }
}

#[no_mangle]
pub extern "C" fn ouma_free(ptr: *mut c_void) {
  unsafe {
    dlmalloc::dlfree(ptr);
  }
}

#[no_mangle]
pub extern "C" fn ouma_malloc(n: size_t) -> *mut c_void {
  unsafe { dlmalloc::dlmalloc(n) }
}

#[no_mangle]
pub extern "C" fn ouma_posix_memalign(
  ptr: *mut *mut c_void,
  n: size_t,
  l: size_t
) -> c_int {
  unsafe { dlmalloc::dlposix_memalign(ptr, n, l) }
}

#[no_mangle]
pub extern "C" fn ouma_realloc(
  ptr: *mut c_void,
  n: size_t
) -> *mut c_void {
  unsafe { dlmalloc::dlrealloc(ptr, n) }
}
