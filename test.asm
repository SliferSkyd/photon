	.globl	main
main:
L0:
	.data
	.align	2
i:	.word	0
	.text
	li	$a0 1
	sw	$a0 i
	.data
	.align	2
j1:	.word	0
	.text
	li	$a0 2
	sw	$a0 j1
	.data
	.align	2
x:	.word	0
	.text
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$t1 4($sp)
	addiu	$sp $sp 4
	add	$a0 $a0 $t1
	sw	$a0 x
L1:
li $v0 10
syscall
