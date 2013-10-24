.ORIG x3000
;R0 has the start address of the array
;x5000 has the size of the array
;R1 has return value
LD R0, PTR
JSR ODDSUM
HALT

ODDSUM
; write your code here

	AND R1,R1,#0;
	AND R2,R2,#0;
	AND R3,R3,#0;
	AND R6,R6,#0;

	LDI R2, SIZE

AGAIN	LDR R1,R0,#0;
	AND R3,R1,#1;
	BRz EVEN
	ADD R6,R6,R1;
	
EVEN	ADD R0,R0,#1;
	ADD R2,R2,#-1;	
	BRp AGAIN



; Implement callee save

; No need to save any registers.

RET

SIZE .FILL x5000
PTR .FILL x5001
.END
