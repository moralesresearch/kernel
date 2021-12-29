/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) 2017 Andes Technology Corporation */

#include <linux/init.h>
#include <linux/linkage.h>
#include <asm/asm.h>
#include <asm/csr.h>
#include <asm/unistd.h>
#include <asm/thread_info.h>
#include <asm/asm-offsets.h>
#include <asm-generic/export.h>
#include <asm/ftrace.h>

	.text

<<<<<<< HEAD
#define FENTRY_RA_OFFSET	12
#define ABI_SIZE_ON_STACK	72
#define ABI_A0			0
#define ABI_A1			8
#define ABI_A2			16
#define ABI_A3			24
#define ABI_A4			32
#define ABI_A5			40
#define ABI_A6			48
#define ABI_A7			56
#define ABI_RA			64

	.macro SAVE_ABI
	addi	sp, sp, -SZREG
	addi	sp, sp, -ABI_SIZE_ON_STACK

	REG_S	a0, ABI_A0(sp)
	REG_S	a1, ABI_A1(sp)
	REG_S	a2, ABI_A2(sp)
	REG_S	a3, ABI_A3(sp)
	REG_S	a4, ABI_A4(sp)
	REG_S	a5, ABI_A5(sp)
	REG_S	a6, ABI_A6(sp)
	REG_S	a7, ABI_A7(sp)
	REG_S	ra, ABI_RA(sp)
	.endm

	.macro RESTORE_ABI
	REG_L	a0, ABI_A0(sp)
	REG_L	a1, ABI_A1(sp)
	REG_L	a2, ABI_A2(sp)
	REG_L	a3, ABI_A3(sp)
	REG_L	a4, ABI_A4(sp)
	REG_L	a5, ABI_A5(sp)
	REG_L	a6, ABI_A6(sp)
	REG_L	a7, ABI_A7(sp)
	REG_L	ra, ABI_RA(sp)

	addi	sp, sp, ABI_SIZE_ON_STACK
	addi	sp, sp, SZREG
	.endm

#ifdef CONFIG_DYNAMIC_FTRACE_WITH_REGS
	.macro SAVE_ALL
	addi	sp, sp, -SZREG
	addi	sp, sp, -PT_SIZE_ON_STACK

	REG_S x1,  PT_EPC(sp)
	addi	sp, sp, PT_SIZE_ON_STACK
	REG_L x1,  (sp)
	addi	sp, sp, -PT_SIZE_ON_STACK
	REG_S x1,  PT_RA(sp)
	REG_L x1,  PT_EPC(sp)

	REG_S x2,  PT_SP(sp)
	REG_S x3,  PT_GP(sp)
	REG_S x4,  PT_TP(sp)
	REG_S x5,  PT_T0(sp)
	REG_S x6,  PT_T1(sp)
	REG_S x7,  PT_T2(sp)
	REG_S x8,  PT_S0(sp)
	REG_S x9,  PT_S1(sp)
	REG_S x10, PT_A0(sp)
	REG_S x11, PT_A1(sp)
	REG_S x12, PT_A2(sp)
	REG_S x13, PT_A3(sp)
	REG_S x14, PT_A4(sp)
	REG_S x15, PT_A5(sp)
	REG_S x16, PT_A6(sp)
	REG_S x17, PT_A7(sp)
	REG_S x18, PT_S2(sp)
	REG_S x19, PT_S3(sp)
	REG_S x20, PT_S4(sp)
	REG_S x21, PT_S5(sp)
	REG_S x22, PT_S6(sp)
	REG_S x23, PT_S7(sp)
	REG_S x24, PT_S8(sp)
	REG_S x25, PT_S9(sp)
	REG_S x26, PT_S10(sp)
	REG_S x27, PT_S11(sp)
	REG_S x28, PT_T3(sp)
	REG_S x29, PT_T4(sp)
	REG_S x30, PT_T5(sp)
	REG_S x31, PT_T6(sp)
	.endm

	.macro RESTORE_ALL
	REG_L x1,  PT_RA(sp)
	addi	sp, sp, PT_SIZE_ON_STACK
	REG_S x1,  (sp)
	addi	sp, sp, -PT_SIZE_ON_STACK
	REG_L x1,  PT_EPC(sp)
	REG_L x2,  PT_SP(sp)
	REG_L x3,  PT_GP(sp)
	REG_L x4,  PT_TP(sp)
	REG_L x5,  PT_T0(sp)
	REG_L x6,  PT_T1(sp)
	REG_L x7,  PT_T2(sp)
	REG_L x8,  PT_S0(sp)
	REG_L x9,  PT_S1(sp)
	REG_L x10, PT_A0(sp)
	REG_L x11, PT_A1(sp)
	REG_L x12, PT_A2(sp)
	REG_L x13, PT_A3(sp)
	REG_L x14, PT_A4(sp)
	REG_L x15, PT_A5(sp)
	REG_L x16, PT_A6(sp)
	REG_L x17, PT_A7(sp)
	REG_L x18, PT_S2(sp)
	REG_L x19, PT_S3(sp)
	REG_L x20, PT_S4(sp)
	REG_L x21, PT_S5(sp)
	REG_L x22, PT_S6(sp)
	REG_L x23, PT_S7(sp)
	REG_L x24, PT_S8(sp)
	REG_L x25, PT_S9(sp)
	REG_L x26, PT_S10(sp)
	REG_L x27, PT_S11(sp)
	REG_L x28, PT_T3(sp)
	REG_L x29, PT_T4(sp)
	REG_L x30, PT_T5(sp)
	REG_L x31, PT_T6(sp)

	addi	sp, sp, PT_SIZE_ON_STACK
	addi	sp, sp, SZREG
	.endm
