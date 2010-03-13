    ;Ensure that the block holding the number of keys contains a known value upon first startup of the product.
	AREA KEYDATA (ROM, ABS, CON)

    org   1000h                        ;Reset Interrupt Vector
	dw 0000h, ffffh
	dw ffffh, ffffh
