	.arch armv7-a
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"arctan2.c"
	.text
	.align	2
	.global	phase_shift
	.arch armv7-a
	.syntax unified
	.arm
	.fpu neon
	.type	phase_shift, %function
phase_shift:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #0
	cmple	r0, #0
	addle	r2, r2, #180
	mov	r0, r2
	bx	lr
	.size	phase_shift, .-phase_shift
	.align	2
	.global	cordic_arctan
	.syntax unified
	.arm
	.fpu neon
	.type	cordic_arctan, %function
cordic_arctan:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:angles
	lsls	r1, r1, #14
	lsl	r0, r0, #14
	movt	ip, #:upper16:angles
	rsbmi	r0, r0, #0
	rsbmi	r1, r1, #0
	push	{r4, lr}
	cmp	r0, #0
	ldr	lr, [ip]
	subge	r3, r0, r1
	addlt	r3, r1, r0
	addge	r2, r1, r0
	sublt	r2, r1, r0
	asr	r4, r3, #1
	ldr	r0, [ip, #4]
	asr	r1, r2, #1
	rsblt	lr, lr, #0
	cmp	r3, #0
	subge	r3, r3, r1
	addlt	r3, r3, r1
	addge	r2, r2, r4
	sublt	r2, r2, r4
	asr	r1, r2, #2
	asr	r4, r3, #2
	addge	r0, lr, r0
	sublt	r0, lr, r0
	cmp	r3, #0
	ldr	lr, [ip, #8]
	subge	r3, r3, r1
	addlt	r3, r3, r1
	addge	r2, r2, r4
	sublt	r2, r2, r4
	asr	r1, r2, #3
	asr	r4, r3, #3
	addge	r0, r0, lr
	sublt	r0, r0, lr
	cmp	r3, #0
	ldr	lr, [ip, #12]
	subge	r3, r3, r1
	addlt	r3, r3, r1
	addge	r2, r2, r4
	sublt	r2, r2, r4
	addge	r0, r0, lr
	asr	r4, r3, #4
	sublt	r0, r0, lr
	ldr	r1, [ip, #16]
	cmp	r3, #0
	asr	lr, r2, #4
	subge	r3, r3, lr
	addlt	r3, r3, lr
	addge	r2, r2, r4
	sublt	r2, r2, r4
	asr	lr, r2, #5
	asr	r4, r3, #5
	addge	r0, r0, r1
	sublt	r0, r0, r1
	cmp	r3, #0
	ldr	r1, [ip, #20]
	subge	r3, r3, lr
	addlt	r3, r3, lr
	addge	r2, r2, r4
	sublt	r2, r2, r4
	addge	r0, r0, r1
	asr	r4, r3, #6
	sublt	r0, r0, r1
	asr	lr, r2, #6
	cmp	r3, #0
	ldr	r1, [ip, #24]
	subge	r3, r3, lr
	addlt	r3, r3, lr
	addge	r2, r2, r4
	sublt	r2, r2, r4
	addge	r0, r0, r1
	asr	r4, r3, #7
	sublt	r0, r0, r1
	asr	lr, r2, #7
	cmp	r3, #0
	ldr	r1, [ip, #28]
	subge	r3, r3, lr
	addlt	r3, r3, lr
	addge	r2, r2, r4
	sublt	r2, r2, r4
	addge	r0, r0, r1
	sublt	r0, r0, r1
	asr	r2, r2, #8
	cmp	r3, #0
	ldr	r1, [ip, #32]
	subge	r3, r3, r2
	addlt	r3, r3, r2
	addge	r0, r0, r1
	sublt	r0, r0, r1
	cmp	r3, #0
	ldr	r3, [ip, #36]
	addge	r0, r3, r0
	sublt	r0, r0, r3
	pop	{r4, pc}
	.size	cordic_arctan, .-cordic_arctan
	.align	2
	.global	arctan2
	.syntax unified
	.arm
	.fpu neon
	.type	arctan2, %function
arctan2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	ip, #:lower16:angles
	lsls	r1, r1, #14
	lsl	r0, r0, #14
	movt	ip, #:upper16:angles
	rsbmi	r0, r0, #0
	rsbmi	r1, r1, #0
	push	{r4, lr}
	cmp	r0, #0
	ldr	lr, [ip]
	subge	r3, r0, r1
	addlt	r3, r0, r1
	addge	r2, r0, r1
	sublt	r2, r1, r0
	asr	r4, r3, #1
	ldr	r0, [ip, #4]
	asr	r1, r2, #1
	rsblt	lr, lr, #0
	cmp	r3, #0
	subge	r3, r3, r1
	addlt	r3, r3, r1
	addge	r2, r2, r4
	sublt	r2, r2, r4
	asr	r1, r2, #2
	asr	r4, r3, #2
	addge	r0, lr, r0
	sublt	r0, lr, r0
	cmp	r3, #0
	ldr	lr, [ip, #8]
	subge	r3, r3, r1
	addlt	r3, r3, r1
	addge	r2, r2, r4
	sublt	r2, r2, r4
	asr	r1, r2, #3
	asr	r4, r3, #3
	addge	r0, r0, lr
	sublt	r0, r0, lr
	cmp	r3, #0
	ldr	lr, [ip, #12]
	subge	r3, r3, r1
	addlt	r3, r3, r1
	addge	r2, r2, r4
	sublt	r2, r2, r4
	asr	r1, r2, #4
	asr	r4, r3, #4
	addge	r0, r0, lr
	sublt	r0, r0, lr
	cmp	r3, #0
	ldr	lr, [ip, #16]
	subge	r3, r3, r1
	addlt	r3, r3, r1
	addge	r2, r2, r4
	sublt	r2, r2, r4
	addge	r0, r0, lr
	asr	r4, r3, #5
	sublt	r0, r0, lr
	ldr	r1, [ip, #20]
	cmp	r3, #0
	asr	lr, r2, #5
	subge	r3, r3, lr
	addlt	r3, r3, lr
	addge	r2, r2, r4
	sublt	r2, r2, r4
	addge	r0, r0, r1
	asr	r4, r3, #6
	sublt	r0, r0, r1
	asr	lr, r2, #6
	cmp	r3, #0
	ldr	r1, [ip, #24]
	subge	r3, r3, lr
	addlt	r3, r3, lr
	addge	r2, r2, r4
	sublt	r2, r2, r4
	addge	r0, r0, r1
	asr	r4, r3, #7
	sublt	r0, r0, r1
	asr	lr, r2, #7
	cmp	r3, #0
	ldr	r1, [ip, #28]
	subge	r3, r3, lr
	addlt	r3, r3, lr
	addge	r2, r2, r4
	sublt	r2, r2, r4
	addge	r0, r0, r1
	sublt	r0, r0, r1
	asr	r2, r2, #8
	cmp	r3, #0
	ldr	r1, [ip, #32]
	subge	r3, r3, r2
	addlt	r3, r3, r2
	addge	r0, r0, r1
	sublt	r0, r0, r1
	cmp	r3, #0
	ldr	r3, [ip, #36]
	addge	r0, r3, r0
	sublt	r0, r0, r3
	pop	{r4, pc}
	.size	arctan2, .-arctan2
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
