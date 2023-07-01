use core::arch::global_asm;

pub type jmp_buf = [crate::c_long; 11];
pub type sigjmp_buf = [crate::c_long; 12];

global_asm!(include_str!("setjmp.s"), options(att_syntax));
