	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.global	current_task
	.data
	.type	current_task, %object
	.size	current_task, 1
current_task:
	.byte	1
	.global	g_tick_count
	.bss
	.align	2
	.type	g_tick_count, %object
	.size	g_tick_count, 4
g_tick_count:
	.space	4
	.global	user_tasks
	.align	2
	.type	user_tasks, %object
	.size	user_tasks, 80
user_tasks:
	.space	80
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	bl	enable_processor_fault
	ldr	r0, .L3
	bl	init_scheduler_stack
	bl	init_tasks_stack
	bl	led_init_all
	mov	r0, #1000
	bl	init_systick_timer
	bl	switch_sp_to_psp
	bl	task1_handler
.L2:
	b	.L2
.L4:
	.align	2
.L3:
	.word	536996864
	.size	main, .-main
	.align	2
	.global	idle_task
	.syntax unified
	.arm
	.type	idle_task, %function
idle_task:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
.L6:
	b	.L6
	.size	idle_task, .-idle_task
	.align	2
	.global	task1_handler
	.syntax unified
	.arm
	.type	task1_handler, %function
task1_handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
.L8:
	mov	r0, #12
	bl	led_on
	mov	r0, #1000
	bl	task_delay
	mov	r0, #12
	bl	led_off
	mov	r0, #1000
	bl	task_delay
	b	.L8
	.size	task1_handler, .-task1_handler
	.align	2
	.global	task2_handler
	.syntax unified
	.arm
	.type	task2_handler, %function
task2_handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
.L10:
	mov	r0, #13
	bl	led_on
	mov	r0, #500
	bl	task_delay
	mov	r0, #13
	bl	led_off
	mov	r0, #500
	bl	task_delay
	b	.L10
	.size	task2_handler, .-task2_handler
	.align	2
	.global	task3_handler
	.syntax unified
	.arm
	.type	task3_handler, %function
task3_handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
.L12:
	mov	r0, #15
	bl	led_on
	mov	r0, #250
	bl	task_delay
	mov	r0, #15
	bl	led_off
	mov	r0, #250
	bl	task_delay
	b	.L12
	.size	task3_handler, .-task3_handler
	.align	2
	.global	task4_handler
	.syntax unified
	.arm
	.type	task4_handler, %function
task4_handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
.L14:
	mov	r0, #14
	bl	led_on
	mov	r0, #125
	bl	task_delay
	mov	r0, #14
	bl	led_off
	mov	r0, #125
	bl	task_delay
	b	.L14
	.size	task4_handler, .-task4_handler
	.global	__aeabi_uidiv
	.align	2
	.global	init_systick_timer
	.syntax unified
	.arm
	.type	init_systick_timer, %function
