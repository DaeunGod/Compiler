# C- Compilation to TM Code
# File: test10.tm
# ##########################################
	.data
inStr:	.asciiz	"Enter value for input instruction: "
OutStr:	.asciiz	"output instruction prints: "
crlfz:	.ascii	"\n"
	.text
	.globl main

# ##########################################
# FUNCTIONS: WR_INT, RD_INT
# WR_INT: print single integer
# RD_INT: read single integer
WR_INT:
	addi	$v0,$0,1 # Print integer
	syscall
	la	$a0,crlfz
	addi	$v0,$0,4
	syscall
	jr	$ra # Return
RD_INT:
	addi	$v0,$0,5 # Read integer
	syscall
	add	$a0,$v0,$0 # Move Integer into $a0
	jr	$ra # Return
# ##########################################

# Function Dec
main:
# 	Save registers
	subu	$sp,$sp,32
	sw	$ra,8($sp)
	sw	$fp,0($sp)
	addu	$fp,$sp,0
# 
	subu	$sp,$sp,4
	subu	$sp,$sp,4
# expr
	beqz	$v0,L0
	subu	$sp,$sp,4
	j	L1
# compound1
L0:
L1:
	jal	RD_INT
	sw	$a0,-8($fp)
	lw	$a0,-8($fp)
	jal	WR_INT
	lw	$a0,-12($fp)
	jal	WR_INT
	addu	$sp,$sp,12
# 
# 	Restore registers
	lw	$ra,8($sp)
	lw	$fp,0($sp)
	addu	$sp,$sp,32
	jr	$ra
