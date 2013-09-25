.ORIG x3000
; Your code goes here
	AND R1, R1, #0		; clears R1
	AND R2, R2, #0		; clears R2
	AND R3, R3, #0		; clears R3
	AND R4, R4, #0		; clears R4
	AND R5, R5, #0		;
	LD R0, STRING		; R1 has the memory location x4000
	LD R5, CONVERT		; R5 has the memory location x5000

STRING_CHECK
	LDR R1, R0, #0		; loads R1 with the current string char
	BRz END_STRING		; string has reach it's end
NUM
	AND R4, R4, #0		; clear R4
	LD R2, NUM_ZER		; R2 has the lower limit of the ascii of numbers
	LD R3, NUM_NIN		; R3 has the upper limit of the ascii of numbers
	JSR RANGE		; RANGE
	ADD R4, R4, #-1		; 
	BRn UPPER_CASE		; if R4 came back 1, then it is a number, else it's not.
	STR R1, R5, #0		; R1 is alpha/num so it's value gets stored
	ADD R5, R5, #1
	ADD R0, R0, #1
	BRnzp STRING_CHECK
UPPER_CASE
	AND R4, R4, #0
	LD R2, BIG_A		; R2 has the lower limit of the ascii of numbers
	LD R3, BIG_Z		; R3 has the upper limit of the ascii of numbers
	JSR RANGE
	ADD R4, R4, #-1
	BRn LOWER_CASE		; if R4 came back 1, then it is a number, else it's not
	STR R1, R5, #0		; R1 is alpha/num so it's value gets stored
	ADD R5, R5, #1
	ADD R0, R0, #1
	BRnzp STRING_CHECK
LOWER_CASE
	AND R4, R4, #0
	LD R2, SMA_A
	LD R3, SMA_Z
	JSR RANGE
	ADD R4, R4, #-1
	BRn SKIP
	STR R1, R5, #0		; R1 is alpha/num so it's value gets stored
	ADD R5, R5, #1
	ADD R0, R0, #1		;
SKIP
	ADD R0, R0, #1
	BRnzp STRING_CHECK
END_STRING
	HALT

STRING	.FILL	x4000
CONVERT	.FILL	x5000
NUM_ZER	.FILL	#48		;ASCII for 0
NUM_NIN	.FILL	#57
SMA_A	.FILL	#97
SMA_Z	.FILL	#122
BIG_A	.FILL	#65
BIG_Z	.FILL	#90



RANGE
; Input R1,R2,R3
; Output R4=1 if R2<=R1<=R3 0 otherwise    

; Your code goes here too
	ST R7, RANGE_SAVER7
	ST R0, RANGE_SAVER0
	ST R5, RANGE_SAVER5
	ST R1, RANGE_SAVER1

	AND R0, R0, #0		; temporary arithmetic register
	AND R5, R5, #0		; used to make the number negative
	NOT R5, R1		;
	ADD R5, R5, #1		; R5 is now -R1
	ADD R0, R2, R5		;
	BRp GO_BACK
	AND R0, R0, #0		;
	ADD R0, R3, R5		;
	BRn GO_BACK
	ADD R4, R4, #1
GO_BACK
	LD R1, RANGE_SAVER1
	LD R5, RANGE_SAVER5
	LD R0, RANGE_SAVER0
	LD R7, RANGE_SAVER7
 	RET

RANGE_SAVER0	.BLKW #1
RANGE_SAVER5	.BLKW #1
RANGE_SAVER7	.BLKW #1
RANGE_SAVER1	.BLKW #1

.END
