#![no_std]
#![allow(unused_macros, non_camel_case_types, non_upper_case_globals)]
#![feature(lang_items, no_sanitize, thread_local)]

extern crate alloc;
extern crate cbitset;

mod api;
mod dlmalloc;
#[macro_use]
mod macros;
mod types;

// Export types
pub use types::*;

// C library
pub mod arch;
pub mod init;
pub mod std;
pub mod support;
