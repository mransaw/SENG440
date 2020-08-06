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
	.global	cordic_arctan
	.arch armv7-a
	.syntax unified
	.arm
	.fpu neon
	.type	cordic_arctan, %function
cordic_arctan:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	lsl	r0, r0, #14
	lsr	r3, r0, #31
	cmp	r0, #0
	rsblt	r3, r3, #0
	rsbge	r3, r3, #1
	lsl	r1, r1, #14
	mul	r0, r0, r3
	lsr	r3, r1, #31
	cmp	r1, #0
	rsblt	r3, r3, #0
	rsbge	r3, r3, #1
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
	mvn	r4, r2
	sub	r0, lr, r0
	asr	r3, r3, #1
	mla	r1, r0, r3, r1
	lsr	r4, r4, #31
	lsr	lr, r2, #31
	sub	r3, lr, r4
	asr	r5, r1, #2
	mla	r3, r5, r3, r2
	mvn	r5, r3
	sub	lr, r4, lr
	asr	r2, r2, #2
	mla	r1, lr, r2, r1
	lsr	r5, r5, #31
	lsr	r4, r3, #31
	sub	r2, r4, r5
	asr	r6, r1, #3
	mla	r2, r6, r2, r3
	mvn	r6, r2
	sub	r4, r5, r4
	asr	r3, r3, #3
	mla	r1, r4, r3, r1
	lsr	r6, r6, #31
	lsr	r5, r2, #31
	sub	r3, r5, r6
	asr	r7, r1, #4
	mla	r3, r7, r3, r2
	mvn	r7, r3
	sub	r5, r6, r5
	asr	r2, r2, #4
	mla	r1, r5, r2, r1
	lsr	r7, r7, #31
	lsr	r2, r3, #31
	sub	r9, r2, r7
	asr	r6, r1, #5
	mla	r9, r6, r9, r3
	mvn	r8, r9
	sub	r7, r7, r2
	asr	r3, r3, #5
	mla	r3, r7, r3, r1
	lsr	r8, r8, #31
	lsr	r1, r9, #31
	sub	r2, r1, r8
	asr	r6, r3, #6
	mla	r2, r6, r2, r9
	mvn	r6, r2
	sub	r8, r8, r1
	asr	r1, r9, #6
	mla	r1, r8, r1, r3
	lsr	fp, r2, #31
	lsr	r6, r6, #31
	sub	r10, fp, r6
	asr	r3, r1, #7
	mla	r10, r3, r10, r2
	movw	r3, #:lower16:angles
	mvn	r9, r10
	sub	r6, r6, fp
	asr	r2, r2, #7
	mla	r1, r6, r2, r1
	movt	r3, #:upper16:angles
	ldr	fp, [r3, #4]
	lsr	r2, r10, #31
	lsr	r9, r9, #31
	mul	fp, fp, r0
	asr	r1, r1, #8
	sub	r0, r2, r9
	mla	r1, r0, r1, r10
	ldr	r0, [r3]
	lsr	r10, r1, #31
	mla	ip, r0, ip, fp
	cmp	r1, #0
	rsblt	r1, r10, #0
	rsbge	r1, r10, #1
	ldr	fp, [r3, #8]
	ldr	r0, [r3, #12]
	mla	lr, fp, lr, ip
	mla	r4, r0, r4, lr
	ldr	lr, [r3, #16]
	ldr	r0, [r3, #20]
	mla	r5, lr, r5, r4
	mla	r7, r0, r7, r5
	ldr	r5, [r3, #24]
	ldr	r0, [r3, #28]
	mla	r8, r5, r8, r7
	mla	r6, r0, r6, r8
	ldr	r0, [r3, #32]
	sub	r9, r9, r2
	mla	r9, r0, r9, r6
	ldr	r0, [r3, #36]
	mla	r0, r0, r1, r9
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
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
	lsl	r0, r0, #14
	lsr	r3, r0, #31
	cmp	r0, #0
	rsblt	r3, r3, #0
	rsbge	r3, r3, #1
	lsl	r2, r1, #14
	mul	r0, r3, r0
	lsr	r1, r2, #31
	cmp	r2, #0
	rsblt	r1, r1, #0
	rsbge	r1, r1, #1
	mvn	ip, r0
	mul	r1, r1, r2
	lsr	ip, ip, #31
	lsr	r2, r0, #31
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
	mvn	r4, r2
	sub	lr, lr, r0
	asr	r3, r3, #1
	mla	r1, lr, r3, r1
	lsr	r0, r2, #31
	lsr	r4, r4, #31
	sub	r3, r0, r4
	asr	r5, r1, #2
	mla	r3, r5, r3, r2
	mvn	r5, r3
	sub	r4, r4, r0
	asr	r2, r2, #2
	mla	r1, r4, r2, r1
	lsr	r0, r3, #31
	lsr	r5, r5, #31
	sub	r2, r0, r5
	asr	r6, r1, #3
	mla	r2, r6, r2, r3
	mvn	r6, r2
	sub	r5, r5, r0
	asr	r3, r3, #3
	mla	r1, r5, r3, r1
	lsr	r0, r2, #31
	lsr	r6, r6, #31
	sub	r3, r0, r6
	asr	r7, r1, #4
	mla	r3, r7, r3, r2
	mvn	r8, r3
	sub	r6, r6, r0
	asr	r2, r2, #4
	mla	r1, r6, r2, r1
	lsr	r8, r8, #31
	lsr	r2, r3, #31
	sub	r10, r2, r8
	asr	r0, r1, #5
	mla	r10, r0, r10, r3
	mvn	r9, r10
	sub	r8, r8, r2
	asr	r3, r3, #5
	mla	r3, r8, r3, r1
	lsr	r0, r10, #31
	lsr	r9, r9, #31
	sub	r2, r0, r9
	asr	r1, r3, #6
	mla	r2, r1, r2, r10
	mvn	r7, r2
	sub	r9, r9, r0
	asr	r1, r10, #6
	mla	r1, r9, r1, r3
	lsr	r0, r2, #31
	lsr	r7, r7, #31
	sub	fp, r0, r7
	asr	r3, r1, #7
	mla	fp, r3, fp, r2
	movw	r3, #:lower16:angles
	mvn	r10, fp
	sub	r7, r7, r0
	asr	r2, r2, #7
	mla	r1, r7, r2, r1
	movt	r3, #:upper16:angles
	ldr	r0, [r3, #4]
	lsr	r2, fp, #31
	lsr	r10, r10, #31
	mul	lr, r0, lr
	asr	r1, r1, #8
	sub	r0, r2, r10
	mla	r1, r0, r1, fp
	ldr	r0, [r3]
	lsr	fp, r1, #31
	mla	ip, r0, ip, lr
	cmp	r1, #0
	rsblt	r1, fp, #0
	rsbge	r1, fp, #1
	ldr	lr, [r3, #8]
	ldr	r0, [r3, #12]
	mla	r4, lr, r4, ip
	mla	r5, r0, r5, r4
	ldr	r4, [r3, #16]
	ldr	r0, [r3, #20]
	mla	r6, r4, r6, r5
	mla	r8, r0, r8, r6
	ldr	r6, [r3, #24]
	ldr	r0, [r3, #28]
	mla	r9, r6, r9, r8
	mla	r7, r0, r7, r9
	ldr	r0, [r3, #32]
	sub	r10, r10, r2
	mla	r10, r0, r10, r7
	ldr	r0, [r3, #36]
	mla	r0, r0, r1, r10
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	arctan2, .-arctan2
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
