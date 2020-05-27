#include <sys/regdef.h>

/*Stack size*/
#define EV_STACK_SIZE 32

/*ABA Caller Offsets*/
#define EV_N 48
#define EV_M 44
#define EV_J 40
#define EV_I 36
#define EV_A 32

/*SRA Offsets*/
#define EV_SRA_FP 28
#define EV_SRA_GP 24

/*LTA Offsets*/
#define EV_LTA_N 16
#define EV_LTA_M 12
#define EV_LTA_J 8
#define EV_LTA_I 4
#define EV_LTA_A 0

.text
.align 2
.globl tiene_vecino
.ent tiene_vecino

tiene_vecino:
	subu sp, sp, EV_STACK_SIZE
	/* SRA */
	sw gp, EV_SRA_GP(sp)
	sw fp, EV_SRA_FP(sp)

	move fp, sp

	/*Set ABA Caller*/
	sw a0, EV_A(fp)
	sw a1, EV_I(fp)
	sw a2, EV_J(fp)
	sw a3, EV_M(fp)

	/*LTA*/
	lw t0, EV_A(fp)
	sw t0, EV_LTA_A(fp)

	lw t0, EV_I(fp)
	sw t0, EV_LTA_I(fp)

	lw t0, EV_J(fp)
	sw t0, EV_LTA_J(fp)

	lw t0, EV_M(fp)
	sw t0, EV_LTA_M(fp)

	lw t0, EV_N(fp)
	sw t0, EV_LTA_N(fp)

	/*Row calculation*/
	lw t0, EV_LTA_I(fp)
	lw t1, EV_LTA_M(fp)
	addu t0, t0, t1
	divu t0, t1
	mfhi t0
	sw t0, EV_LTA_I(fp)

	/*Column calculation*/
	lw t0, EV_LTA_J(fp)
	lw t1, EV_LTA_N(fp)
	addu t0, t0, t1
	divu t0, t1
	mfhi t0
	sw t0, EV_LTA_J(fp)

	/*Offset calculation*/
	lw t0, EV_LTA_J(fp)
	lw t1, EV_LTA_I(fp)
	lw t2, EV_LTA_M(fp)
	mult t1, t2
	mflo t1
	addu t0, t0, t1

	/*Check*/
	lw t1, EV_LTA_A(fp)
	addu t1, t1, t0
	li t0, '1'
	lbu t1, 0(t1)

	li v0, 0
	bne t0, t1, fin
	addiu v0, v0, 1

fin:
    lw fp, EV_SRA_FP(sp)
    lw gp, EV_SRA_GP(sp)

    addiu sp, sp, EV_STACK_SIZE
    jr ra
    
.end tiene_vecino
