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
	.file	"diagonalize.c"
	.text
	.align	2
	.global	cordic
	.arch armv7-a
	.syntax unified
	.arm
	.fpu neon
	.type	cordic, %function
cordic:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r2, #0
	movlt	ip, #49152
	movge	ip, #16384
	addlt	r2, r2, #8192
	subge	r2, r2, #8192
	movtlt	ip, 65535
	cmp	r2, #0
	addlt	r2, r2, #4800
	subge	r2, r2, #4800
	asr	r3, ip, #1
	addlt	r2, r2, #36
	subge	r2, r2, #36
	addlt	r3, r3, #16384
	sublt	ip, ip, #8192
	rsbge	r3, r3, #16384
	addge	ip, ip, #8192
	cmp	r2, #0
	addlt	r2, r2, #2544
	subge	r2, r2, #2544
	addlt	r2, r2, #11
	subge	r2, r2, #11
	push	{r4, lr}
	asr	r4, ip, #2
	asr	lr, r3, #2
	sublt	ip, ip, lr
	addlt	r3, r3, r4
	subge	r3, r3, r4
	addge	ip, ip, lr
	cmp	r2, #0
	addlt	r2, r2, #1296
	subge	r2, r2, #1296
	asr	r4, ip, #3
	asr	lr, r3, #3
	addlt	r2, r2, #1
	subge	r2, r2, #1
	addlt	r3, r3, r4
	sublt	ip, ip, lr
	subge	r3, r3, r4
	addge	ip, ip, lr
	cmp	r2, #0
	addlt	r2, r2, #648
	subge	r2, r2, #648
	asr	r4, ip, #4
	asr	lr, r3, #4
	addlt	r2, r2, #3
	subge	r2, r2, #3
	addlt	r3, r3, r4
	sublt	ip, ip, lr
	subge	r3, r3, r4
	addge	ip, ip, lr
	cmp	r2, #0
	asr	r4, ip, #5
	asr	lr, r3, #5
	addlt	r2, r2, #324
	subge	r2, r2, #324
	addlt	r3, r3, r4
	sublt	ip, ip, lr
	subge	r3, r3, r4
	addge	ip, ip, lr
	addlt	r2, r2, #2
	subge	r2, r2, #2
	cmp	r2, #0
	asr	r4, ip, #6
	asr	lr, r3, #6
	sublt	ip, ip, lr
	addlt	r3, r3, r4
	subge	r3, r3, r4
	addge	ip, ip, lr
	addlt	r2, r2, #163
	subge	r2, r2, #163
	cmp	r2, #0
	asr	r4, ip, #7
	asr	lr, r3, #7
	sublt	ip, ip, lr
	addlt	r3, r3, r4
	subge	r3, r3, r4
	addge	ip, ip, lr
	addlt	r2, r2, #81
	subge	r2, r2, #81
	cmp	r2, #0
	asr	lr, r3, #8
	asr	r4, ip, #8
	addlt	r3, r3, r4
	sublt	ip, ip, lr
	subge	r3, r3, r4
	addge	ip, ip, lr
	addlt	r2, r2, #41
	subge	r2, r2, #41
	asr	lr, ip, #9
	cmp	r2, #0
	asr	r2, r3, #9
	sublt	ip, ip, r2
	addlt	r3, lr, r3
	subge	r3, r3, lr
	addge	ip, r2, ip
	rsb	lr, r3, r3, lsl #5
	rsb	r2, ip, ip, lsl #5
	add	lr, r3, lr, lsl #4
	add	r2, ip, r2, lsl #4
	add	lr, r3, lr, lsl #1
	add	r2, ip, r2, lsl #1
	rsb	r3, r3, lr, lsl #4
	rsb	ip, ip, r2, lsl #4
	add	r3, r3, r3, lsl #2
	add	ip, ip, ip, lsl #2
	add	r3, r3, #65536
	add	ip, ip, #65536
	asr	r3, r3, #17
	asr	ip, ip, #17
	str	r3, [r0]
	str	ip, [r1]
	pop	{r4, pc}
	.size	cordic, .-cordic
	.align	2
	.global	dot_productM
	.syntax unified
	.arm
	.fpu neon
	.type	dot_productM, %function
