   ; ***** NOTE *****
   ;
   ; The output from a correct implementation
   ; of traverse.asm can be found at the bottom of the 
   ; file sample_input.asm


   .ORIG x3000

   JSR TRAVERSE

   HALT




TRAVERSE

   ; To assist us in grading, please adhere to 
   ; the following register usage

   ;R0 has the current page
   ;R1 has the input
   ;R2 has the count of iterations completed
   ;R3 has the address where the output is being stored
   ;R4-R7 are registers to use for your own purposes
   ;but be sure to document their uses here
	

   ;YOUR CODE GOES HERE
	ST R0, TRANS_R0
	ST R1, TRANS_R1
	ST R2, TRANS_R2
	ST R3, TRANS_R3
	ST R4, TRANS_R4
	ST R5, TRANS_R5
	ST R6, TRANS_R6
	ST R7, TRANS_R7
	
	LD R4, ADDR
	ADD R4, R4, R2		; 
	LDR R5, R4, #0		; R5 has the content at addr R4
	ADD R1, R1, #0		; calls the input value
	BRzp CURRENT		; if input value is 0, go to current
	ADD R4, R4, #1		; we want the content of the addr +1
	LDR R5, R4, #0		; R5 has the value if the bit is 1.
	
	
CURRENT
	STR  R5 ,R3, #0		; ADDR of output now has the content of the current addr.

	

	LD R0, TRANS_R0
	LD R1, TRANS_R1
	LD R2, TRANS_R2
	LD R3, TRANS_R3
	LD R4, TRANS_R4
	LD R5, TRANS_R5
	LD R6, TRANS_R6
	LD R7, TRANS_R7

   RET

   ;PUT ALL OF YOUR DATA VALUES (.FILLS, .BLKWS etc) BELOW
INPUT_BITS	.FILL	x4000
OUTPUT		.FILL	x6000
ADDR		.FILL	x7000
TRANS_R0	.BLKW 	#1
TRANS_R1	.BLKW 	#1
TRANS_R2	.BLKW 	#1
TRANS_R3	.BLKW 	#1
TRANS_R4	.BLKW 	#1
TRANS_R5	.BLKW 	#1
TRANS_R6	.BLKW 	#1
TRANS_R7	.BLKW 	#1
   .END

