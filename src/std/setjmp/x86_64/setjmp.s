.text
.align 2
.globl __oumalibc_sigsetjmp
__oumalibc_sigsetjmp:
	movl	%esi,(8 * 8)(%rdi)
	testl	%esi,%esi
	jz	2f

	pushq	%rdi
	movq	%rdi,%rcx
	movq	$1,%rdi			/* SIG_BLOCK       */
	movq	$0,%rsi			/* (sigset_t*)set  */
	leaq	(9 * 8)(%rdi),%rdx	/* 9,10 (sigset_t*)oset */
	call	sigprocmask
	popq	%rdi
2:
	// Save the callee-save registers.
	movq	(%rsp),%r11
	movq	%rbx,(0 * 8)(%rdi)
	movq	%rbp,(1 * 8)(%rdi)
	movq	%r12,(2 * 8)(%rdi)
	movq	%r13,(3 * 8)(%rdi)
	movq	%r14,(4 * 8)(%rdi)
	movq	%r15,(5 * 8)(%rdi)
	movq	%rsp,(6 * 8)(%rdi)
	movq	%r11,(7  * 8)(%rdi)

	xorl	%eax,%eax
	ret
.size __oumalibc_sigsetjmp, .-__oumalibc_sigsetjmp

.text
.align 2
.globl __oumalibc_setjmp
__oumalibc_setjmp:
	movl	$1, %esi
	jmp	__oumalibc_sigsetjmp
.size __oumalibc_setjmp, .-__oumalibc_setjmp

.text
.align 2
.globl __oumalibc__setjmp
__oumalibc__setjmp:
	xorl	%esi, %esi
	jmp	__oumalibc_sigsetjmp
.size __oumalibc__setjmp, .-__oumalibc__setjmp

.text
.align 2
.globl __oumalibc_siglongjmp
__oumalibc_siglongjmp:
	movq	%rdi,%r12
	pushq	%rsi
	cmpl	$0, (8 * 8)(%rdi)
	jz	2f

	leaq	(9 * 8)(%rdi),%rsi
	movl	$3,%edi		/* SIG_SETMASK */
	xorq	%rdx,%rdx
	call	sigprocmask
2:
	popq	%rax

	// Restore the callee-save registers.
	movq	(0 * 8)(%rdi),%rbx
	movq	(1 * 8)(%rdi),%rbp
	movq	(2 * 8)(%rdi),%r12
	movq	(3 * 8)(%rdi),%r13
	movq	(4 * 8)(%rdi),%r14
	movq	(5 * 8)(%rdi),%r15
	movq	(6 * 8)(%rdi),%rsp
	movq	(7 * 8)(%rdi),%r11

	movl	%esi,%eax
	testl	%eax,%eax
	jnz	1f
	incl	%eax
1:	movq	%r11,0(%rsp)
	ret
.weak __oumalibc_longjmp
.equ  __oumalibc_longjmp, __oumalibc_siglongjmp
.weak __oumalibc__longjmp
.equ  __oumalibc__longjmp, __oumalibc_siglongjmp
.size __oumalibc_siglongjmp, .-__oumalibc_siglongjmp
