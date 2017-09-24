	.syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.syntax unified
	.file	"main.c"
	.data
	.align	2
	.type	j, %object
	.size	j, 4
j:
	.word	20
	.text
	.align	2
	.global	fact
	.thumb
	.thumb_func
	.type	fact, %function
fact:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, [r7, #4]
	cmp	r3, #1
	bne	.L2
	movs	r3, #1
	b	.L3
.L2:
	ldr	r3, .L5
	ldr	r3, [r3]
	ldr	r2, [r7, #4]
	cmp	r2, r3
	beq	.L4
	ldr	r3, [r7, #4]
	subs	r3, r3, #1
	mov	r0, r3
	bl	fact
	mov	r2, r0
	ldr	r3, [r7, #4]
	mul	r3, r3, r2
	b	.L3
.L4:
	ldr	r3, [r7, #4]
	subs	r3, r3, #2
	mov	r0, r3
	bl	fact
	mov	r2, r0
	ldr	r3, [r7, #4]
	mul	r3, r3, r2
.L3:
	mov	r0, r3
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L6:
	.align	2
.L5:
	.word	j
	.size	fact, .-fact
	.align	2
	.global	main
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	movs	r3, #5
	str	r3, [r7, #4]
	ldr	r0, [r7, #4]
	bl	fact
	ldr	r3, .L9
	movs	r2, #10
	str	r2, [r3]
	ldr	r0, [r7, #4]
	bl	fact
	movs	r3, #0
	mov	r0, r3
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L10:
	.align	2
.L9:
	.word	j
	.size	main, .-main
	.ident	"GCC: (GNU Tools for ARM Embedded Processors) 5.4.1 20160919 (release) [ARM/embedded-5-branch revision 240496]"
