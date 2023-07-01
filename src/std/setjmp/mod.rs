use crate::c_int;

cfg_if! {
  if #[cfg(target_arch = "aarch64")] {
    mod arm64;
    pub use arm64::*;
  } else if #[cfg(target_arch = "x86_64")] {
    mod x86_64;
    pub use x86_64::*;
  } else {
    compile_error!("Platform is not supported");
  }
}

extern "C" {
  pub fn __oumalibc_longjmp(
    buf: *mut jmp_buf,
    c: c_int
  );
  pub fn __oumalibc__longjmp(
    buf: *mut jmp_buf,
    c: c_int
  );
  pub fn __oumalibc_siglongjmp(
    buf: *mut sigjmp_buf,
    c: c_int
  );
  pub fn __oumalibc_setjmp(buf: *mut jmp_buf) -> c_int;
  pub fn __oumalibc__setjmp(buf: *mut jmp_buf) -> c_int;
  pub fn __oumalibc_sigsetjmp(
    buf: *mut sigjmp_buf,
    c: c_int
  ) -> c_int;
}

#[no_mangle]
pub extern "C" fn ouma_longjmp(
  buf: *mut jmp_buf,
  c: c_int
) {
  unsafe { __oumalibc_longjmp(buf, c) };
}

#[no_mangle]
pub extern "C" fn ouma__longjmp(
  buf: *mut jmp_buf,
  c: c_int
) {
  unsafe { __oumalibc__longjmp(buf, c) };
}

#[no_mangle]
pub extern "C" fn ouma_siglongjmp(
  buf: *mut sigjmp_buf,
  c: c_int
) {
  unsafe { __oumalibc_siglongjmp(buf, c) };
}

#[no_mangle]
pub extern "C" fn ouma_setjmp(buf: *mut jmp_buf) -> c_int {
  unsafe { __oumalibc_setjmp(buf) }
}

#[no_mangle]
pub extern "C" fn ouma__setjmp(buf: *mut jmp_buf) -> c_int {
  unsafe { __oumalibc__setjmp(buf) }
}

#[no_mangle]
pub extern "C" fn ouma_sigsetjmp(
  buf: *mut sigjmp_buf,
  c: c_int
) -> c_int {
  unsafe { __oumalibc_sigsetjmp(buf, c) }
}
