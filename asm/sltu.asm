.data
word:	.word 0xFAFEF1F0

TAB: 	.asciz "\t"
NL: 	.asciz	"\n"
Label:	.asciz "SltuT"
l_ok:	.asciz	" OK"
l_fail:	.asciz	" FAIL"

.text
	li t0, -1
	li t1, 5
	sltu t3, t0, t1
	beqz t3, OK
	j FAIL
	
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
