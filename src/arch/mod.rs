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
