;									tab:8
;
; prog1.asm - starting code for ECE198KL Spring 2013 Program 1
;
; "Copyright (c) 2013 by Steven S. Lumetta.
;
; Permission to use, copy, modify, and distribute this software and its
; documentation for any purpose, without fee, and without written agreement is
; hereby granted, provided that the above copyright notice and the following
; two paragraphs appear in all copies of this software.
; 
; IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
; ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
; DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
; EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
; OF THE POSSIBILITY OF SUCH DAMAGE.
; 
; THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
; WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
; MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
; PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
; THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
; SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
;
; Author:	    Steve Lumetta
; Version:	    1.00
; Creation Date:    11 January 2013
; Filename:	    prog1.asm
; History:
;	SL	1.00	11 January 2013
;		Adapted from ECE190 example code.
;

; 
;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

; INTRO: My code prints the histogram stored at x3F00. It has an up counter
; which monitors which character the program is printing as well as which 
; memory address we are currently on. It will take the number stored in memory 
; and split up the 16 bits and divide it into 4 groups. Each group is then 
; converted to hexadecimal by looping a bit shift and using BRzp to see if the 
; most significant bit is 0 or 1. After 4 iterations, the hexadecimal number is
; printed and move onto the next three groups. I add a certain number to a 
; to a regisiter depending on where the most significant bit originally was before
; the bit shift. I will then take the number and add the difference to convert it
; to its ASCII counter part and print this digit. After printing one line, the
; histogram will go to the next memory address and repeat this 26 more times.

; R0 : Initially used as a histogram address holder. It is also used to print.
; R1 : Used to store NUM_BINS
; R3 : Used as a 4 bit counter after dividing the 16 bit count into four groups.
; R4 : stores the value of the frequency of each character
; R5 : Used to convert binary to hexdecimal. 8,4,2,1 are added to this
;	   register depending on how many bit shifts have occurred.
; R6 : Line counter, used to see if we have finished the histogram
; R7 : used as the ASCII value for '@'.
PRINT_HIST
	AND R0, R0, #0		; clear R0
	AND R1, R1, #0		; clear R1
	AND R3, R3, #0		; clears R3
	AND R4, R4, #0		; clear R4
	AND R5, R5, #0		; clears R5
	AND R6, R6, #0		; clears R6
PRINTING	
	AND R3, R3, #0		; clear R3
	ADD R3, R3, #4		; initiate digit counter (groups of 4 bits)
	LD R0, HIST_ADDR 	; R0 points to the first histogram address
	ADD R0, R0, R6		; current location of the histogram
	LD R1, NUM_BINS		; R1 has the value 27
	NOT R1, R1			; complements 27, to be subtracted
	ADD R1, R1, #1		; makes 27 negative 27
	ADD R1, R6, R1		; See's if the print has done 27 iterations
	BRzp DONE			; if the loops has ran 27 times, the program halts.
	LDR R4, R0, #0		; R4 has the value in the histogram, the character count
	AND R0, R0, #0		; clears R0
	LD R7, CHAR_ASCII	; sets R7 as the ASCII value for '@'
	ADD R0, R6, R7		; sets R0 as the ASCII value for the current character
	OUT					; prints R0, which will be the corresponding character for each frequency
	LD R0, SPACE_ASCII	; sets R0 as the ASCII value for ' '.
	OUT					; prints a space
BIT_PRINTER
	AND R5, R5, #0		; clears R5
	ADD R4, R4, #0		; Used for the following BR
	BRzp FIRST_BIT		; if the most significant bit of R4 is 0, next step is skipped
	ADD R5, R5, #8		; adds 8 to the R5
FIRST_BIT
	ADD R4, R4, R4		; bit shift to the left
	BRzp SECOND_BIT		;if the most significant bit is 0, the next step is skipped
	ADD  R5, R5, #4		; adds 4 to R5
SECOND_BIT
	ADD R4, R4, R4		; bit shift to the left
	BRzp THIRD_BIT		;	if the most significant bit is 0, the next step is skipped
	ADD  R5, R5, #2		; adds 2 to R5
THIRD_BIT
	ADD R4, R4, R4		; bit shift to the left
	BRzp FOURTH_BIT		;	if the most significant bit is 0, the next step is skipped
	ADD  R5, R5, #1		; adds 1 to R5
FOURTH_BIT
	ADD R4, R4, R4		; bit shift to the left
	ADD R5, R5, #-9		; see if the count will result in a digit or a letter
	BRp LETTER			; if the count is more than 9, it is a letter and will be printed differently.
	ADD R5, R5, #9		; re-correct the count
	LD R1, NUMBER_CONVERT		; the difference between the count number and its corresponding ASCII value
	AND R0, R0, #0		; clears R0
	ADD R0, R5, R1		; convert the true value to it's corresponding ASCII value
	BRnzp PRINT			; goes to print for the 4 hexdecimal bits to be printed
LETTER
	ADD R5, R5, #9		; re-correct the count
	LD R1, LETTER_CONVERT	; the difference between the number count and it's corresponding ASCII value
	AND R0, R0, #0		; clears R0
	ADD R0, R5, R1	; converts the true value to its corresponding ASCII value
PRINT
	OUT		; Prints R0
	ADD R3, R3, #-1		; Down counts R4
	BRp BIT_PRINTER		; If R4 is still positive, it will continue to the next four bits
	ADD R6, R6, #1		; Adds 1 to the line counter
	AND R0, R0, #0		; clears R0
	ADD R0, R0, #10		; Goes to the next line
	OUT					
	BRnzp PRINTING		; goes back to the printing loop.

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
CHAR_ASCII	.FILL #64	;ASCII value @
SPACE_ASCII	.FILL #32	; Space's ASCII value
NUMBER_CONVERT	.FILL #48	; offset of numbers and their corresponding ASCII values
LETTER_CONVERT	.FILL #55	; offset of letters and their corresponding ASCII values
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