#endif /* CONFIG_DYNAMIC_FTRACE_WITH_REGS */

ENTRY(ftrace_caller)
	SAVE_ABI

	addi	a0, ra, -FENTRY_RA_OFFSET
	la	a1, function_trace_op
	REG_L	a2, 0(a1)
	REG_L	a1, ABI_SIZE_ON_STACK(sp)
	mv	a3, sp

ftrace_call:
	.global ftrace_call
	call	ftrace_stub

#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	addi	a0, sp, ABI_SIZE_ON_STACK
	REG_L	a1, ABI_RA(sp)
	addi	a1, a1, -FENTRY_RA_OFFSET
#ifdef HAVE_FUNCTION_GRAPH_FP_TEST
	mv	a2, s0
#endif
ftrace_graph_call:
	.global ftrace_graph_call
	call	ftrace_stub
#endif
	RESTORE_ABI
=======
	.macro SAVE_ABI_STATE
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	addi    sp, sp, -48
	sd      s0, 32(sp)
	sd      ra, 40(sp)
	addi    s0, sp, 48
	sd      t0, 24(sp)
	sd      t1, 16(sp)
#ifdef HAVE_FUNCTION_GRAPH_FP_TEST
	sd      t2, 8(sp)
#endif
#else
	addi	sp, sp, -16
	sd	s0, 0(sp)
	sd	ra, 8(sp)
	addi	s0, sp, 16
#endif
	.endm

	.macro RESTORE_ABI_STATE
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	ld	s0, 32(sp)
	ld	ra, 40(sp)
	addi	sp, sp, 48
#else
	ld	ra, 8(sp)
	ld	s0, 0(sp)
	addi	sp, sp, 16
#endif
	.endm

	.macro RESTORE_GRAPH_ARGS
	ld	a0, 24(sp)
	ld	a1, 16(sp)
#ifdef HAVE_FUNCTION_GRAPH_FP_TEST
	ld	a2, 8(sp)
#endif
	.endm

ENTRY(ftrace_graph_caller)
	addi	sp, sp, -16
	sd	s0, 0(sp)
	sd	ra, 8(sp)
	addi	s0, sp, 16
ftrace_graph_call:
	.global ftrace_graph_call
	/*
	 * Calling ftrace_enable/disable_ftrace_graph_caller would overwrite the
	 * call below.  Check ftrace_modify_all_code for details.
	 */
	call	ftrace_stub
	ld	ra, 8(sp)
	ld	s0, 0(sp)
	addi	sp, sp, 16
	ret
ENDPROC(ftrace_graph_caller)

ENTRY(ftrace_caller)
	/*
	 * a0: the address in the caller when calling ftrace_caller
	 * a1: the caller's return address
	 * a2: the address of global variable function_trace_op
	 */
	ld	a1, -8(s0)
	addi	a0, ra, -MCOUNT_INSN_SIZE
	la	t5, function_trace_op
	ld	a2, 0(t5)

#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	/*
	 * the graph tracer (specifically, prepare_ftrace_return) needs these
	 * arguments but for now the function tracer occupies the regs, so we
	 * save them in temporary regs to recover later.
	 */
	addi	t0, s0, -8
	mv	t1, a0
#ifdef HAVE_FUNCTION_GRAPH_FP_TEST
	ld	t2, -16(s0)
#endif
#endif

	SAVE_ABI_STATE
ftrace_call:
	.global ftrace_call
	/*
	 * For the dynamic ftrace to work, here we should reserve at least
	 * 8 bytes for a functional auipc-jalr pair.  The following call
	 * serves this purpose.
	 *
	 * Calling ftrace_update_ftrace_func would overwrite the nops below.
	 * Check ftrace_modify_all_code for details.
	 */
	call	ftrace_stub

#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	RESTORE_GRAPH_ARGS
	call	ftrace_graph_caller
#endif

	RESTORE_ABI_STATE
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
	ret
ENDPROC(ftrace_caller)

#ifdef CONFIG_DYNAMIC_FTRACE_WITH_REGS
<<<<<<< HEAD
ENTRY(ftrace_regs_caller)
	SAVE_ALL

	addi	a0, ra, -FENTRY_RA_OFFSET
	la	a1, function_trace_op
	REG_L	a2, 0(a1)
	REG_L	a1, PT_SIZE_ON_STACK(sp)
	mv	a3, sp
