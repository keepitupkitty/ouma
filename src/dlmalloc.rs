// Adopted from Redox relibc

use {
  crate::{c_int, size_t},
  alloc::alloc::{GlobalAlloc, Layout},
  core::{
    ffi::c_void,
    sync::atomic::{AtomicUsize, Ordering}
  }
};

extern "C" {
  pub fn mspace_memalign(
    msp: usize,
    alignment: size_t,
    bytes: size_t
  ) -> *mut c_void;
  pub fn mspace_free(
    msp: usize,
    mem: *mut c_void
  );
  pub fn dlcalloc(
    n: size_t,
    l: size_t
  ) -> *mut c_void;
  pub fn dlfree(ptr: *mut c_void);
  pub fn dlmalloc(n: size_t) -> *mut c_void;
  pub fn dlposix_memalign(
    ptr: *mut *mut c_void,
    n: size_t,
    l: size_t
  ) -> c_int;
  pub fn dlrealloc(
    ptr: *mut c_void,
    n: size_t
  ) -> *mut c_void;
}

pub struct Dlmalloc {
  mstate: AtomicUsize
}

#[global_allocator]
pub static ALLOCATOR: Dlmalloc = Dlmalloc { mstate: AtomicUsize::new(0) };

impl Dlmalloc {
  pub fn get_book_keeper(&self) -> usize {
    self.mstate.load(Ordering::Relaxed)
  }
}

unsafe impl GlobalAlloc for Dlmalloc {
  #[inline(always)]
  unsafe fn alloc(
    &self,
    layout: Layout
  ) -> *mut u8 {
    mspace_memalign(ALLOCATOR.get_book_keeper(), layout.size(), layout.align())
      as *mut u8
  }

  #[inline(always)]
  unsafe fn dealloc(
    &self,
    ptr: *mut u8,
    _layout: Layout
  ) {
    mspace_free(ALLOCATOR.get_book_keeper(), ptr as *mut c_void)
  }
}