dot_productM:
	@ args = 0, pretend = 0, frame = 544
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	vpush.64	{d8, d9, d10, d11, d12, d13, d14, d15}
	mov	r7, r1
	ldrsh	r3, [r0, #28]
	ldrsh	ip, [r0, #6]
	sub	sp, sp, #548
	ldrsh	r1, [r0, #8]
	str	r3, [sp, #4]
	str	ip, [sp, #8]
	ldrsh	r3, [r0, #10]
	ldrsh	ip, [r0, #18]
	str	r1, [sp, #12]
	str	r3, [sp, #16]
	ldrsh	r1, [r0, #20]
	ldrsh	r3, [r0, #22]
	str	ip, [sp, #20]
	ldrsh	ip, [r0, #30]
	str	r1, [sp, #24]
	str	r3, [sp, #28]
	ldrsh	r1, [r0, #32]
	str	ip, [sp, #32]
	ldrsh	r3, [r0, #34]
	ldrsh	ip, [r0, #36]
	ldrsh	r6, [r0]
	ldrsh	lr, [r0, #2]
	ldrsh	r8, [r0, #12]
	ldrsh	r4, [r0, #4]
	ldrsh	r5, [r0, #14]
	ldrsh	r9, [r0, #16]
	ldrsh	r10, [r0, #24]
	ldrsh	fp, [r0, #26]
	str	r1, [sp, #36]
	str	ip, [sp, #44]
	str	r3, [sp, #40]
	ldrsh	r3, [r0, #38]
	ldrsh	r1, [r0, #40]
	ldrsh	ip, [r0, #48]
	str	r3, [sp, #48]
	ldrsh	r3, [r0, #50]
	str	r1, [sp, #52]
	str	ip, [sp, #56]
	ldrsh	r1, [r0, #52]
	ldrsh	ip, [r0, #60]
	str	r3, [sp, #60]
	ldrsh	r3, [r0, #62]
	str	r1, [sp, #64]
	str	ip, [sp, #68]
	ldrsh	r1, [r0, #64]
	ldrsh	ip, [r0, #42]
	str	r3, [sp, #72]
	ldrsh	r3, [r0, #44]
	str	r1, [sp, #76]
	str	ip, [sp, #80]
	ldrsh	r1, [r0, #46]
	ldrsh	ip, [r0, #54]
	str	r3, [sp, #84]
	ldrsh	r3, [r0, #56]
	str	r1, [sp, #88]
	str	ip, [sp, #92]
	ldrsh	r1, [r0, #66]
	ldrsh	ip, [r0, #58]
	str	r3, [sp, #96]
	ldrsh	r3, [r0, #68]
	str	ip, [sp, #100]
	str	r1, [sp, #104]
	str	r3, [sp, #108]
	vdup.16	d7, fp
	vld1.16	{d19}, [r7]
	str	fp, [sp, #124]
	ldr	fp, [sp, #32]
	add	r3, r7, #48
	vdup.16	d29, fp
	ldr	fp, [sp, #92]
	vld1.16	{d16}, [r3]
	vdup.16	d23, fp
	ldr	fp, [sp, #96]
	ldr	r3, [sp, #108]
	vdup.16	d24, fp
	ldr	fp, [sp, #72]
	add	ip, r7, #12
	vdup.16	d25, fp
	ldr	fp, [sp, #68]
	vld1.16	{d20}, [ip]
	vdup.16	d5, fp
	vdup.16	d1, r3
	vdup.16	d0, r6
	vdup.16	d4, lr
	ldr	ip, [sp, #8]
	vdup.16	d8, r5
	vdup.16	d12, ip
	mov	ip, r5
	ldr	r5, [sp, #24]
	str	r10, [sp, #120]
	vdup.16	d6, r5
	ldr	r5, [sp, #20]
	vdup.16	d31, r10
	vdup.16	d22, r5
	ldr	r5, [sp, #44]
	ldr	r10, [sp, #48]
	vdup.16	d27, r5
	ldr	r5, [sp, #80]
	vdup.16	d28, r10
	vdup.16	d26, r5
	ldr	r10, [sp, #84]
	ldr	r5, [sp, #56]
	vdup.16	d3, r10
	vdup.16	d21, r5
	ldr	r10, [sp, #60]
	ldr	r5, [sp, #104]
	vdup.16	d18, r10
	vstr	d24, [sp, #256]
	vstr	d5, [sp, #184]
	vdup.16	d2, r5
	vmull.s16 q2, d4, d20
	vstr	d1, [sp, #272]
	vdup.16	d24, r4
	vmull.s16 q0, d0, d19
	add	r1, r7, #36
	vld1.16	{d17}, [r1]
	ldr	r1, [sp, #12]
	vstr	d18, [sp, #136]
	vstr	d21, [sp, #168]
	vstr	d23, [sp, #248]
	vstr	d25, [sp, #240]
	vstr	d2, [sp, #264]
	vdup.16	d14, r1
	ldr	r1, [sp, #36]
	ldrsh	r0, [r0, #70]
	vstr	d24, [sp, #128]
	vadd.i32	d24, d0, d4
	vstr	d24, [sp, #280]
	vmull.s16 q12, d6, d16
	vstr	d24, [sp, #288]
	vstr	d25, [sp, #296]
	vmull.s16 q12, d17, d29
	vstr	d24, [sp, #328]
	vstr	d25, [sp, #336]
	vmull.s16 q12, d20, d28
	vstr	d24, [sp, #360]
	vstr	d25, [sp, #368]
	vmull.s16 q12, d19, d27
	vmull.s16 q13, d17, d26
	vldr	d28, [sp, #240]
	vstr	d26, [sp, #376]
	vstr	d27, [sp, #384]
	vldr	d27, [sp, #136]
	vadd.i32	d21, d1, d5
	vmull.s16 q2, d20, d27
	vmull.s16 q13, d20, d28
	vstr	d26, [sp, #136]
	vstr	d27, [sp, #144]
	vldr	d27, [sp, #168]
	mov	r10, r0
	ldr	r0, [sp, #28]
	vstr	d4, [sp, #408]
	vstr	d5, [sp, #416]
	vdup.16	d6, r0
	vmull.s16 q2, d19, d27
	vstr	d6, [sp, #224]
	vstr	d4, [sp, #392]
	vstr	d5, [sp, #400]
	vmull.s16 q3, d7, d20
	vldr	d5, [sp, #184]
	vdup.16	d30, r1
	add	r1, r7, #24
	vld1.16	{d2}, [r1]
	ldr	r5, [sp, #16]
	ldr	r1, [sp, #4]
	str	r4, [sp, #112]
	ldr	r4, [sp, #52]
	vmull.s16 q13, d19, d5
	vstr	d24, [sp, #344]
	vstr	d25, [sp, #352]
	vdup.16	d9, r5
	vdup.16	d23, r9
	vstr	d6, [sp, #312]
	vstr	d7, [sp, #320]
	vdup.16	d25, r4
	vmull.s16 q3, d31, d19
	vdup.16	d31, r1
	str	r9, [sp, #116]
	ldr	r9, [sp, #88]
	add	r3, r7, #60
	vld1.16	{d18}, [r3]
	vmull.s16 q0, d16, d3
	ldr	r0, [sp, #40]
	vstr	d9, [sp, #216]
	vstr	d23, [sp, #152]
	vstr	d31, [sp, #200]
	vstr	d25, [sp, #232]
	vldr	d24, [sp, #128]
	vdup.16	d3, r9
	vstr	d26, [sp, #456]
	vstr	d27, [sp, #464]
	ldr	r9, [sp, #64]
	vldr	d27, [sp, #248]
	vdup.16	d5, r9
	vstr	d5, [sp, #240]
	vmull.s16 q2, d17, d27
	vldr	d27, [sp, #264]
	vmull.s16 q6, d12, d17
	vmull.s16 q11, d22, d17
	vmull.s16 q13, d17, d27
	vldr	d17, [sp, #256]
	vmull.s16 q12, d24, d2
	vstr	d4, [sp, #424]
	vstr	d5, [sp, #432]
	vmull.s16 q2, d16, d17
	vldr	d17, [sp, #272]
	vmull.s16 q7, d14, d16
	vmull.s16 q15, d16, d30
	vadd.i32	d21, d21, d25
	vmull.s16 q8, d16, d17
	vldr	d28, [sp, #280]
	vstr	d16, [sp, #184]
	vstr	d17, [sp, #192]
	vstr	d21, [sp, #280]
	vdup.16	d16, r10
	vldr	d21, [sp, #216]
	vmull.s16 q4, d8, d20
	vstr	d16, [sp, #264]
	vmull.s16 q10, d21, d18
	vadd.i32	d16, d12, d14
	vdup.16	d10, r8
	vadd.i32	d16, d16, d20
	vmull.s16 q5, d10, d19
	vadd.i32	d19, d28, d24
	vdup.16	d29, r0
	ldr	r0, [sp, #100]
	vstr	d26, [sp, #168]
	vstr	d27, [sp, #176]
	vdup.16	d27, r0
	ldr	r0, [sp, #76]
	vadd.i32	d17, d13, d15
	vdup.16	d28, r0
	vadd.i32	d13, d16, d19
	vldr	d19, [sp, #152]
	vadd.i32	d12, d17, d21
	vstr	d28, [sp, #248]
	vmull.s16 q10, d19, d2
	vadd.i32	d28, d10, d8
	vadd.i32	d17, d11, d9
	vadd.i32	d8, d28, d20
	vadd.i32	d9, d17, d21
	vldr	d20, [sp, #288]
	vldr	d21, [sp, #296]
	vldr	d17, [sp, #224]
	vadd.i32	d28, d22, d20
	vmull.s16 q12, d17, d18
	vadd.i32	d23, d23, d21
	vldr	d17, [sp, #200]
	vldr	d20, [sp, #312]
	vldr	d21, [sp, #320]
	vstr	d4, [sp, #440]
	vstr	d5, [sp, #448]
	vstr	d27, [sp, #256]
	vmov	d4, d23  @ v2si
	vadd.i32	d27, d6, d20
	vadd.i32	d23, d7, d21
	vmull.s16 q10, d17, d2
	vadd.i32	d7, d27, d20
	vstr	d20, [sp, #200]
	vstr	d21, [sp, #208]
	vldr	d20, [sp, #328]
	vldr	d21, [sp, #336]
	vadd.i32	d31, d21, d31
	str	r10, [sp, #128]
	vstr	d12, [sp, #272]
	vstr	d13, [sp, #216]
	vstr	d9, [sp, #304]
	vstr	d23, [sp, #288]
	vstr	d7, [sp, #224]
	vadd.i32	d27, d20, d30
	vstr	d31, [sp, #312]
	vldr	d20, [sp, #360]
	vldr	d21, [sp, #368]
	vldr	d22, [sp, #344]
	vldr	d23, [sp, #352]
	vldr	d17, [sp, #232]
	vadd.i32	d26, d20, d22
	vmull.s16 q6, d2, d17
	vadd.i32	d6, d21, d23
	vldr	d20, [sp, #376]
	vldr	d21, [sp, #384]
	vldr	d30, [sp, #392]
	vldr	d31, [sp, #400]
	vadd.i32	d22, d26, d12
	vldr	d19, [sp, #248]
	vadd.i32	d26, d0, d20
	vadd.i32	d23, d1, d21
	vldr	d20, [sp, #408]
	vldr	d21, [sp, #416]
	vldr	d17, [sp, #240]
	vadd.i32	d7, d20, d30
	vadd.i32	d31, d21, d31
	vmull.s16 q10, d2, d19
	vldr	d0, [sp, #440]
	vldr	d1, [sp, #448]
	vstr	d20, [sp, #152]
	vstr	d21, [sp, #160]
	vmov	d5, d8  @ v2si
	vldr	d20, [sp, #424]
	vldr	d21, [sp, #432]
	vmull.s16 q4, d2, d17
	vldr	d17, [sp, #256]
	vstr	d22, [sp, #232]
	vadd.i32	d22, d0, d20
	vadd.i32	d20, d1, d21
	vmull.s16 q0, d18, d17
	vldr	d17, [sp, #264]
	vmull.s16 q5, d18, d3
	vmull.s16 q7, d29, d18
	vldr	d2, [sp, #456]
	vldr	d3, [sp, #464]
	vmull.s16 q9, d18, d17
	vldr	d17, [sp, #136]
	vadd.i32	d30, d17, d2
	vldr	d17, [sp, #144]
	vadd.i32	d28, d28, d24
	vadd.i32	d29, d17, d3
	vldr	d17, [sp, #152]
	vldr	d3, [sp, #168]
	vldr	d24, [sp, #288]
	vadd.i32	d30, d30, d17
	vadd.i32	d28, d5, d28
	vldr	d17, [sp, #184]
	vldr	d5, [sp, #208]
	vadd.i32	d7, d7, d8
	vadd.i32	d5, d24, d5
	vadd.i32	d21, d17, d3
	vldr	d24, [sp, #224]
	vldr	d3, [sp, #176]
	vldr	d17, [sp, #192]
	vadd.i32	d27, d27, d14
	vadd.i32	d22, d22, d0
	vadd.i32	d17, d17, d3
	vadd.i32	d27, d24, d27
	vadd.i32	d22, d7, d22
	vldr	d24, [sp, #312]
	vldr	d7, [sp, #160]
	vadd.i32	d31, d31, d9
	vadd.i32	d25, d4, d25
	vldr	d9, [sp, #304]
	vldr	d4, [sp, #232]
	vadd.i32	d6, d6, d13
	vadd.i32	d26, d26, d10
	vadd.i32	d23, d23, d11
	vadd.i32	d17, d17, d19
	vadd.i32	d21, d21, d18
	vadd.i32	d24, d24, d15
	vadd.i32	d20, d20, d1
	vadd.i32	d29, d29, d7
	vldr	d19, [sp, #272]
	vldr	d18, [sp, #280]
	vldr	d13, [sp, #216]
	str	r2, [sp, #200]
	ldrsh	r4, [r7, #20]
	ldrsh	r5, [r7, #56]
	ldr	r2, [sp, #12]
	ldr	r0, [sp, #24]
	mul	fp, lr, r4
	vmov.i32	d16, #0xd  @ v2si
	vadd.i32	d25, d9, d25
	str	lr, [sp, #152]
	str	ip, [sp, #184]
	mul	lr, r2, r5
	mul	r10, r4, ip
	ldrsh	r2, [r7, #8]
	mul	ip, r5, r0
	vadd.i32	d26, d4, d26
	ldr	r0, [sp, #124]
	vadd.i32	d23, d6, d23
	vadd.i32	d24, d5, d24
	vadd.i32	d29, d29, d17
	vadd.i32	d21, d30, d21
	vadd.i32	d20, d31, d20
	ldrsh	r3, [r7, #44]
	mul	r9, r4, r0
	str	r6, [sp, #136]
	ldr	r0, [sp, #36]
	mla	fp, r6, r2, fp
	ldr	r6, [sp, #8]
	mul	r0, r5, r0
	mla	lr, r6, r3, lr
	ldr	r6, [sp, #120]
	str	r8, [sp, #168]
	mla	r9, r2, r6, r9
	ldr	r6, [sp, #32]
	mla	r10, r2, r8, r10
	mla	r0, r3, r6, r0
	ldr	r8, [sp, #20]
	ldr	r6, [sp, #48]
	mla	ip, r3, r8, ip
	mul	r8, r4, r6
	ldr	r6, [sp, #44]
	vadd.i32	d4, d19, d18
	mla	r8, r2, r6, r8
	ldr	r6, [sp, #84]
	str	lr, [sp, #216]
	mul	r1, r5, r6
	ldr	r6, [sp, #80]
	vadd.i32	d28, d28, d16
	mla	r1, r3, r6, r1
	str	r1, [sp, #232]
	ldr	r1, [sp, #60]
	vadd.i32	d25, d25, d16
	mul	r1, r4, r1
	mov	lr, r1
	vadd.i32	d26, d26, d16
	vadd.i32	d23, d23, d16
	vadd.i32	d27, d27, d16
	vadd.i32	d22, d22, d16
	vadd.i32	d21, d21, d16
	vadd.i32	d24, d24, d16
	vadd.i32	d20, d20, d16
	vadd.i32	d29, d29, d16
	vadd.i32	d3, d13, d16
	vadd.i32	d4, d4, d16
	ldr	r1, [sp, #72]
	vshr.s32	d8, d28, #14
	mul	r4, r4, r1
	ldr	r1, [sp, #56]
	vshr.s32	d9, d25, #14
	mla	lr, r2, r1, lr
	ldr	r1, [sp, #68]
	vshr.s32	d18, d26, #14
	vshr.s32	d19, d23, #14
	mla	r4, r2, r1, r4
	ldr	r2, [sp, #96]
	vshr.s32	d10, d27, #14
	vshr.s32	d30, d22, #14
	vshr.s32	d6, d21, #14
	vshr.s32	d11, d24, #14
	vshr.s32	d31, d20, #14
	vshr.s32	d7, d29, #14
	ldr	r1, [sp, #108]
	mul	r2, r5, r2
	mul	r5, r5, r1
	ldr	r1, [sp, #92]
	ldrsh	r6, [r7, #32]
	mla	r2, r3, r1, r2
	ldr	r1, [sp, #104]
	vshr.s32	d0, d3, #14
	mla	r5, r3, r1, r5
	ldr	r3, [sp, #112]
	vshr.s32	d1, d4, #14
	mla	fp, r3, r6, fp
	ldr	r3, [sp, #116]
	ldr	r1, [sp, #136]
	mla	r10, r6, r3, r10
	ldr	r3, [sp, #4]
	vmovn.i32	d8, q4
	mla	r3, r6, r3, r9
	str	r3, [sp, #224]
	ldr	r3, [sp, #52]
	vmovn.i32	d18, q9
	mla	r8, r6, r3, r8
	ldr	r3, [sp, #64]
	vmovn.i32	d30, q15
	mla	lr, r6, r3, lr
	ldr	r3, [sp, #76]
	str	lr, [sp, #240]
	mla	r4, r6, r3, r4
	ldrsh	r6, [r7, #10]
	ldrsh	r3, [r7, #68]
	mul	r9, r6, r1
	ldr	lr, [sp, #216]
	ldr	r1, [sp, #16]
	str	r9, [sp, #136]
	mla	lr, r1, r3, lr
	ldr	r1, [sp, #28]
	ldr	r9, [sp, #232]
	mla	ip, r3, r1, ip
	ldr	r1, [sp, #40]
	vmovn.i32	d6, q3
	mla	r0, r3, r1, r0
	ldr	r1, [sp, #88]
	vmovn.i32	d10, q5
	mla	r1, r3, r1, r9
	ldr	r9, [sp, #100]
	add	r1, r8, r1
	mla	r2, r3, r9, r2
	ldr	r9, [sp, #128]
	ldr	r8, [sp, #168]
	mla	r3, r3, r9, r5
	ldr	r5, [sp, #224]
	add	r3, r4, r3
	add	r0, r5, r0
	ldr	r5, [sp, #240]
	ldr	r4, [sp, #8]
	add	r2, r5, r2
	ldrsh	r5, [r7, #46]
	mul	r9, r6, r8
	add	lr, fp, lr
	ldr	r8, [sp, #20]
	mul	fp, r5, r4
	vmovn.i32	d0, q0
	mul	r8, r5, r8
	ldr	r4, [sp, #44]
	str	fp, [sp, #8]
	add	ip, r10, ip
	ldr	fp, [sp, #32]
	ldr	r10, [sp, #120]
	str	r8, [sp, #20]
	mul	fp, r5, fp
	mul	r8, r6, r10
	mul	r10, r6, r4
	str	fp, [sp, #32]
	str	r10, [sp, #120]
	ldr	r10, [sp, #80]
	ldr	r4, [sp, #56]
	mul	r10, r5, r10
	mul	fp, r6, r4
	ldr	r4, [sp, #68]
	str	r10, [sp, #44]
	mul	r6, r6, r4
	ldr	r4, [sp, #92]
	add	r3, r3, #13
	mul	r10, r5, r4
	ldr	r4, [sp, #104]
	asr	r3, r3, #14
	mul	r5, r5, r4
	add	r4, sp, #484
	vst1.16	{d8}, [r4]
	add	lr, lr, #13
	add	r4, sp, #508
	vst1.16	{d18}, [r4]
	str	r3, [sp]
	add	r4, sp, #532
	add	r3, sp, #480
	asr	lr, lr, #14
	add	ip, ip, #13
	vst1.16	{d6}, [r4]
	vstr	d30, [sp, #520]
	vstr	d10, [sp, #496]
	asr	ip, ip, #14
	strh	lr, [r3]	@ movhi
	add	r0, r0, #13
	add	r3, sp, #492
	strh	ip, [r3]	@ movhi
	asr	r0, r0, #14
	add	ip, sp, #504
	ldrsh	r4, [r7, #22]
	strh	r0, [ip]	@ movhi
	add	r1, r1, #13
	ldr	ip, [sp, #184]
	add	r0, sp, #516
	asr	r1, r1, #14
	strh	r1, [r0]	@ movhi
	mla	r9, r4, ip, r9
	ldr	r0, [sp, #120]
	ldr	ip, [sp, #48]
	add	r2, r2, #13
	ldr	r3, [sp]
	mla	r0, r4, ip, r0
	add	r1, sp, #528
	asr	r2, r2, #14
	strh	r2, [r1]	@ movhi
	add	r2, sp, #540
	ldr	r1, [sp, #152]
	strh	r3, [r2]	@ movhi
	ldr	r2, [sp, #136]
	ldr	ip, [sp, #60]
	mla	r2, r4, r1, r2
	str	r0, [sp, #48]
	ldr	r1, [sp, #124]
	ldr	r0, [sp, #72]
	ldrsh	lr, [r7, #34]
	ldrsh	r3, [r7, #58]
	vstr	d0, [sp, #472]
	mla	r8, r4, r1, r8
	mla	fp, r4, ip, fp
	ldr	r1, [sp, #12]
	mla	r4, r4, r0, r6
	ldr	ip, [sp, #24]
	ldr	r6, [sp, #8]
	ldr	r0, [sp, #20]
	mla	r1, r3, r1, r6
	mla	r0, r3, ip, r0
	ldr	r6, [sp, #32]
	ldr	ip, [sp, #36]
	mla	ip, r3, ip, r6
	ldr	r6, [sp, #84]
	str	ip, [sp, #8]
	ldr	ip, [sp, #44]
	mla	r6, r3, r6, ip
	ldr	ip, [sp, #96]
	mla	r10, r3, ip, r10
	ldr	ip, [sp, #108]
	mla	r5, r3, ip, r5
	ldrsh	r3, [r7, #70]
	ldr	r7, [sp, #112]
	ldr	ip, [sp, #48]
	mla	r2, lr, r7, r2
	ldr	r7, [sp, #116]
	mla	r9, lr, r7, r9
	ldr	r7, [sp, #4]
	mla	r8, lr, r7, r8
	ldr	r7, [sp, #52]
	mla	r7, lr, r7, ip
	ldr	ip, [sp, #64]
	mla	fp, lr, ip, fp
	ldr	ip, [sp, #76]
	mla	r4, lr, ip, r4
	ldr	lr, [sp, #16]
	ldr	ip, [sp, #8]
	mla	r1, r3, lr, r1
	ldr	lr, [sp, #28]
	add	r2, r1, r2
	mla	r0, r3, lr, r0
	ldr	lr, [sp, #40]
	add	r2, r2, #13
	mla	ip, r3, lr, ip
	ldr	lr, [sp, #88]
	add	r9, r0, r9
	mla	r6, r3, lr, r6
	ldr	lr, [sp, #100]
	add	r7, r6, r7
	mla	r10, r3, lr, r10
	ldr	lr, [sp, #128]
	add	r6, sp, #480
	mla	r3, r3, lr, r5
	add	r6, r6, #2
	asr	r5, r2, #14
	strh	r5, [r6]	@ movhi
	add	r9, r9, #13
	add	r5, sp, #492
	add	r8, ip, r8
	asr	r9, r9, #14
	add	r5, r5, #2
	strh	r9, [r5]	@ movhi
	add	r3, r3, r4
	add	r5, sp, #504
	add	r4, r8, #13
	asr	r4, r4, #14
	add	r5, r5, #2
	strh	r4, [r5]	@ movhi
	add	lr, r7, #13
	add	r4, sp, #516
	add	fp, r10, fp
	asr	lr, lr, #14
	add	r4, r4, #2
	strh	lr, [r4]	@ movhi
	add	ip, fp, #13
	add	lr, sp, #528
	add	lr, lr, #2
	asr	ip, ip, #14
	strh	ip, [lr]	@ movhi
	add	r3, r3, #13
	add	ip, sp, #540
	ldr	r0, [sp, #200]
	asr	r3, r3, #14
	add	ip, ip, #2
	mov	r2, #72
	add	r1, sp, #472
	strh	r3, [ip]	@ movhi
	bl	memcpy
	add	sp, sp, #548
	@ sp needed
	vldm	sp!, {d8-d15}
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	dot_productM, .-dot_productM
	.align	2
	.global	T1dot_productM
	.syntax unified
	.arm
	.fpu neon
	.type	T1dot_productM, %function
T1dot_productM:
	@ args = 0, pretend = 0, frame = 504
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	vpush.64	{d8, d9, d10, d11, d12, d13, d14, d15}
	mov	r6, r1
	ldrsh	r3, [r0, #26]
	ldrsh	ip, [r0, #50]
	sub	sp, sp, #508
	ldrsh	r1, [r0, #38]
	str	r3, [sp, #8]
	str	ip, [sp, #16]
	ldrsh	r3, [r0, #62]
	ldrsh	ip, [r0, #4]
	str	r1, [sp, #12]
	str	r3, [sp, #20]
	ldrsh	r1, [r0, #16]
	ldrsh	r3, [r0, #28]
	str	ip, [sp, #24]
	ldrsh	ip, [r0, #40]
	str	r1, [sp, #28]
	str	r3, [sp, #32]
	str	ip, [sp, #36]
	ldrsh	r3, [r0, #6]
	ldrsh	ip, [r0, #64]
	ldrsh	r1, [r0, #52]
	ldrsh	r5, [r0]
	ldrsh	lr, [r0, #12]
	ldrsh	r7, [r0, #36]
	ldrsh	r4, [r0, #24]
	ldrsh	r8, [r0, #48]
	ldrsh	r9, [r0, #60]
	ldrsh	r10, [r0, #2]
	ldrsh	fp, [r0, #14]
	str	ip, [sp, #44]
	str	r3, [sp, #48]
	str	r1, [sp, #40]
	ldrsh	r1, [r0, #18]
	ldrsh	ip, [r0, #30]
	ldrsh	r3, [r0, #42]
	str	ip, [sp, #56]
	ldrsh	ip, [r0, #8]
	str	r1, [sp, #52]
	str	ip, [sp, #72]
	ldrsh	ip, [r0, #32]
	ldrsh	r1, [r0, #54]
	str	r3, [sp, #60]
	ldrsh	r3, [r0, #66]
	str	ip, [sp, #80]
	ldrsh	ip, [r0, #68]
	str	r1, [sp, #64]
	str	r3, [sp, #68]
	ldrsh	r1, [r0, #44]
	ldrsh	r3, [r0, #20]
	str	ip, [sp, #92]
	ldrsh	ip, [r0, #22]
	str	r3, [sp, #76]
	str	r1, [sp, #84]
	ldrsh	r3, [r0, #56]
	ldrsh	r1, [r0, #10]
	str	ip, [sp, #100]
	ldrsh	ip, [r0, #58]
	str	r3, [sp, #88]
	str	r1, [sp, #96]
	ldrsh	r3, [r0, #34]
	ldrsh	r1, [r0, #46]
	str	ip, [sp, #112]
	add	ip, r6, #12
	str	r3, [sp, #104]
	str	r1, [sp, #108]
	vdup.16	d14, r8
	vld1.16	{d19}, [r6]
	vld1.16	{d20}, [ip]
	mov	ip, r8
	ldr	r8, [sp, #16]
	vdup.16	d6, fp
	vdup.16	d8, r8
	mov	r8, fp
	ldr	fp, [sp, #28]
	vdup.16	d0, r5
	vdup.16	d7, fp
	ldr	fp, [sp, #24]
	vdup.16	d4, lr
	vdup.16	d31, fp
	ldr	fp, [sp, #52]
	str	r10, [sp, #124]
	vdup.16	d28, fp
	ldr	fp, [sp, #48]
	vdup.16	d22, r10
	vdup.16	d27, fp
	ldr	fp, [sp, #84]
	ldr	r10, [sp, #40]
	vdup.16	d23, fp
	ldr	fp, [sp, #88]
	vdup.16	d29, r10
	vdup.16	d24, fp
	ldr	fp, [sp, #108]
	ldr	r10, [sp, #60]
	vdup.16	d1, fp
	vdup.16	d26, r10
	ldr	r10, [sp, #76]
	add	r3, r6, #48
	vdup.16	d18, r10
	ldr	r10, [sp, #72]
	vld1.16	{d16}, [r3]
	vdup.16	d21, r10
	ldr	r10, [sp, #100]
	ldr	r3, [sp, #96]
	vdup.16	d25, r10
	ldr	r10, [sp, #112]
	vmull.s16 q2, d4, d20
	vdup.16	d2, r3
	vstr	d1, [sp, #256]
	vdup.16	d9, r10
	vmull.s16 q0, d0, d19
	add	r1, r6, #36
	vld1.16	{d17}, [r1]
	ldr	r1, [sp, #12]
	vstr	d18, [sp, #152]
	vdup.16	d10, r1
	ldr	r1, [sp, #36]
	vstr	d21, [sp, #136]
	vstr	d23, [sp, #168]
	vadd.i32	d21, d1, d5
	vstr	d24, [sp, #240]
	vstr	d25, [sp, #248]
	vstr	d2, [sp, #232]
	vstr	d9, [sp, #264]
	ldrsh	r0, [r0, #70]
	vdup.16	d24, r4
	vdup.16	d30, r1
	ldr	r1, [sp, #64]
	str	r4, [sp, #116]
	vldr	d5, [sp, #152]
	vstr	d24, [sp, #128]
	vadd.i32	d24, d0, d4
	vmull.s16 q2, d20, d5
	vstr	d4, [sp, #368]
	vstr	d5, [sp, #376]
	vldr	d4, [sp, #248]
	vmull.s16 q2, d20, d4
	vstr	d4, [sp, #416]
	vstr	d5, [sp, #424]
	vldr	d5, [sp, #136]
	vstr	d24, [sp, #272]
	vmull.s16 q2, d19, d5
	vmull.s16 q12, d6, d20
	vstr	d4, [sp, #352]
	vstr	d5, [sp, #360]
	vstr	d24, [sp, #280]
	vstr	d25, [sp, #288]
	vldr	d5, [sp, #232]
	vmull.s16 q12, d19, d31
	vmull.s16 q2, d19, d5
	vstr	d24, [sp, #304]
	vstr	d25, [sp, #312]
	vmull.s16 q12, d16, d29
	mov	r10, r0
	ldr	r0, [sp, #8]
	ldr	fp, [sp, #20]
	vdup.16	d6, r0
	ldr	r0, [sp, #32]
	ldr	r4, [sp, #56]
	vdup.16	d31, r0
	ldr	r0, [sp, #44]
	vstr	d4, [sp, #136]
	vstr	d5, [sp, #144]
	vdup.16	d29, r0
	ldr	r0, [sp, #80]
	vdup.16	d11, r9
	vdup.16	d23, fp
	vstr	d24, [sp, #320]
	vstr	d25, [sp, #328]
	vdup.16	d5, r0
	vmull.s16 q12, d19, d27
	vdup.16	d27, r4
	vdup.16	d3, r1
	add	r3, r6, #60
	add	r1, r6, #24
	vld1.16	{d2}, [r1]
	vld1.16	{d18}, [r3]
	vstr	d24, [sp, #336]
	vstr	d25, [sp, #344]
	str	r9, [sp, #120]
	vstr	d11, [sp, #184]
	ldr	r9, [sp, #68]
	vstr	d23, [sp, #200]
	vstr	d6, [sp, #192]
	vmull.s16 q11, d22, d19
	vstr	d31, [sp, #208]
	vstr	d29, [sp, #216]
	vstr	d27, [sp, #224]
	vldr	d24, [sp, #128]
	vstr	d5, [sp, #232]
	vldr	d19, [sp, #272]
	vldr	d5, [sp, #168]
	vmull.s16 q2, d17, d5
	vdup.16	d12, r7
	vstr	d4, [sp, #384]
	vstr	d5, [sp, #392]
	vldr	d5, [sp, #256]
	vmull.s16 q6, d12, d17
	vmull.s16 q13, d17, d26
	vmull.s16 q5, d10, d17
	vmull.s16 q15, d17, d30
	vmull.s16 q2, d17, d5
	vldr	d17, [sp, #240]
	vstr	d4, [sp, #152]
	vstr	d5, [sp, #160]
	vmull.s16 q2, d16, d17
	vldr	d17, [sp, #264]
	vmull.s16 q4, d8, d16
	vmull.s16 q0, d16, d3
	vmull.s16 q7, d14, d16
	vmull.s16 q8, d16, d17
	vdup.16	d3, r9
	ldr	r9, [sp, #92]
	vmull.s16 q12, d24, d2
	vstr	d16, [sp, #168]
	vstr	d17, [sp, #176]
	vdup.16	d16, r9
	vadd.i32	d25, d21, d25
	vstr	d16, [sp, #240]
	vldr	d21, [sp, #184]
	vdup.16	d16, r10
	vmull.s16 q14, d20, d28
	vmull.s16 q3, d20, d7
	vadd.i32	d17, d13, d15
	vmull.s16 q10, d21, d18
	vstr	d16, [sp, #256]
	vadd.i32	d16, d12, d14
	vadd.i32	d19, d19, d24
	vadd.i32	d12, d17, d21
	vadd.i32	d16, d16, d20
	vldr	d21, [sp, #200]
	vadd.i32	d13, d16, d19
	vmull.s16 q10, d21, d18
	vadd.i32	d19, d11, d9
	vadd.i32	d17, d10, d8
	vadd.i32	d21, d19, d21
	vadd.i32	d8, d17, d20
	vldr	d19, [sp, #192]
	vstr	d21, [sp, #296]
	vldr	d20, [sp, #280]
	vldr	d21, [sp, #288]
	ldr	r4, [sp, #104]
	vstr	d4, [sp, #400]
	vstr	d5, [sp, #408]
	vadd.i32	d17, d22, d20
	vdup.16	d5, r4
	vadd.i32	d22, d23, d21
	vstr	d25, [sp, #272]
	vldr	d20, [sp, #304]
	vldr	d21, [sp, #312]
	vmull.s16 q12, d19, d2
	vldr	d19, [sp, #208]
	vadd.i32	d23, d17, d24
	vstr	d5, [sp, #248]
	vadd.i32	d17, d6, d20
	vmull.s16 q2, d2, d19
	vadd.i32	d7, d7, d21
	vldr	d20, [sp, #320]
	vldr	d21, [sp, #328]
	vadd.i32	d6, d17, d4
	vadd.i32	d31, d21, d31
	str	r10, [sp, #128]
	vstr	d12, [sp, #264]
	vstr	d13, [sp, #184]
	vstr	d8, [sp, #200]
	vstr	d22, [sp, #280]
	vstr	d23, [sp, #192]
	vstr	d7, [sp, #304]
	vstr	d6, [sp, #208]
	vstr	d31, [sp, #320]
	vldr	d19, [sp, #216]
	vadd.i32	d17, d20, d30
	vmull.s16 q7, d18, d19
	vldr	d20, [sp, #336]
	vldr	d21, [sp, #344]
	vldr	d19, [sp, #224]
	vadd.i32	d9, d17, d14
	vmull.s16 q6, d2, d19
	vadd.i32	d17, d28, d20
	vmull.s16 q5, d18, d3
	vadd.i32	d6, d29, d21
	vadd.i32	d29, d17, d12
	vadd.i32	d17, d0, d26
	vldr	d20, [sp, #368]
	vldr	d21, [sp, #376]
	vldr	d30, [sp, #352]
	vldr	d31, [sp, #360]
	vadd.i32	d26, d17, d10
	vldr	d17, [sp, #232]
	vstr	d9, [sp, #216]
	vadd.i32	d23, d1, d27
	vmull.s16 q4, d2, d17
	vldr	d0, [sp, #400]
	vldr	d1, [sp, #408]
	vldr	d17, [sp, #240]
	vadd.i32	d7, d20, d30
	vadd.i32	d31, d21, d31
	vldr	d20, [sp, #384]
	vldr	d21, [sp, #392]
	vstr	d29, [sp, #224]
	vldr	d19, [sp, #248]
	vldr	d28, [sp, #416]
	vldr	d29, [sp, #424]
	vadd.i32	d22, d0, d20
	vadd.i32	d20, d1, d21
	vmull.s16 q0, d18, d17
	vldr	d21, [sp, #144]
	vldr	d17, [sp, #256]
	vmull.s16 q1, d2, d19
	vldr	d30, [sp, #136]
	vmull.s16 q9, d18, d17
	vadd.i32	d29, d29, d21
	vldr	d17, [sp, #168]
	vldr	d21, [sp, #152]
	vadd.i32	d30, d28, d30
	vadd.i32	d21, d17, d21
	vldr	d28, [sp, #160]
	vldr	d17, [sp, #176]
	vldr	d27, [sp, #200]
	vadd.i32	d17, d17, d28
	vldr	d28, [sp, #192]
	vldr	d24, [sp, #304]
	vadd.i32	d28, d27, d28
	vldr	d27, [sp, #280]
	vadd.i32	d5, d24, d5
	vadd.i32	d25, d27, d25
	vldr	d24, [sp, #208]
	vldr	d27, [sp, #216]
	vldr	d4, [sp, #224]
	vadd.i32	d21, d21, d18
	vadd.i32	d17, d17, d19
	vldr	d18, [sp, #272]
	vldr	d19, [sp, #264]
	vadd.i32	d27, d24, d27
	vldr	d24, [sp, #320]
	vadd.i32	d26, d4, d26
	vadd.i32	d4, d19, d18
	vldr	d18, [sp, #296]
	vadd.i32	d6, d6, d13
	vadd.i32	d23, d23, d11
	vadd.i32	d30, d30, d2
	vadd.i32	d29, d29, d3
	vadd.i32	d7, d7, d8
	vadd.i32	d31, d31, d9
	vadd.i32	d22, d22, d0
	vadd.i32	d24, d24, d15
	vadd.i32	d20, d20, d1
	vldr	d13, [sp, #184]
	str	r2, [sp, #200]
	ldrsh	r2, [r6, #20]
	ldrsh	r3, [r6, #56]
	str	lr, [sp, #152]
	mul	fp, lr, r2
	str	r8, [sp, #192]
	mul	lr, ip, r3
	mul	r10, r2, r8
	ldr	r8, [sp, #16]
	ldrsh	r0, [r6, #44]
	str	ip, [sp, #184]
	mul	ip, r3, r8
	vmov.i32	d16, #0xd  @ v2si
	vadd.i32	d25, d18, d25
	mla	lr, r7, r0, lr
	ldr	r8, [sp, #40]
	str	r7, [sp, #168]
	vadd.i32	d23, d6, d23
	ldr	r7, [sp, #12]
	vadd.i32	d24, d5, d24
	vadd.i32	d17, d29, d17
	vadd.i32	d22, d7, d22
	vadd.i32	d21, d30, d21
	vadd.i32	d20, d31, d20
	mla	ip, r0, r7, ip
	mul	r8, r3, r8
	ldr	r7, [sp, #52]
	ldr	r1, [sp, #36]
	mul	r7, r2, r7
	ldrsh	r4, [r6, #8]
	ldr	r9, [sp, #28]
	mla	r8, r0, r1, r8
	ldr	r1, [sp, #48]
	mla	fp, r5, r4, fp
	str	r5, [sp, #136]
	mla	r7, r4, r1, r7
	ldr	r5, [sp, #124]
	ldr	r1, [sp, #64]
	mul	r9, r2, r9
	mla	r10, r4, r5, r10
	mul	r1, r3, r1
	ldr	r5, [sp, #24]
	str	lr, [sp, #216]
	mla	r9, r4, r5, r9
	ldr	r5, [sp, #60]
	vadd.i32	d28, d28, d16
	mla	r1, r0, r5, r1
	str	r1, [sp, #224]
	ldr	r1, [sp, #76]
	vadd.i32	d25, d25, d16
	mul	r1, r2, r1
	mov	lr, r1
	vadd.i32	d26, d26, d16
	vadd.i32	d23, d23, d16
	vadd.i32	d27, d27, d16
	vadd.i32	d22, d22, d16
	vadd.i32	d21, d21, d16
	vadd.i32	d24, d24, d16
	vadd.i32	d20, d20, d16
	vadd.i32	d17, d17, d16
	vadd.i32	d3, d13, d16
	vadd.i32	d4, d4, d16
	ldr	r1, [sp, #100]
	vshr.s32	d8, d28, #14
	mul	r2, r2, r1
	ldr	r1, [sp, #72]
	vshr.s32	d9, d25, #14
	mla	lr, r4, r1, lr
	ldr	r1, [sp, #96]
	vshr.s32	d18, d26, #14
	mla	r4, r4, r1, r2
	ldr	r2, [sp, #88]
	ldr	r1, [sp, #112]
	mul	r2, r3, r2
	mul	r3, r3, r1
	ldr	r1, [sp, #84]
	vshr.s32	d19, d23, #14
	mla	r2, r0, r1, r2
	ldr	r1, [sp, #108]
	vshr.s32	d10, d27, #14
	vshr.s32	d30, d22, #14
	vshr.s32	d6, d21, #14
	vshr.s32	d11, d24, #14
	vshr.s32	d31, d20, #14
	vshr.s32	d7, d17, #14
	ldrsh	r5, [r6, #32]
	mla	r0, r0, r1, r3
	ldr	r3, [sp, #116]
	vshr.s32	d0, d3, #14
	mla	r3, r3, r5, fp
	str	r3, [sp, #208]
	ldr	r3, [sp, #8]
	vshr.s32	d1, d4, #14
	mla	r10, r5, r3, r10
	ldr	r3, [sp, #32]
	ldr	fp, [sp, #104]
	mla	r9, r5, r3, r9
	ldr	r3, [sp, #56]
	ldr	r1, [sp, #136]
	mla	r7, r5, r3, r7
	ldr	r3, [sp, #80]
	vmovn.i32	d8, q4
	mla	lr, r5, r3, lr
	mla	r5, r5, fp, r4
	ldrsh	r4, [r6, #10]
	str	lr, [sp, #232]
	mul	lr, r1, r4
	ldrsh	r3, [r6, #68]
	ldr	r1, [sp, #120]
	str	lr, [sp, #240]
	ldr	lr, [sp, #216]
	ldr	fp, [sp, #224]
	mla	lr, r1, r3, lr
	ldr	r1, [sp, #20]
	vmovn.i32	d18, q9
	mla	ip, r3, r1, ip
	ldr	r1, [sp, #44]
	vmovn.i32	d30, q15
	mla	r8, r3, r1, r8
	ldr	r1, [sp, #68]
	vmovn.i32	d6, q3
	mla	r1, r3, r1, fp
	ldr	fp, [sp, #92]
	vmovn.i32	d10, q5
	mla	r2, r3, fp, r2
	ldr	fp, [sp, #128]
	add	ip, r10, ip
	mla	r3, r3, fp, r0
	ldr	fp, [sp, #208]
	ldr	r10, [sp, #232]
	add	lr, fp, lr
	add	r1, r7, r1
	ldrsh	fp, [r6, #46]
	ldr	r7, [sp, #168]
	add	r2, r10, r2
	mul	r10, r7, fp
	ldr	r7, [sp, #12]
	add	r0, r9, r8
	add	r3, r5, r3
	mul	r9, r7, fp
	ldr	r5, [sp, #124]
	ldr	r7, [sp, #48]
	str	r10, [sp, #136]
	mul	r10, r5, r4
	ldr	r5, [sp, #24]
	vmovn.i32	d0, q0
	str	r9, [sp, #12]
	mul	r8, r7, r4
	mul	r9, r5, r4
	ldr	r7, [sp, #60]
	ldr	r5, [sp, #36]
	mul	r7, fp, r7
	mul	r5, r5, fp
	str	r7, [sp, #36]
	str	r5, [sp, #24]
	ldr	r7, [sp, #72]
	ldr	r5, [sp, #96]
	mul	r7, r4, r7
	mul	r4, r4, r5
	ldr	r5, [sp, #84]
	add	r3, r3, #13
	mul	r5, fp, r5
	str	r5, [sp, #48]
	ldr	r5, [sp, #108]
	add	r2, r2, #13
	mul	fp, fp, r5
	asr	r5, r3, #14
	add	r3, sp, #444
	vst1.16	{d8}, [r3]
	asr	r2, r2, #14
	add	r3, sp, #468
	add	lr, lr, #13
	vst1.16	{d18}, [r3]
	str	r2, [sp, #4]
	add	r3, sp, #492
	add	r2, sp, #440
	asr	lr, lr, #14
	add	ip, ip, #13
	vst1.16	{d6}, [r3]
	vstr	d30, [sp, #480]
	vstr	d10, [sp, #456]
	asr	ip, ip, #14
	strh	lr, [r2]	@ movhi
	add	r0, r0, #13
	add	r2, sp, #452
	strh	ip, [r2]	@ movhi
	asr	r0, r0, #14
	add	ip, sp, #464
	add	r1, r1, #13
	strh	r0, [ip]	@ movhi
	asr	r1, r1, #14
	add	r0, sp, #476
	ldrsh	r3, [r6, #22]
	strh	r1, [r0]	@ movhi
	ldr	r0, [sp, #192]
	ldr	r2, [sp, #4]
	add	r1, sp, #488
	mla	r10, r0, r3, r10
	ldr	r0, [sp, #28]
	strh	r2, [r1]	@ movhi
	add	r1, sp, #500
	strh	r5, [r1]	@ movhi
	mla	r9, r0, r3, r9
	ldr	r5, [sp, #240]
	ldr	r0, [sp, #52]
	ldr	r1, [sp, #152]
	mla	r8, r0, r3, r8
	mla	r1, r1, r3, r5
	ldr	r0, [sp, #76]
	ldr	r5, [sp, #100]
	ldrsh	r2, [r6, #58]
	ldr	ip, [sp, #184]
	mla	r7, r3, r0, r7
	mla	r3, r3, r5, r4
	ldr	r5, [sp, #136]
	ldrsh	lr, [r6, #34]
	mla	r0, ip, r2, r5
	vstr	d0, [sp, #432]
	ldr	ip, [sp, #16]
	ldr	r5, [sp, #12]
	ldr	r4, [sp, #24]
	mla	r5, ip, r2, r5
	ldr	ip, [sp, #40]
	str	r5, [sp, #12]
	mla	r5, ip, r2, r4
	ldr	r4, [sp, #36]
	ldr	ip, [sp, #64]
	mla	ip, r2, ip, r4
	ldr	r4, [sp, #88]
	str	ip, [sp, #16]
	ldr	ip, [sp, #48]
	mla	r4, r2, r4, ip
	ldr	ip, [sp, #112]
	mla	r2, r2, ip, fp
	ldrsh	fp, [r6, #70]
	ldr	r6, [sp, #116]
	ldr	ip, [sp, #12]
	mla	r1, r6, lr, r1
	ldr	r6, [sp, #8]
	mla	r10, r6, lr, r10
	ldr	r6, [sp, #32]
	mla	r9, r6, lr, r9
	ldr	r6, [sp, #56]
	mla	r8, lr, r6, r8
	ldr	r6, [sp, #80]
	mla	r7, lr, r6, r7
	ldr	r6, [sp, #104]
	mla	r3, lr, r6, r3
	ldr	lr, [sp, #120]
	mla	r0, lr, fp, r0
	ldr	lr, [sp, #20]
	add	r1, r0, r1
	mla	r6, lr, fp, ip
	ldr	lr, [sp, #44]
	ldr	ip, [sp, #16]
	mla	r5, lr, fp, r5
	ldr	lr, [sp, #68]
	add	r6, r6, r10
	mla	ip, fp, lr, ip
	ldr	lr, [sp, #92]
	add	r5, r5, r9
	mla	r4, fp, lr, r4
	ldr	lr, [sp, #128]
	add	r6, r6, #13
	mla	r2, fp, lr, r2
	add	r1, r1, #13
	add	r3, r2, r3
	add	r2, r5, #13
	asr	r5, r6, #14
	add	r6, sp, #440
	add	r4, r4, r7
	add	r6, r6, #2
	asr	r7, r1, #14
	strh	r7, [r6]	@ movhi
	add	r6, sp, #452
	add	r6, r6, #2
	add	ip, ip, r8
	strh	r5, [r6]	@ movhi
	add	r5, sp, #464
	add	lr, ip, #13
	add	r5, r5, #2
	add	ip, r4, #13
	asr	r4, r2, #14
	strh	r4, [r5]	@ movhi
	add	r4, sp, #476
	asr	lr, lr, #14
	add	r4, r4, #2
	strh	lr, [r4]	@ movhi
	add	lr, sp, #488
	add	lr, lr, #2
	asr	ip, ip, #14
	strh	ip, [lr]	@ movhi
	add	r3, r3, #13
	add	ip, sp, #500
	asr	r3, r3, #14
	add	ip, ip, #2
	ldr	r0, [sp, #200]
	mov	r2, #72
	add	r1, sp, #432
	strh	r3, [ip]	@ movhi
	bl	memcpy
	add	sp, sp, #508
	@ sp needed
	vldm	sp!, {d8-d15}
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	T1dot_productM, .-T1dot_productM
	.align	2
	.global	T2dot_productM
	.syntax unified
	.arm
	.fpu neon
	.type	T2dot_productM, %function
T2dot_productM:
	@ args = 0, pretend = 0, frame = 184
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	mov	r6, r1
	sub	sp, sp, #188
	add	r3, r1, #72
	str	r3, [sp, #100]
	add	r3, r0, #72
	str	r3, [sp, #92]
	add	r3, sp, #112
	str	r0, [sp, #104]
	str	r2, [sp, #108]
	str	r3, [sp, #16]
.L29:
	ldrsh	r3, [r6]
	str	r3, [sp, #20]
	ldrsh	r3, [r6, #12]
	str	r3, [sp, #24]
	ldrsh	r3, [r6, #24]
	str	r3, [sp, #28]
	ldrsh	r3, [r6, #2]
	str	r3, [sp, #32]
	ldrsh	r3, [r6, #14]
	str	r3, [sp, #36]
	ldrsh	r3, [r6, #26]
	str	r3, [sp, #40]
	ldrsh	r3, [r6, #4]
	str	r3, [sp, #44]
	ldrsh	r3, [r6, #16]
	str	r3, [sp, #48]
	ldrsh	r3, [r6, #28]
	str	r3, [sp, #52]
	ldrsh	r3, [r6, #6]
	str	r3, [sp, #56]
	ldrsh	r3, [r6, #18]
	str	r3, [sp, #60]
	ldrsh	r3, [r6, #30]
	str	r3, [sp, #64]
	ldrsh	r3, [r6, #8]
	str	r3, [sp, #68]
	ldrsh	r3, [r6, #20]
	str	r3, [sp, #72]
	ldrsh	r3, [r6, #32]
	str	r3, [sp, #76]
	ldrsh	r3, [r6, #10]
	str	r3, [sp, #80]
	ldrsh	r3, [r6, #22]
	ldr	r2, [sp, #16]
	str	r3, [sp, #84]
	add	r1, r2, #4
	ldrsh	r3, [r6, #34]
	stm	sp, {r1, r2}
	str	r3, [sp, #88]
	add	r10, r2, #2
	ldr	r3, [sp, #104]
	str	r6, [sp, #96]
	str	r10, [sp, #8]
.L30:
	ldrsh	r7, [r3, #2]
	ldrsh	r6, [r3, #14]
	ldrsh	r5, [r3, #26]
	ldr	r2, [sp, #32]
	ldr	r10, [sp, #40]
	mul	r4, r7, r2
	mul	lr, r2, r6
	mul	ip, r2, r5
	ldr	r2, [sp, #36]
	ldrsh	r9, [r3]
	mul	r0, r7, r2
	mul	r1, r6, r2
	mul	r2, r5, r2
	ldrsh	r8, [r3, #12]
	ldrsh	fp, [r3, #24]
	mul	r7, r7, r10
	mul	r6, r6, r10
	mul	r5, r5, r10
	ldr	r10, [sp, #20]
	str	r2, [sp, #12]
	mla	r4, r9, r10, r4
	ldr	r2, [sp, #28]
	mla	lr, r10, r8, lr
	mla	ip, r10, fp, ip
	ldr	r10, [sp, #24]
	mla	r7, r9, r2, r7
	mla	r0, r9, r10, r0
	mov	r9, r10
	mla	r1, r8, r10, r1
	mov	r10, r2
	mla	r6, r8, r2, r6
	ldr	r2, [sp, #12]
	ldrsh	r8, [r3, #16]
	mla	r2, fp, r9, r2
	mla	r5, fp, r10, r5
	ldrsh	r9, [r3, #4]
	ldrsh	fp, [r3, #28]
	ldr	r10, [sp, #44]
	str	r2, [sp, #12]
	mla	r4, r9, r10, r4
	ldr	r2, [sp, #52]
	mla	lr, r10, r8, lr
	mla	ip, r10, fp, ip
	ldr	r10, [sp, #48]
	mla	r7, r9, r2, r7
	mla	r0, r9, r10, r0
	mov	r9, r10
	mla	r1, r8, r10, r1
	mov	r10, r2
	mla	r6, r8, r2, r6
	ldr	r2, [sp, #12]
	ldrsh	r8, [r3, #18]
	mla	r2, fp, r9, r2
	mla	r5, fp, r10, r5
	ldrsh	r9, [r3, #6]
	ldrsh	fp, [r3, #30]
	ldr	r10, [sp, #56]
	str	r2, [sp, #12]
	mla	r4, r9, r10, r4
	ldr	r2, [sp, #64]
	mla	lr, r10, r8, lr
	mla	ip, r10, fp, ip
	ldr	r10, [sp, #60]
	mla	r7, r9, r2, r7
	mla	r0, r9, r10, r0
	mov	r9, r10
	mla	r1, r8, r10, r1
	mov	r10, r2
	mla	r6, r8, r2, r6
	ldr	r2, [sp, #12]
	mla	r5, fp, r10, r5
	mla	r2, fp, r9, r2
	ldrsh	r9, [r3, #8]
	str	r2, [sp, #12]
	ldrsh	r8, [r3, #20]
	ldrsh	fp, [r3, #32]
	ldr	r10, [sp, #68]
	ldr	r2, [sp, #76]
	mla	r4, r9, r10, r4
	mla	lr, r10, r8, lr
	mla	ip, r10, fp, ip
	ldr	r10, [sp, #72]
	add	r3, r3, #36
	mla	r0, r9, r10, r0
	mla	r9, r9, r2, r7
	mov	r7, r10
	mla	r1, r8, r10, r1
	mov	r10, r2
	mla	r8, r8, r2, r6
	ldr	r2, [sp, #12]
	ldrsh	r6, [r3, #-14]
	mla	r2, fp, r7, r2
	mla	r5, fp, r10, r5
	ldrsh	r7, [r3, #-26]
	ldrsh	fp, [r3, #-2]
	ldr	r10, [sp, #80]
	str	r2, [sp, #12]
	mla	r4, r7, r10, r4
	ldr	r2, [sp, #88]
	mla	lr, r10, r6, lr
	mla	ip, r10, fp, ip
	ldr	r10, [sp, #84]
	add	ip, ip, #13
	mla	r0, r7, r10, r0
	mla	r7, r7, r2, r9
	mov	r9, r10
	mla	r1, r6, r10, r1
	mov	r10, r2
	mla	r6, r6, r2, r8
	ldr	r2, [sp, #12]
	ldr	r8, [sp, #92]
	mla	r2, fp, r9, r2
	cmp	r8, r3
	ldr	r8, [sp, #4]
	asr	ip, ip, #14
	mla	r5, fp, r10, r5
	strh	ip, [r8, #24]	@ movhi
	add	ip, r8, #36
	add	r4, r4, #13
	add	lr, lr, #13
	add	r2, r2, #13
	str	ip, [sp, #4]
	ldr	ip, [sp, #8]
	asr	r2, r2, #14
	asr	r4, r4, #14
	asr	lr, lr, #14
	strh	r4, [r8]	@ movhi
	strh	lr, [r8, #12]	@ movhi
	add	r0, r0, #13
	strh	r2, [ip, #24]	@ movhi
	add	r7, r7, #13
	ldr	r2, [sp]
	add	r1, r1, #13
	add	r6, r6, #13
	add	r5, r5, #13
	asr	r1, r1, #14
	asr	r0, r0, #14
	asr	r7, r7, #14
	asr	r6, r6, #14
	asr	r5, r5, #14
	strh	r1, [ip, #12]	@ movhi
	strh	r0, [ip]	@ movhi
	add	r1, ip, #36
	strh	r7, [r2]	@ movhi
	strh	r6, [r2, #12]	@ movhi
	strh	r5, [r2, #24]	@ movhi
	add	r2, r2, #36
	str	r1, [sp, #8]
	str	r2, [sp]
	bne	.L30
	ldr	r6, [sp, #96]
	ldr	r3, [sp, #100]
	add	r6, r6, #36
	cmp	r3, r6
	ldr	r3, [sp, #16]
	add	r3, r3, #6
	str	r3, [sp, #16]
	bne	.L29
	add	r1, sp, #112
	ldr	r0, [sp, #108]
	mov	r2, #72
	bl	memcpy
	add	sp, sp, #188
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
	.size	T2dot_productM, .-T2dot_productM
	.align	2
	.global	transposeM
	.syntax unified
	.arm
	.fpu neon
	.type	transposeM, %function
transposeM:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r3, r0
	push	{r4, lr}
	ldrh	ip, [r0, #12]
	ldrh	lr, [r0]
	ldrh	r2, [r3, #36]
	ldrh	r0, [r0, #24]
	sub	sp, sp, #72
	strh	lr, [sp]	@ movhi
	strh	ip, [sp, #2]	@ movhi
	ldrh	lr, [r3, #48]
	ldrh	ip, [r3, #60]
	strh	r0, [sp, #4]	@ movhi
	strh	r2, [sp, #6]	@ movhi
	ldrh	r0, [r3, #2]
	ldrh	r2, [r3, #14]
	strh	lr, [sp, #8]	@ movhi
	strh	ip, [sp, #10]	@ movhi
	ldrh	lr, [r3, #26]
	ldrh	ip, [r3, #38]
	strh	r0, [sp, #12]	@ movhi
	strh	r2, [sp, #14]	@ movhi
	ldrh	r0, [r3, #50]
	ldrh	r2, [r3, #62]
	strh	lr, [sp, #16]	@ movhi
	strh	ip, [sp, #18]	@ movhi
	ldrh	lr, [r3, #4]
	ldrh	ip, [r3, #16]
	strh	r0, [sp, #20]	@ movhi
	strh	r2, [sp, #22]	@ movhi
	ldrh	r0, [r3, #28]
	ldrh	r2, [r3, #40]
	strh	lr, [sp, #24]	@ movhi
	strh	ip, [sp, #26]	@ movhi
	strh	r0, [sp, #28]	@ movhi
	strh	r2, [sp, #30]	@ movhi
	ldrh	lr, [r3, #52]
	ldrh	ip, [r3, #64]
	ldrh	r0, [r3, #6]
	ldrh	r2, [r3, #18]
	strh	lr, [sp, #32]	@ movhi
	strh	ip, [sp, #34]	@ movhi
	ldrh	lr, [r3, #30]
	ldrh	ip, [r3, #42]
	strh	r0, [sp, #36]	@ movhi
	strh	r2, [sp, #38]	@ movhi
	ldrh	r0, [r3, #54]
	ldrh	r2, [r3, #66]
	strh	lr, [sp, #40]	@ movhi
	strh	ip, [sp, #42]	@ movhi
	ldrh	lr, [r3, #8]
	ldrh	ip, [r3, #20]
	strh	r0, [sp, #44]	@ movhi
	strh	r2, [sp, #46]	@ movhi
	ldrh	r0, [r3, #32]
	ldrh	r2, [r3, #44]
	strh	lr, [sp, #48]	@ movhi
	strh	ip, [sp, #50]	@ movhi
	ldrh	lr, [r3, #56]
	ldrh	ip, [r3, #68]
	strh	r0, [sp, #52]	@ movhi
	strh	r2, [sp, #54]	@ movhi
	ldrh	r0, [r3, #10]
	ldrh	r2, [r3, #22]
	strh	lr, [sp, #56]	@ movhi
	strh	ip, [sp, #58]	@ movhi
	strh	r0, [sp, #60]	@ movhi
	strh	r2, [sp, #62]	@ movhi
	ldrh	r4, [r3, #34]
	ldrh	lr, [r3, #46]
	ldrh	ip, [r3, #58]
	ldrh	r3, [r3, #70]
	mov	r0, r1
	mov	r2, #72
	mov	r1, sp
	strh	r4, [sp, #64]	@ movhi
	strh	lr, [sp, #66]	@ movhi
	strh	ip, [sp, #68]	@ movhi
	strh	r3, [sp, #70]	@ movhi
	bl	memcpy
	add	sp, sp, #72
	@ sp needed
	pop	{r4, pc}
	.size	transposeM, .-transposeM
	.align	2
	.global	print_matrix2
	.syntax unified
	.arm
	.fpu neon
	.type	print_matrix2, %function
print_matrix2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movw	r4, #:lower16:.LC0
	mov	r5, r0
	movt	r4, #:upper16:.LC0
	ldrsh	r1, [r5]
	mov	r0, r4
	bl	printf
	ldrsh	r1, [r5, #2]
	mov	r0, r4
	bl	printf
	mov	r0, #10
	bl	putchar
	ldrsh	r1, [r5, #4]
	mov	r0, r4
	bl	printf
	ldrsh	r1, [r5, #6]
	mov	r0, r4
	bl	printf
	mov	r0, #10
	bl	putchar
	pop	{r4, r5, r6, lr}
	mov	r0, #10
	b	putchar
	.size	print_matrix2, .-print_matrix2
	.align	2
	.global	print_matrixM
	.syntax unified
	.arm
	.fpu neon
	.type	print_matrixM, %function
print_matrixM:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	movw	r6, #:lower16:.LC0
	add	r5, r0, #10
	add	r7, r0, #82
	movt	r6, #:upper16:.LC0
.L39:
	sub	r4, r5, #12
.L40:
	ldrsh	r1, [r4, #2]!
	mov	r0, r6
	bl	printf
	cmp	r4, r5
	bne	.L40
	add	r5, r4, #12
	mov	r0, #10
	bl	putchar
	cmp	r5, r7
	bne	.L39
	pop	{r4, r5, r6, r7, r8, lr}
	mov	r0, #10
	b	putchar
	.size	print_matrixM, .-print_matrixM
	.align	2
	.global	print_descaled
	.syntax unified
	.arm
	.fpu neon
	.type	print_descaled, %function
print_descaled:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	movw	r6, #:lower16:.LC1
	vpush.64	{d8}
	vldr.64	d8, .L50
	add	r5, r0, #10
	add	r7, r0, #82
	movt	r6, #:upper16:.LC1
.L45:
	sub	r4, r5, #12
.L46:
	ldrsh	r3, [r4, #2]!
	mov	r0, r6
	vmov	s15, r3	@ int
	vcvt.f64.s32	d16, s15
	vmul.f64	d16, d16, d8
	vmov	r2, r3, d16
	bl	printf
	cmp	r4, r5
	bne	.L46
	add	r5, r4, #12
	mov	r0, #10
	bl	putchar
	cmp	r5, r7
	bne	.L45
	vldm	sp!, {d8}
	pop	{r4, r5, r6, r7, r8, lr}
	mov	r0, #10
	b	putchar
.L51:
	.align	3
.L50:
	.word	0
	.word	1058013184
	.size	print_descaled, .-print_descaled
	.global	angles
	.section	.rodata
	.align	3
	.type	angles, %object
	.size	angles, 40
angles:
	.word	8192
	.word	4836
	.word	2555
	.word	1297
	.word	651
	.word	326
	.word	163
	.word	81
	.word	41
	.space	4
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d \000"
.LC1:
	.ascii	"%f \000"
	.ident	"GCC: (GNU) 8.2.1 20180801 (Red Hat 8.2.1-2)"
	.section	.note.GNU-stack,"",%progbits