=======
	.macro SAVE_ALL
	addi	sp, sp, -(PT_SIZE_ON_STACK+16)
	sd	s0, (PT_SIZE_ON_STACK)(sp)
	sd	ra, (PT_SIZE_ON_STACK+8)(sp)
	addi	s0, sp, (PT_SIZE_ON_STACK+16)

	sd x1,  PT_RA(sp)
	sd x2,  PT_SP(sp)
	sd x3,  PT_GP(sp)
	sd x4,  PT_TP(sp)
	sd x5,  PT_T0(sp)
	sd x6,  PT_T1(sp)
	sd x7,  PT_T2(sp)
	sd x8,  PT_S0(sp)
	sd x9,  PT_S1(sp)
	sd x10, PT_A0(sp)
	sd x11, PT_A1(sp)
	sd x12, PT_A2(sp)
	sd x13, PT_A3(sp)
	sd x14, PT_A4(sp)
	sd x15, PT_A5(sp)
	sd x16, PT_A6(sp)
	sd x17, PT_A7(sp)
	sd x18, PT_S2(sp)
	sd x19, PT_S3(sp)
	sd x20, PT_S4(sp)
	sd x21, PT_S5(sp)
	sd x22, PT_S6(sp)
	sd x23, PT_S7(sp)
	sd x24, PT_S8(sp)
	sd x25, PT_S9(sp)
	sd x26, PT_S10(sp)
	sd x27, PT_S11(sp)
	sd x28, PT_T3(sp)
	sd x29, PT_T4(sp)
	sd x30, PT_T5(sp)
	sd x31, PT_T6(sp)
	.endm

	.macro RESTORE_ALL
	ld x1,  PT_RA(sp)
	ld x2,  PT_SP(sp)
	ld x3,  PT_GP(sp)
	ld x4,  PT_TP(sp)
	ld x5,  PT_T0(sp)
	ld x6,  PT_T1(sp)
	ld x7,  PT_T2(sp)
	ld x8,  PT_S0(sp)
	ld x9,  PT_S1(sp)
	ld x10, PT_A0(sp)
	ld x11, PT_A1(sp)
	ld x12, PT_A2(sp)
	ld x13, PT_A3(sp)
	ld x14, PT_A4(sp)
	ld x15, PT_A5(sp)
	ld x16, PT_A6(sp)
	ld x17, PT_A7(sp)
	ld x18, PT_S2(sp)
	ld x19, PT_S3(sp)
	ld x20, PT_S4(sp)
	ld x21, PT_S5(sp)
	ld x22, PT_S6(sp)
	ld x23, PT_S7(sp)
	ld x24, PT_S8(sp)
	ld x25, PT_S9(sp)
	ld x26, PT_S10(sp)
	ld x27, PT_S11(sp)
	ld x28, PT_T3(sp)
	ld x29, PT_T4(sp)
	ld x30, PT_T5(sp)
	ld x31, PT_T6(sp)

	ld	s0, (PT_SIZE_ON_STACK)(sp)
	ld	ra, (PT_SIZE_ON_STACK+8)(sp)
	addi	sp, sp, (PT_SIZE_ON_STACK+16)
	.endm

	.macro RESTORE_GRAPH_REG_ARGS
	ld	a0, PT_T0(sp)
	ld	a1, PT_T1(sp)
#ifdef HAVE_FUNCTION_GRAPH_FP_TEST
	ld	a2, PT_T2(sp)
#endif
	.endm

/*
 * Most of the contents are the same as ftrace_caller.
 */
ENTRY(ftrace_regs_caller)
	/*
	 * a3: the address of all registers in the stack
	 */
	ld	a1, -8(s0)
	addi	a0, ra, -MCOUNT_INSN_SIZE
	la	t5, function_trace_op
	ld	a2, 0(t5)
	addi	a3, sp, -(PT_SIZE_ON_STACK+16)

#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	addi	t0, s0, -8
	mv	t1, a0
#ifdef HAVE_FUNCTION_GRAPH_FP_TEST
	ld	t2, -16(s0)
#endif
#endif
	SAVE_ALL
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b

ftrace_regs_call:
	.global ftrace_regs_call
	call	ftrace_stub

#ifdef CONFIG_FUNCTION_GRAPH_TRACER
<<<<<<< HEAD
	addi	a0, sp, PT_RA
	REG_L	a1, PT_EPC(sp)
	addi	a1, a1, -FENTRY_RA_OFFSET
#ifdef HAVE_FUNCTION_GRAPH_FP_TEST
	mv	a2, s0
#endif
ftrace_graph_regs_call:
	.global ftrace_graph_regs_call
	call	ftrace_stub
=======
	RESTORE_GRAPH_REG_ARGS
	call	ftrace_graph_caller
>>>>>>> 482398af3c2fc5af953c5a3127ca167a01d0949b
#endif

	RESTORE_ALL
	ret
ENDPROC(ftrace_regs_caller)
#endif /* CONFIG_DYNAMIC_FTRACE_WITH_REGS */
