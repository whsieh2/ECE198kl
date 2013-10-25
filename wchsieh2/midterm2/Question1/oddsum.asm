	.ORIG x3000
;R0 has the start address of the array
;x5000 has the size of the array
;R6 has return value
	LD R0, PTR
	JSR ODDSUM
HALT

ODDSUM
	ST R0, SUM_SAVER0	;stores R0	- Used as a pointer to the current value address
	ST R3, SUM_SAVER3	;stores R3	- Holds the value for each of the inputs
	ST R4, SUM_SAVER4	;stores R4	- temporary, but used as the negative of the size. Used to check if the for loop is done
	ST R5, SUM_SAVER5	;stores R5	- Used as the result of R3 & 1
	

	LD R2, SIZE			;R2 has the size of the array
	NOT R2, R2			; R4 is a temp register.
	ADD R4, R2, #1		; R4 now has the negative value of the size
	ADD R0, R0, #-1		;
LOOP
	ADD R0, R0, #1		; increment R0 
	ADD R4, R4, #1		;
	BRp END				; see's if the for loop is done
	LDR R3, R0, #0		;Will use as each value of the array
	AND R5, R3, #1		;R5 = R3 & 1
	BRz	LOOP			;if the number is not odd, it goes to the next number
	ADD R6, R6, R3		;if the number is odd, it is added to R6
	BRnzp LOOP
END
	LD R0, SUM_SAVER0	;restores R0
	LD R3, SUM_SAVER3	;restores R3
	LD R4, SUM_SAVER4	;restores R4
	LD R5, SUM_SAVER5	;restores R5
RET

SUM_SAVER0	.BLKW #1
SUM_SAVER3	.BLKW #1
SUM_SAVER4	.BLKW #1
SUM_SAVER5	.BLKW #1
SIZE .FILL x5000
PTR .FILL x5001

.END
