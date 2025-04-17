	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 2
	.globl	__Z11disp_structR3Stu           ; -- Begin function _Z11disp_structR3Stu
	.p2align	2
__Z11disp_structR3Stu:                  ; @_Z11disp_structR3Stu
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	ldur	x8, [x29, #-8]
	ldr	w8, [x8]
                                        ; implicit-def: $x10
	mov	x10, x8
	ldur	x8, [x29, #-8]
	mov	x9, sp
	str	x10, [x9]
	add	x8, x8, #4
	str	x8, [x9, #8]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	stp	x28, x27, [sp, #-32]!           ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	sub	sp, sp, #1056
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w27, -24
	.cfi_offset w28, -32
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-24]
	str	wzr, [sp, #16]
	add	x0, sp, #20
	str	x0, [sp, #8]                    ; 8-byte Folded Spill
	mov	x1, #1028                       ; =0x404
	bl	_bzero
	ldr	x0, [sp, #8]                    ; 8-byte Folded Reload
	mov	w8, #3                          ; =0x3
	str	w8, [sp, #20]
	mov	w8, #78                         ; =0x4e
	strb	w8, [sp, #24]
	mov	w8, #65                         ; =0x41
	strb	w8, [sp, #25]
	mov	w9, #90                         ; =0x5a
	strb	w9, [sp, #26]
	mov	w9, #72                         ; =0x48
	strb	w9, [sp, #27]
	strb	w8, [sp, #28]
	bl	__Z11disp_structR3Stu
	ldur	x9, [x29, #-24]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB1_2
	b	LBB1_1
LBB1_1:
	bl	___stack_chk_fail
LBB1_2:
	mov	w0, #0                          ; =0x0
	add	sp, sp, #1056
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp], #32             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Student_id:%d\tinfo:%s\n"

.subsections_via_symbols
