.data
	uno: .word	1
	dos: .word	2
	tres: .word	3

.text
	lw $t4, uno
	li $t0, uno
	li $t1, 4
	lwp $t2, $t1, 1, $t0