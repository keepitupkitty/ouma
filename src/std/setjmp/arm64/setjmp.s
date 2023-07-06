.text
.align 2
.globl __oumalibc_setjmp
__oumalibc_setjmp:
	mov w1, #1
	b __oumalibc_sigsetjmp
.size __oumalibc_setjmp, .-__oumalibc_setjmp

.text
.align 2
.globl __oumalibc__setjmp
__oumalibc__setjmp:
	mov w1, #0
	b __oumalibc_sigsetjmp
.size __oumalibc__setjmp, .-__oumalibc__setjmp

.text
.align 2
.globl __oumalibc_sigsetjmp
__oumalibc_sigsetjmp:
	// Check if we have signal mask
	str	w1, [x0, #0]

	// Check if we actually need a sigmask
	cbz	w1, 1f

	// Store current signal mask
	stp	x0, x30, [sp, #-16]
	mov	x1, #0 // NULL
	add	x2, x0, #8 // old
	bl	sigprocmask
	ldp	x0, x30, [sp], #16

1:
	// Store the low bits of the shadow call stack pointer
	and	x3, x18, #0x1fff

	// Store core registers
	mov	x10, sp
	stp	x30, x10, [x0, #16]
	stp	x28, x29, [x0, #32]
	stp	x26, x27, [x0, #48]
	stp	x24, x25, [x0, #64]
	stp	x22, x23, [x0, #80]
	stp	x20, x21, [x0, #96]
	stp	x3,  x19, [x0, #112]

	// Store floating point registers
	stp	d14, d15, [x0, #128]
	stp	d12, d13, [x0, #144]
	stp	d10, d11, [x0, #160]
	stp	d8,  d9,  [x0, #176]

	// Return
	mov	w0, #0
	ret
.size __oumalibc_sigsetjmp, .-__oumalibc_sigsetjmp

.text
.align 2
.globl __oumalibc_siglongjmp
__oumalibc_siglongjmp:
	// Check if we need to restore signal mask
	ldr	w9, [x0, #0]
	cbz	w9, 1f

	// Restore signal mask
	stp	x0, x30, [sp, #-16]
	mov	x19, x1 // Stored value
	mov	x2, x0
	mov	x0, #2 // mask
	add	x1, x2, #8 // new mask
	mov	x2, #0 // NULL
	bl	sigprocmask
	mov	x1, x19 // Restored value
	ldp	x0, x30, [sp], #16

1:
	// Restore core registers
	ldp	x30, x10, [x0, #16]
	ldp	x28, x29, [x0, #32]
	ldp	x26, x27, [x0, #48]
	ldp	x24, x25, [x0, #64]
	ldp	x22, x23, [x0, #80]
	ldp	x20, x21, [x0, #96]
	ldp	x3,  x19, [x0, #112]
	mov	sp, x10

	// Restore the low bits of the shadow call stack pointer
	and	x18, x18, #0xffffffffffffe000
	orr	x18, x3, x18

	// Restore floating point registers
	ldp	d14, d15, [x0, #128]
	ldp	d12, d13, [x0, #144]
	ldp	d10, d11, [x0, #160]
	ldp	d8,  d9,  [x0, #176]

	// Return
	cmp	w1, wzr
	csinc	w0, w1, wzr, ne
	ret
.weak __oumalibc_longjmp
.equ  __oumalibc_longjmp, __oumalibc_siglongjmp
.weak __oumalibc__longjmp
.equ  __oumalibc__longjmp, __oumalibc_siglongjmp
.size __oumalibc_siglongjmp, .-__oumalibc_siglongjmp
