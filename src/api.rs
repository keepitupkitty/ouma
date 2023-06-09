use {
  crate::c_int,
  core::{fmt, fmt::Write, panic::PanicInfo},
  syscalls::*
};

struct IoWrite(pub c_int);

impl IoWrite {
  fn write(
    &self,
    buf: &[u8]
  ) {
    let _ = unsafe { syscall!(Sysno::write, self.0, buf.as_ptr(), buf.len()) };
  }
}

impl fmt::Write for IoWrite {
  fn write_str(
    &mut self,
    s: &str
  ) -> fmt::Result {
    self.write(s.as_bytes());
    Ok(())
  }
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
  let mut w = IoWrite(2);
  let _ =
    w.write_fmt(format_args!("\x1b[31mOUMA LIBC PANIC\x1b[0m: {}\n", info));
  let _ = unsafe { syscall!(Sysno::exit, 127) };
  loop {}
}

#[lang = "eh_personality"]
#[no_mangle]
pub extern "C" fn rust_eh_personality() {}
