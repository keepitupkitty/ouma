use core::ffi::c_void;

#[no_mangle]
extern "C" fn __oumalibc_start(raw_args: *mut c_void) {
  panic!("We are in libc! Arguments: {:?}", raw_args);
}