init_systick_timer:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	ldr	r3, .L16
	str	r3, [fp, #-8]
	ldr	r3, .L16+4
	str	r3, [fp, #-12]
	ldr	r1, [fp, #-24]
	ldr	r0, .L16+8
	bl	__aeabi_uidiv
	mov	r3, r0
	sub	r3, r3, #1
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	and	r2, r3, #-16777216
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	ldr	r3, [fp, #-8]
	ldr	r2, [r3]
	ldr	r3, [fp, #-16]
	orr	r2, r2, r3
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	ldr	r3, [fp, #-12]
	ldr	r3, [r3]
	orr	r2, r3, #2
	ldr	r3, [fp, #-12]
	str	r2, [r3]
	ldr	r3, [fp, #-12]
	ldr	r3, [r3]
	orr	r2, r3, #4
	ldr	r3, [fp, #-12]
	str	r2, [r3]
	ldr	r3, [fp, #-12]
	ldr	r3, [r3]
	orr	r2, r3, #1
	ldr	r3, [fp, #-12]
	str	r2, [r3]
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L17:
	.align	2
.L16:
	.word	-536813548
	.word	-536813552
	.word	16000000
	.size	init_systick_timer, .-init_systick_timer
	.align	2
	.global	init_tasks_stack
	.syntax unified
	.arm
	.type	init_tasks_stack, %function
init_tasks_stack:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #20
	ldr	r3, .L23
	mov	r2, #0
	strb	r2, [r3, #8]
	ldr	r3, .L23
	mov	r2, #0
	strb	r2, [r3, #24]
	ldr	r3, .L23
	mov	r2, #0
	strb	r2, [r3, #40]
	ldr	r3, .L23
	mov	r2, #0
	strb	r2, [r3, #56]
	ldr	r3, .L23
	mov	r2, #0
	strb	r2, [r3, #72]
	ldr	r3, .L23
	ldr	r2, .L23+4
	str	r2, [r3]
	ldr	r3, .L23
	ldr	r2, .L23+8
	str	r2, [r3, #16]
	ldr	r3, .L23
	ldr	r2, .L23+12
	str	r2, [r3, #32]
	ldr	r3, .L23
	ldr	r2, .L23+16
	str	r2, [r3, #48]
	ldr	r3, .L23
	ldr	r2, .L23+20
	str	r2, [r3, #64]
	ldr	r3, .L23
	ldr	r2, .L23+24
	str	r2, [r3, #12]
	ldr	r3, .L23
	ldr	r2, .L23+28
	str	r2, [r3, #28]
	ldr	r3, .L23
	ldr	r2, .L23+32
	str	r2, [r3, #44]
	ldr	r3, .L23
	ldr	r2, .L23+36
	str	r2, [r3, #60]
	ldr	r3, .L23
	ldr	r2, .L23+40
	str	r2, [r3, #76]
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L19
.L22:
	ldr	r2, .L23
	ldr	r3, [fp, #-12]
	ldr	r3, [r2, r3, lsl #4]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	sub	r3, r3, #4
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	mov	r2, #16777216
	str	r2, [r3]
	ldr	r3, [fp, #-8]
	sub	r3, r3, #4
	str	r3, [fp, #-8]
	ldr	r2, .L23
	ldr	r3, [fp, #-12]
	lsl	r3, r3, #4
	add	r3, r2, r3
	ldr	r3, [r3, #12]
	mov	r2, r3
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	ldr	r3, [fp, #-8]
	sub	r3, r3, #4
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	mvn	r2, #2
	str	r2, [r3]
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L20
.L21:
	ldr	r3, [fp, #-8]
	sub	r3, r3, #4
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	mov	r2, #0
	str	r2, [r3]
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L20:
	ldr	r3, [fp, #-16]
	cmp	r3, #12
	ble	.L21
	ldr	r2, [fp, #-8]
	ldr	r1, .L23
	ldr	r3, [fp, #-12]
	str	r2, [r1, r3, lsl #4]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L19:
	ldr	r3, [fp, #-12]
	cmp	r3, #4
	ble	.L22
	nop
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L24:
	.align	2
.L23:
	.word	user_tasks
	.word	536997888
	.word	537001984
	.word	537000960
	.word	536999936
	.word	536998912
	.word	idle_task
	.word	task1_handler
	.word	task2_handler
	.word	task3_handler
	.word	task4_handler
	.size	init_tasks_stack, .-init_tasks_stack
	.align	2
	.global	init_scheduler_stack
	.syntax unified
	.arm
	.type	init_scheduler_stack, %function
init_scheduler_stack:
	@ Function supports interworking.
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	r3, r0
	.syntax divided
@ 190 "main.c" 1
	MSR MSP, r3
@ 0 "" 2
@ 191 "main.c" 1
	BX LR
@ 0 "" 2
	.arm
	.syntax unified
	nop
	.size	init_scheduler_stack, .-init_scheduler_stack
	.align	2
	.global	enable_processor_fault
	.syntax unified
	.arm
	.type	enable_processor_fault, %function
enable_processor_fault:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	ldr	r3, .L27
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	orr	r2, r3, #65536
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	orr	r2, r3, #131072
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	orr	r2, r3, #262144
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L28:
	.align	2
.L27:
	.word	-536810204
	.size	enable_processor_fault, .-enable_processor_fault
	.align	2
	.global	get_psp_value
	.syntax unified
	.arm
	.type	get_psp_value, %function
get_psp_value:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L31
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r2, r3
	ldr	r3, .L31+4
	ldr	r3, [r3, r2, lsl #4]
	mov	r0, r3
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L32:
	.align	2
.L31:
	.word	current_task
	.word	user_tasks
	.size	get_psp_value, .-get_psp_value
	.align	2
	.global	update_next_task
	.syntax unified
	.arm
	.type	update_next_task, %function
update_next_task:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #255
	str	r3, [fp, #-8]
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L34
.L37:
	ldr	r3, .L41
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, #1
	and	r2, r3, #255
	ldr	r3, .L41
	strb	r2, [r3]
	ldr	r3, .L41
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L41+4
	umull	r1, r3, r2, r3
	lsr	r1, r3, #2
	mov	r3, r1
	lsl	r3, r3, #2
	add	r3, r3, r1
	sub	r3, r2, r3
	and	r2, r3, #255
	ldr	r3, .L41
	strb	r2, [r3]
	ldr	r3, .L41
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r2, .L41+8
	lsl	r3, r3, #4
	add	r3, r2, r3
	ldrb	r3, [r3, #8]	@ zero_extendqisi2
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L35
	ldr	r3, .L41
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L39
.L35:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L34:
	ldr	r3, [fp, #-12]
	cmp	r3, #4
	ble	.L37
	b	.L36
.L39:
	nop
.L36:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	beq	.L40
	ldr	r3, .L41
	mov	r2, #0
	strb	r2, [r3]
.L40:
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L42:
	.align	2
.L41:
	.word	current_task
	.word	-858993459
	.word	user_tasks
	.size	update_next_task, .-update_next_task
	.align	2
	.global	save_psp_value
	.syntax unified
	.arm
	.type	save_psp_value, %function
save_psp_value:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	ldr	r3, .L44
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r1, r3
	ldr	r2, .L44+4
	ldr	r3, [fp, #-8]
	str	r3, [r2, r1, lsl #4]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L45:
	.align	2
.L44:
	.word	current_task
	.word	user_tasks
	.size	save_psp_value, .-save_psp_value
	.align	2
	.global	switch_sp_to_psp
	.syntax unified
	.arm
	.type	switch_sp_to_psp, %function
switch_sp_to_psp:
	@ Function supports interworking.
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.syntax divided
@ 236 "main.c" 1
	PUSH {LR}
@ 0 "" 2
@ 237 "main.c" 1
	BL get_psp_value
@ 0 "" 2
@ 238 "main.c" 1
	MSR PSP, R0
@ 0 "" 2
@ 239 "main.c" 1
	POP {LR}
@ 0 "" 2
@ 242 "main.c" 1
	MOV R0, #0X02
@ 0 "" 2
@ 243 "main.c" 1
	MSR CONTROL, R0
@ 0 "" 2
@ 244 "main.c" 1
	BX LR
@ 0 "" 2
	.arm
	.syntax unified
	nop
	.size	switch_sp_to_psp, .-switch_sp_to_psp
	.align	2
	.global	schedule
	.syntax unified
	.arm
	.type	schedule, %function
schedule:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	ldr	r3, .L48
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	orr	r2, r3, #268435456
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L49:
	.align	2
.L48:
	.word	-536810236
	.size	schedule, .-schedule
	.align	2
	.global	task_delay
	.syntax unified
	.arm
	.type	task_delay, %function
task_delay:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	.syntax divided
@ 257 "main.c" 1
	MOV R0, #0x1
@ 0 "" 2
@ 257 "main.c" 1
	MSR PRIMASK, R0
@ 0 "" 2
	.arm
	.syntax unified
	ldr	r3, .L52
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L51
	ldr	r3, .L52+4
	ldr	r2, [r3]
	ldr	r3, .L52
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r0, r3
	ldr	r3, [fp, #-8]
	add	r2, r2, r3
	ldr	r1, .L52+8
	lsl	r3, r0, #4
	add	r3, r1, r3
	str	r2, [r3, #4]
	ldr	r3, .L52
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r2, .L52+8
	lsl	r3, r3, #4
	add	r3, r2, r3
	mvn	r2, #0
	strb	r2, [r3, #8]
	bl	schedule
.L51:
	.syntax divided
@ 267 "main.c" 1
	MOV R0, #0x0
@ 0 "" 2
@ 267 "main.c" 1
	MSR PRIMASK, R0
@ 0 "" 2
	.arm
	.syntax unified
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L53:
	.align	2
.L52:
	.word	current_task
	.word	g_tick_count
	.word	user_tasks
	.size	task_delay, .-task_delay
	.align	2
	.global	PendSV_Handler
	.syntax unified
	.arm
	.type	PendSV_Handler, %function
PendSV_Handler:
	@ Function supports interworking.
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.syntax divided
@ 275 "main.c" 1
	MRS R0, PSP
@ 0 "" 2
@ 277 "main.c" 1
	STMDB R0!, {R4-R11}
@ 0 "" 2
@ 279 "main.c" 1
	PUSH {LR}
@ 0 "" 2
@ 280 "main.c" 1
	BL save_psp_value
@ 0 "" 2
@ 285 "main.c" 1
	BL update_next_task
@ 0 "" 2
@ 287 "main.c" 1
	BL get_psp_value
@ 0 "" 2
@ 289 "main.c" 1
	LDMIA R0!, {R4-R11}
@ 0 "" 2
@ 291 "main.c" 1
	MSR PSP, R0
@ 0 "" 2
@ 292 "main.c" 1
	POP {LR}
@ 0 "" 2
@ 293 "main.c" 1
	BX LR
@ 0 "" 2
	.arm
	.syntax unified
	nop
	.size	PendSV_Handler, .-PendSV_Handler
	.align	2
	.global	update_global_tick_count
	.syntax unified
	.arm
	.type	update_global_tick_count, %function
update_global_tick_count:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L56
	ldr	r3, [r3]
	add	r3, r3, #1
	ldr	r2, .L56
	str	r3, [r2]
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L57:
	.align	2
.L56:
	.word	g_tick_count
	.size	update_global_tick_count, .-update_global_tick_count
	.align	2
	.global	unblock_tasks
	.syntax unified
	.arm
	.type	unblock_tasks, %function
unblock_tasks:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #1
	str	r3, [fp, #-8]
	b	.L59
.L61:
	ldr	r2, .L62
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #4
	add	r3, r2, r3
	ldrb	r3, [r3, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L60
	ldr	r2, .L62
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #4
	add	r3, r2, r3
	ldr	r2, [r3, #4]
	ldr	r3, .L62+4
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L60
	ldr	r2, .L62
	ldr	r3, [fp, #-8]
	lsl	r3, r3, #4
	add	r3, r2, r3
	mov	r2, #0
	strb	r2, [r3, #8]
.L60:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L59:
	ldr	r3, [fp, #-8]
	cmp	r3, #4
	ble	.L61
	nop
	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L63:
	.align	2
.L62:
	.word	user_tasks
	.word	g_tick_count
	.size	unblock_tasks, .-unblock_tasks
	.align	2
	.global	SysTick_Handler
	.syntax unified
	.arm
	.type	SysTick_Handler, %function
SysTick_Handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	ldr	r3, .L65
	str	r3, [fp, #-8]
	bl	update_global_tick_count
	bl	unblock_tasks
	ldr	r3, [fp, #-8]
	ldr	r3, [r3]
	orr	r2, r3, #268435456
	ldr	r3, [fp, #-8]
	str	r2, [r3]
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L66:
	.align	2
.L65:
	.word	-536810236
	.size	SysTick_Handler, .-SysTick_Handler
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Exception : Hardfault\000"
	.text
	.align	2
	.global	HardFault_Handler
	.syntax unified
	.arm
	.type	HardFault_Handler, %function
HardFault_Handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r0, .L69
	bl	puts
.L68:
	b	.L68
.L70:
	.align	2
.L69:
	.word	.LC0
	.size	HardFault_Handler, .-HardFault_Handler
	.section	.rodata
	.align	2
.LC1:
	.ascii	"Exception : MemManage\000"
	.text
	.align	2
	.global	MemManage_Handler
	.syntax unified
	.arm
	.type	MemManage_Handler, %function
MemManage_Handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r0, .L73
	bl	puts
.L72:
	b	.L72
.L74:
	.align	2
.L73:
	.word	.LC1
	.size	MemManage_Handler, .-MemManage_Handler
	.section	.rodata
	.align	2
.LC2:
	.ascii	"Exception : BusFault\000"
	.text
	.align	2
	.global	BusFault_Handler
	.syntax unified
	.arm
	.type	BusFault_Handler, %function
BusFault_Handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r0, .L77
	bl	puts
.L76:
	b	.L76
.L78:
	.align	2
.L77:
	.word	.LC2
	.size	BusFault_Handler, .-BusFault_Handler
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
