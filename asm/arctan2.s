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
	.global	f1
	.arch armv7-a
	.syntax unified
	.arm
	.fpu neon
	.type	f1, %function
f1:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f1, .-f1
	.align	2
	.global	f2
	.syntax unified
	.arm
	.fpu neon
	.type	f2, %function
f2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f2, .-f2
	.align	2
	.global	f3
	.syntax unified
	.arm
	.fpu neon
	.type	f3, %function
f3:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f3, .-f3
	.align	2
	.global	f4
	.syntax unified
	.arm
	.fpu neon
	.type	f4, %function
f4:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f4, .-f4
	.align	2
	.global	f5
	.syntax unified
	.arm
	.fpu neon
	.type	f5, %function
f5:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f5, .-f5
	.align	2
	.global	f6
	.syntax unified
	.arm
	.fpu neon
	.type	f6, %function
f6:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f6, .-f6
	.align	2
	.global	f7
	.syntax unified
	.arm
	.fpu neon
	.type	f7, %function
f7:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f7, .-f7
	.align	2
	.global	f8
	.syntax unified
	.arm
	.fpu neon
	.type	f8, %function
f8:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f8, .-f8
	.align	2
	.global	f9
	.syntax unified
	.arm
	.fpu neon
	.type	f9, %function
f9:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	f9, .-f9
	.align	2
	.global	arctan2
	.syntax unified
	.arm
	.fpu neon
	.type	arctan2, %function
arctan2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	lsl	r1, r1, #14
	lsr	r3, r1, #31
	cmp	r1, #0
	rsblt	r3, r3, #0
	rsbge	r3, r3, #1
	lsl	r0, r0, #14
	mul	r0, r0, r3
	mvn	ip, r0
	mul	r1, r1, r3
	lsr	r2, r0, #31
	lsr	ip, ip, #31
	sub	r3, r2, ip
	mla	r3, r1, r3, r0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mvn	lr, r3
	sub	ip, ip, r2
	mla	r1, ip, r0, r1
	lsr	lr, lr, #31
	lsr	r0, r3, #31
	sub	r4, r0, lr
	asr	r2, r1, #1
	mla	r2, r4, r2, r3
	mvn	r5, r2
	sub	lr, lr, r0
	asr	r3, r3, #1
	mla	r1, lr, r3, r1
	lsr	r0, r2, #31
	lsr	r5, r5, #31
	sub	r3, r0, r5
	asr	r4, r1, #2
	mla	r3, r4, r3, r2
	mvn	r7, r3
	sub	r5, r5, r0
	asr	r2, r2, #2
	mla	r1, r5, r2, r1
	lsr	r0, r3, #31
	lsr	r7, r7, #31
	sub	r2, r0, r7
	asr	r4, r1, #3
	mla	r2, r4, r2, r3
	mvn	r8, r2
	sub	r7, r7, r0
	asr	r3, r3, #3
	mla	r1, r7, r3, r1
	lsr	r0, r2, #31
	lsr	r8, r8, #31
	sub	r3, r0, r8
	asr	r4, r1, #4
	mla	r3, r4, r3, r2
	mvn	r6, r3
	sub	r8, r8, r0
	asr	r2, r2, #4
	mla	r1, r8, r2, r1
	lsr	r6, r6, #31
	lsr	r2, r3, #31
	sub	r0, r2, r6
	asr	r9, r1, #5
	mla	r0, r9, r0, r3
	mvn	r4, r0
	sub	r6, r6, r2
	asr	r3, r3, #5
	mla	r2, r6, r3, r1
	lsr	r9, r0, #31
	lsr	r4, r4, #31
	sub	r3, r9, r4
	asr	r1, r2, #6
	mla	r3, r1, r3, r0
	mvn	r1, r3
	sub	r4, r4, r9
	asr	r0, r0, #6
	mla	r9, r4, r0, r2
	lsr	r1, r1, #31
	lsr	r0, r3, #31
	sub	fp, r0, r1
	asr	r2, r9, #7
	mla	fp, r2, fp, r3
	mvn	r10, fp
	movw	r2, #:lower16:angles
	sub	r1, r1, r0
	asr	r0, r3, #7
	mla	r0, r1, r0, r9
	lsr	r10, r10, #31
	lsr	r9, fp, #31
	movt	r2, #:upper16:angles
	sub	r3, r9, r10
	asr	r0, r0, #8
	mla	r0, r3, r0, fp
	ldr	r3, [r2, #4]
	sub	r9, r10, r9
	mul	lr, r3, lr
	ldr	r10, [r2]
	lsr	r3, r0, #31
	mla	ip, r10, ip, lr
	cmp	r0, #0
	rsblt	r3, r3, #0
	rsbge	r3, r3, #1
	ldr	lr, [r2, #8]
	ldr	r0, [r2, #12]
	mla	r5, lr, r5, ip
	mla	r7, r0, r7, r5
	ldr	r5, [r2, #16]
	ldr	r0, [r2, #20]
	mla	r8, r5, r8, r7
	mla	r6, r0, r6, r8
	ldr	r8, [r2, #24]
	ldr	r0, [r2, #28]
	mla	r4, r8, r4, r6
	mla	r1, r0, r1, r4
	ldr	r10, [r2, #32]
	ldr	r0, [r2, #36]
	mla	r1, r10, r9, r1
	mla	r0, r0, r3, r1
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	arctan2, .-arctan2
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
