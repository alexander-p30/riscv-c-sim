.data
word:	.word 0xFAFEF1F0

TAB: 	.asciz "\t"
NL: 	.asciz	"\n"
Label:	.asciz "JalrT"
l_ok:	.asciz	" OK"
l_fail:	.asciz	" FAIL"

.text	# pula para OK se jalr funcionar corretamente
	li t0, 8
	jalr a0, t0, 4
	j FAIL
	j OK
	
FAIL:
	la a0, Label
	li a7, 4
	ecall
	la a0, l_fail
	li a7, 4
	ecall
	la a0, NL
	ecall
	li a7, 10
	ecall
	
OK:
	la a0, Label
	li a7, 4
	ecall
	la a0, l_ok
	li a7, 4
	ecall
	la a0, NL
	ecall
	li a7, 10
	ecall
