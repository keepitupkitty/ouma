use core::arch::global_asm;

pub type jmp_buf = [crate::c_long; 32];
pub type sigjmp_buf = [crate::c_long; 33];

global_asm!(include_str!("setjmp.s"));
