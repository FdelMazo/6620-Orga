#include <sys/regdef.h>

/*Stack size*/
#define V_STACK_SIZE 68

/*ABA Caller Offsets*/
#define V_N 84
#define V_M 80
#define V_J 76
#define V_I 72
#define V_A 68

/*SRA Offsets*/
#define V_SRA_RA 60
#define V_SRA_FP 52
#define V_SRA_GP 48

/*LTA Offsets*/
#define V_LTA_NEIGHBOURS 44
#define V_LTA_N 40
#define V_LTA_M 36
#define V_LTA_J 32
#define V_LTA_I 28
#define V_LTA_A 24

/*ABA Offsets*/
#define V_ABA_N 16
#define V_ABA_M 12
#define V_ABA_J 8
#define V_ABA_I 4
#define V_ABA_A 0

.text
.align 2
.extern tiene_vecino
.globl vecinos
.ent vecinos

vecinos:
	subu sp, sp, V_STACK_SIZE
	/* SRA */
	sw ra, V_SRA_RA(sp)
	sw fp, V_SRA_FP(sp)
	sw gp, V_SRA_GP(sp)

	move fp, sp

	/*Set ABA Caller*/
	sw a0, V_A(fp)
	sw a1, V_I(fp)
	sw a2, V_J(fp)
	sw a3, V_M(fp)

	/*LTA*/
	lw t0, V_A(fp)
	sw t0, V_LTA_A(fp)

	lw t0, V_I(fp)
	sw t0, V_LTA_I(fp)

	lw t0, V_J(fp)
	sw t0, V_LTA_J(fp)

	lw t0, V_M(fp)
	sw t0, V_LTA_M(fp)

	lw t0, V_N(fp)
	sw t0, V_LTA_N(fp)

    sw zero, V_LTA_NEIGHBOURS(fp)

top_left:
	lw a0, V_LTA_A(fp) 	/*char* a*/
	lw t0, V_LTA_I(fp) 	/*int i*/
	addiu a1, t0, -1
	lw t0, V_LTA_J(fp) 	/*int j*/
	addiu a2, t0, -1
	lw a3, V_LTA_M(fp) 	/*int m*/
	lw t0, V_LTA_N(fp) 	/*int m in ABA*/
	sw t0, V_ABA_N(fp) 

	jal tiene_vecino

	lw t0, V_LTA_NEIGHBOURS(fp)
	addu t0, t0, v0
	sw t0, V_LTA_NEIGHBOURS(fp)

top:
	lw a0, V_LTA_A(fp) 	/*char* a*/
	lw t0, V_LTA_I(fp) 	/*int i*/
	addiu a1, t0, -1
	lw a2, V_LTA_J(fp) 	/*int j*/
	lw a3, V_LTA_M(fp) 	/*int m*/
	lw t0, V_LTA_N(fp) 	/*int m in ABA*/
	sw t0, V_ABA_N(fp) 

	jal tiene_vecino

	lw t0, V_LTA_NEIGHBOURS(fp)
	addu t0, t0, v0
	sw t0, V_LTA_NEIGHBOURS(fp)

top_right:
	lw a0, V_LTA_A(fp) 	/*char* a*/
	lw t0, V_LTA_I(fp) 	/*int i*/
	addiu a1, t0, -1
	lw t0, V_LTA_J(fp) 	/*int j*/
	addiu a2, t0, 1
	lw a3, V_LTA_M(fp) 	/*int m*/
	lw t0, V_LTA_N(fp) 	/*int m in ABA*/
	sw t0, V_ABA_N(fp) 

	jal tiene_vecino

	lw t0, V_LTA_NEIGHBOURS(fp)
	addu t0, t0, v0
	sw t0, V_LTA_NEIGHBOURS(fp)

left:
	lw a0, V_LTA_A(fp) 	/*char* a*/
	lw a1, V_LTA_I(fp) 	/*int i*/
	lw t0, V_LTA_J(fp) 	/*int j*/
	addiu a2, t0, -1
	lw a3, V_LTA_M(fp) 	/*int m*/
	lw t0, V_LTA_N(fp) 	/*int m in ABA*/
	sw t0, V_ABA_N(fp) 

	jal tiene_vecino

	lw t0, V_LTA_NEIGHBOURS(fp)
	addu t0, t0, v0
	sw t0, V_LTA_NEIGHBOURS(fp)

right:
	lw a0, V_LTA_A(fp) 	/*char* a*/
	lw a1, V_LTA_I(fp) 	/*int i*/
	lw t0, V_LTA_J(fp) 	/*int j*/
	addiu a2, t0, 1
	lw a3, V_LTA_M(fp) 	/*int m*/
	lw t0, V_LTA_N(fp) 	/*int m in ABA*/
	sw t0, V_ABA_N(fp) 

	jal tiene_vecino

	lw t0, V_LTA_NEIGHBOURS(fp)
	addu t0, t0, v0
	sw t0, V_LTA_NEIGHBOURS(fp)

bottom_left:
	lw a0, V_LTA_A(fp) 	/*char* a*/
	lw t0, V_LTA_I(fp) 	/*int i*/
	addiu a1, t0, 1
	lw t0, V_LTA_J(fp) 	/*int j*/
	addiu a2, t0, -1
	lw a3, V_LTA_M(fp) 	/*int m*/
	lw t0, V_LTA_N(fp) 	/*int m in ABA*/
	sw t0, V_ABA_N(fp) 

	jal tiene_vecino

	lw t0, V_LTA_NEIGHBOURS(fp)
	addu t0, t0, v0
	sw t0, V_LTA_NEIGHBOURS(fp)

bottom:
	lw a0, V_LTA_A(fp) 	/*char* a*/
	lw t0, V_LTA_I(fp) 	/*int i*/
	addiu a1, t0, 1
	lw a2, V_LTA_J(fp) 	/*int j*/
	lw a3, V_LTA_M(fp) 	/*int m*/
	lw t0, V_LTA_N(fp) 	/*int m in ABA*/
	sw t0, V_ABA_N(fp) 

	jal tiene_vecino

	lw t0, V_LTA_NEIGHBOURS(fp)
	addu t0, t0, v0
	sw t0, V_LTA_NEIGHBOURS(fp)

bottom_right:
	lw a0, V_LTA_A(fp) 	/*char* a*/
	lw t0, V_LTA_I(fp) 	/*int i*/
	addiu a1, t0, 1
	lw t0, V_LTA_J(fp) 	/*int j*/
	addiu a2, t0, 1
	lw a3, V_LTA_M(fp) 	/*int m*/
	lw t0, V_LTA_N(fp) 	/*int m in ABA*/
	sw t0, V_ABA_N(fp) 

	jal tiene_vecino

	lw t0, V_LTA_NEIGHBOURS(fp)
	addu v0, t0, v0

end_vecinos:
    lw fp, V_SRA_FP(sp)
    lw gp, V_SRA_GP(sp)    
    lw ra, V_SRA_RA(sp)

    addiu sp, sp, V_STACK_SIZE
    jr ra

.end vecinos