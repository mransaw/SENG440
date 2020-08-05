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
	.file	"int_main.c"
	.text
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.arch armv7-a
	.syntax unified
	.arm
	.fpu neon
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 632
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r0, #0
	sub	sp, sp, #668
	movw	r5, #32769
	bl	time
	bl	srand
	movt	r5, 32768
	add	r4, sp, #172
	add	r6, sp, #244
.L2:
	sub	r7, r4, #12
.L3:
	bl	rand
	smull	r3, r2, r5, r0
	asr	r3, r0, #31
	add	r2, r2, r0
	rsb	r3, r3, r2, asr #15
	add	r0, r0, r3
	strh	r0, [r7], #2	@ movhi
	cmp	r7, r4
	bne	.L3
	add	r4, r7, #12
	cmp	r4, r6
	bne	.L2
	add	r10, sp, #160
	mov	r0, r10
	bl	print_matrixM
	mov	r4, #0
	mov	r3, #1073741824
	mov	ip, #16384
	vldr	d16, .L14
	add	r1, sp, #88
	mov	r2, #72
	add	r0, sp, #232
	str	r3, [sp, #100]
	str	r3, [sp, #128]
	str	r3, [sp, #156]
	vstr	d16, [sp, #88]
	str	ip, [sp, #116]
	str	ip, [sp, #144]
	str	r4, [sp, #36]
	str	r4, [sp, #96]
	str	r4, [sp, #104]
	str	r4, [sp, #108]
	str	r4, [sp, #112]
	str	r4, [sp, #120]
	str	r4, [sp, #124]
	str	r4, [sp, #132]
	str	r4, [sp, #136]
	str	r4, [sp, #140]
	str	r4, [sp, #148]
	str	r4, [sp, #152]
	bl	memcpy
	add	r1, sp, #88
	mov	r2, #72
	add	r0, sp, #304
	bl	memcpy
	str	r4, [sp, #40]
	bl	clock
	mov	r3, #10
	str	r0, [sp, #68]
	str	r3, [sp, #64]
	add	r9, sp, #376
	add	fp, sp, #448
.L5:
	mov	r3, #12
	str	r3, [sp, #52]
.L7:
	ldr	r3, [sp, #52]
	add	r2, r10, r3
	mov	r8, r3
	add	r6, r3, #2
	sub	r7, r3, #10
	add	r3, r9, r3
	str	r2, [sp, #56]
	str	r3, [sp, #60]
.L6:
	bl	clock
	ldr	r3, [sp, #56]
	str	r0, [sp, #48]
	ldrsh	r4, [r10, r8]
	ldrsh	r1, [r10, r6]
	ldrsh	ip, [r10, r7]
	ldrsh	r0, [r3, #-12]
	add	r2, r4, r1, lsl #16
	add	lr, ip, r0, lsl #16
	.syntax divided
@ 83 "int_main.c" 1
	 qadd16 r2 , r2 , lr
	
@ 0 "" 2
	.arm
	.syntax unified
	add	r4, r1, r4, lsl #16
	add	r0, r0, ip, lsl #16
	.syntax divided
@ 93 "int_main.c" 1
	 qsub16 r4 , r4 , r0
	
@ 0 "" 2
	.arm
	.syntax unified
	sxth	r1, r4
	sxth	r0, r2
	str	r2, [sp, #44]
	bl	arctan2
	ldr	r2, [sp, #44]
	mov	r5, r0
	asr	r1, r2, #16
	asr	r0, r4, #16
	bl	arctan2
	mov	r4, r0
	sub	r2, r5, r0
	add	r2, r2, #1
	add	r5, r5, r4
	add	r1, sp, #76
	add	r0, sp, #72
	asr	r2, r2, #1
	bl	cordic
	add	r2, r5, #1
	asr	r2, r2, #1
	add	r1, sp, #84
	add	r0, sp, #80
	bl	cordic
	bl	clock
	ldr	r3, [sp, #48]
	ldr	ip, [sp, #36]
	sub	r3, r0, r3
	add	r3, ip, r3
	add	r1, sp, #88
	mov	r2, #72
	mov	r0, r9
	str	r3, [sp, #36]
	bl	memcpy
	add	r1, sp, #88
	mov	r2, #72
	mov	r0, fp
	bl	memcpy
	ldr	r2, [sp, #72]
	ldr	r3, [sp, #80]
	ldr	r1, [sp, #52]
	ldr	ip, [sp, #76]
	ldr	r0, [sp, #84]
	ldr	r5, [sp, #60]
	sxth	r3, r3
	sxth	r2, r2
	add	r1, fp, r1
	strh	r3, [r1, #-12]	@ movhi
	rsb	r4, ip, #0
	rsb	lr, r0, #0
	strh	r2, [r5, #-12]	@ movhi
	strh	lr, [fp, r8]	@ movhi
	strh	r4, [r9, r7]	@ movhi
	strh	r0, [fp, r7]	@ movhi
	strh	ip, [r9, r8]	@ movhi
	strh	r3, [fp, r6]	@ movhi
	strh	r2, [r9, r6]	@ movhi
	bl	clock
	add	r1, sp, #520
	mov	r4, r0
	mov	r0, r9
	bl	transposeM
	mov	r2, r10
	mov	r1, r10
	mov	r0, r9
	bl	dot_productM
	add	r2, sp, #232
	mov	r0, r2
	add	r1, sp, #520
	bl	dot_productM
	add	r1, sp, #592
	mov	r0, fp
	bl	transposeM
	mov	r2, r10
	mov	r1, fp
	mov	r0, r10
	bl	dot_productM
	add	r2, sp, #304
	mov	r1, r2
	add	r0, sp, #592
	bl	dot_productM
	bl	clock
	ldr	r3, [sp, #40]
	add	r6, r6, #14
	sub	r0, r0, r4
	add	r3, r3, r0
	cmp	r6, #84
	add	r8, r8, #12
	add	r7, r7, #2
	str	r3, [sp, #40]
	bne	.L6
	ldr	r3, [sp, #52]
	add	r3, r3, #14
	cmp	r3, #82
	str	r3, [sp, #52]
	bne	.L7
	ldr	r3, [sp, #64]
	subs	r3, r3, #1
	str	r3, [sp, #64]
	bne	.L5
	bl	clock
	vldr.32	s15, [sp, #36]	@ int
	vcvt.f64.s32	d16, s15
	vldr.32	s15, [sp, #40]	@ int
	ldr	r3, [sp, #68]
	vcvt.f64.s32	d17, s15
	sub	r0, r0, r3
	vmov	s15, r0	@ int
	vldr.64	d19, .L14+8
	vcvt.f64.s32	d18, s15
	vmul.f64	d16, d16, d19
	vmul.f64	d17, d17, d19
	vldr.64	d20, .L14+16
	vmul.f64	d18, d18, d19
	vdiv.f64	d23, d16, d20
	vdiv.f64	d22, d16, d19
	vdiv.f64	d21, d17, d20
	vdiv.f64	d16, d17, d19
	movw	r0, #:lower16:.LC0
	vdiv.f64	d17, d18, d19
	vstr.64	d23, [sp, #8]
	vmov	r2, r3, d17
	vstr.64	d22, [sp]
	vstr.64	d21, [sp, #24]
	vstr.64	d16, [sp, #16]
	mov	r1, #10
	movt	r0, #:upper16:.LC0
	bl	printf
	mov	r0, r10
	bl	print_matrixM
	ldr	r0, [sp, #64]
	add	sp, sp, #668
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L15:
	.align	3
.L14:
	.short	16384
	.short	0
	.short	0
	.short	0
	.word	0
	.word	1093567616
	.word	0
	.word	1101206224
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d sweeps, took %.0f microseconds total\012calculat"
	.ascii	"ing angles took %.0fus (%.0f avg), rotating M and u"
	.ascii	"pdating MUV took %.0fus (%.0f avg)\012\012\000"
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
