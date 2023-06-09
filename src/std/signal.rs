use crate::c_int;

pub const __NSIG: c_int = 64;
pub const __RESERVED_SIGRT: c_int = 2;
pub const __SIGRTMIN: c_int = 32;
pub const __SIGRTMAX: c_int = __NSIG;

pub const NSIG: c_int = __NSIG + 1;
pub const SIGRTMIN: c_int = __oumalibc_current_sigrtmin();
pub const SIGRTMAX: c_int = __oumalibc_current_sigrtmax();

#[no_mangle]
pub const extern "C" fn __oumalibc_current_sigrtmin() -> c_int {
  __SIGRTMIN + __RESERVED_SIGRT
}

#[no_mangle]
pub const extern "C" fn __oumalibc_current_sigrtmax() -> c_int {
  __SIGRTMAX
}

pub const SYS_SIG_LIST: [&'static str; 32] = [
  "Unknown signal 0\0",
  "Hangup\0",
  "Interrupt\0",
  "Quit\0",
  "Illegal instruction\0",
  "Trace/breakpoint trap\0",
  "Aborted\0",
  "Bus error\0",
  "Floating point exception\0",
  "Killed\0",
  "User defined signal 1\0",
  "Segmentation fault\0",
  "User defined signal 2\0",
  "Broken pipe\0",
  "Alarm clock\0",
  "Terminated\0",
  "Stack fault\0",
  "Child exited\0",
  "Continued\0",
  "Stopped (signal)\0",
  "Stopped\0",
  "Stopped (tty input)\0",
  "Stopped (tty output)\0",
  "Urgent I/O condition\0",
  "CPU time limit exceeded\0",
  "File size limit exceeded\0",
  "Virtual timer expired\0",
  "Profiling timer expired\0",
  "Window changed\0",
  "I/O possible\0",
  "Power failure\0",
  "Bad system call\0"
];
