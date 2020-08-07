.data
	uno: .word	1
	dos: .word	2
	tres: .word	3

.text
	li $t0, uno
	li $t1, 4
	lws $t2, $t1, 2, $t0