;                          tab:8
;
; prog3.asm - starting code for ECE198KL Spring 2013 Program 3
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
; Author:       Steve Lumetta
; Version:      1.00
; Creation Date:    26 January 2013
; Filename:     prog3.asm
; History:
;  SL 1.00  26 January 2013
;     First written.
;

   .ORIG x3000    ; starting address is x3000

;INTRO: I first made a loop to go through the database. If a NULL
; is read first, the loop terminates and will print what is stored
; in the array. If it is not NULL, the each character in the string
; will be read until a NULL is found, then the three choices and the
; addr of the beginning of the string will be stored in the array.
; If a NULL appears right after the three choices, my program will
; print requested values in the array in the requested format. 
; Printing consists of storing the choices in registers and printing
; those values.

;R0: Keeps track of the current array address
;R1: Holds the choice information
;R2: Count for the number of times the string address is stored in the array.
;R3: Holds each string starting address
	;Used to see if we have printed the right number of pages.
;R4: Reads the values stored in the database.
;R5: Holds the choice values
;R6: Keeps track of the current database address
;R7: Unused.

DATABASE_MEMORY_STORAGE
	LD R0, DATA			; R0 has the value x4000 (Array memory location)
	AND R6, R6, #0		; clear R6
	AND R2, R2, #0		; clear R2
	AND R5, R5, #0		; clear R5
	LD R6, STRING_START	; R6 has the value x5000 (database start address)
END_OF_DATABASE
	AND R3, R3, #0		; clears R3 of its prior value
	ADD R3, R6, #0		; R3 has the String Text Address
	LDR R4, R6, #0		; Loads the value at address in R6 into R4
	BRz PRINT_ARRAY		; If Null, end the loop
DATABASE_LOOP
	ADD R6, R6, #1		; add the counter to R6 (the current database address)
	LDR R4, R6, #0		; Load the value at address R6 into R4
	BRnp DATABASE_LOOP 	; if Database is not null, continue to increment
	STR R3, R0, #0		; R0 now has the location of where the string started
	ADD R2, R2, #1		;
ARRAY_LOOP	
	ADD R0, R0, #1		; add the counter to R0 (the current array address)
	ADD R6, R6, #1		; add the counter to R6 (the current database address)
	LDR R1, R6, #0		; load the value at address R6 to R1 (String text)
	STR R1, R0, #0		; store choice information at memory location of value R0

	ADD R0, R0, #1		; add the counter to R0 (the current array address)
	ADD R6, R6, #1		; add the counter to R6 (the current database address)
	LDR R1, R6, #0		; load the value at address R6 to R1 (String text)
	STR R1, R0, #0		; store choice information at memory location of value R0
	
	ADD R0, R0, #1		; add the counter to R0 (the current array address)
	ADD R6, R6, #1		; add the counter to R6 (the current database address)
	LDR R1, R6, #0		; load the value at address R6 to R1 (String text)
	STR R1, R0, #0		; store choice information at memory location of value R0
	ADD R0, R0, #1		; increment array address
	ADD R6, R6, #1		; increments the database addr to the next one.
	BRnzp END_OF_DATABASE
PRINT_ARRAY
	AND R1, R1, #0		; clear R1
	AND R6, R6, #0		; clear R6
	AND R4, R4, #0		; clear R4
	AND R5, R5, #0		; clear R5
	AND R0, R0, #0		; clear R0
	LD R0, DATA			; R0 has the value x4000
	NOT R2, R2			; Complement of R2 (totaly number of pages)
	ADD R2, R2, #1		; -(total number of pages)
	ADD R6, R6, #-1		; R6 is -1
PRINT_LOOP
	ADD R6, R6, #1		; Add 1 to the page count
	ADD R0, R0, #1		; increment array address
	LDR R1, R0, #0		; Load R1 with the first hexadecimal number
	ADD R0, R0, #1		; increment array address
	LDR R4, R0, #0		; Load R4 with the second hexadecimal number
	ADD R0, R0, #1		; increment array address
	LDR R5, R0, #0		; Load R5 with the third hexadecimal number
	JSR PRINT_LINE		; Print the current page
	ADD R0, R0, #1		; increment array address
	AND R3, R3, #0		; clear R3
	ADD R3, R6, R2		; See if the loop still has more pages to print.
	ADD R3, R3, #1		; compensate because R6's count starts from 0.
	BRn PRINT_LOOP		; keep printing if the total number of pages has not been printed.
	BRnzp LETS_PLAY


;
; For Program 2, you must wrap the following code up as a subroutine.
;
; This code relies on another subroutine called PRINT_CHAR
;   that prints a single ASCII character in the low 8 bits of R2
;   to the monitor.  The PRINT_CHAR call must not change any registers
;   (other than R7)!
;

;
; Subroutine PRINT_HEX_DIGIT
;   input: R3 -- 8-bit value to be printed as hex (high bits ignored)
;   caller-saved registers: R7 (as always with LC-3)
;   callee-saved registers: all other registers

; This subroutine will use the PRINT_CHAR subroutine instead of OUT
; to print each hexadecimal number. It will convert it's input (R3)
; value into it's ASCII value which will then be used as an input 
; for PRINT_CHAR.

PRINT_HEX_DIGIT

; registers used in this subroutine
;   R2 -- ASCII character to be printed
;   R3 -- 8-bit value to be printed as hex (high bits ignored)
;   R4 -- bit counter
;   R5 -- digit counter
;   R6 -- temporary
 ; store registers
; print low 8 bits of R3 as hexadecimal
; shift R3 up 8 bits
	ST	R2,HEX_DIGIT_R2
	ST	R3,HEX_DIGIT_R3
	ST	R4,HEX_DIGIT_R4
	ST	R5,HEX_DIGIT_R5
	ST	R6,HEX_DIGIT_R6
	ST	R7,HEX_DIGIT_R7

	AND R2,R2,#0		; initialize shift count to 8
	ADD R2,R2,#8
SHIFT_LOOP
	ADD R3,R3,R3		; shift one bit
	ADD R2,R2,#-1		; count down
	BRp SHIFT_LOOP		; keep going until we're done

	AND R5,R5,#0		; initialize digit count to 0
DIG_LOOP
	AND R4,R4,#0		; initialize bit count to 0
	AND R2,R2,#0		; initialize current digit to 0
BIT_LOOP
	ADD R2,R2,R2		; double the current digit (shift left)
	ADD R3,R3,#0		; is the MSB set?
	BRzp MSB_CLEAR
	ADD R2,R2,#1		; if so, add 1 to digit
MSB_CLEAR
	ADD R3,R3,R3		; now get rid of that bit (shift left)
	ADD R4,R4,#1		; increment the bit count
	ADD R6,R4,#-4		; have four bits yet?
	BRn BIT_LOOP		; if not, go get another

	ADD R6,R2,#-10		; is the digit >= 10?
	BRzp HIGH_DIGIT		; if so, we need to print a letter
	LD R6,ASC_ZERO		; add '0' to digits < 10
	BRnzp PRINT_DIGIT
HIGH_DIGIT
	LD R6,ASC_HIGH		; add 'A' - 10 to digits >= 10
PRINT_DIGIT
	ADD R2,R2,R6		; calculate the digit
	ST R7,DIGIT_R7
	JSR PRINT_CHAR		; print the digit
	LD R7,DIGIT_R7
	ADD R5,R5,#1		; increment the digit count
	ADD R6,R5,#-2		; printed both digits yet?
	BRn DIG_LOOP		; if not, go print another

	LD	R2,HEX_DIGIT_R2
	LD	R3,HEX_DIGIT_R3
	LD	R4,HEX_DIGIT_R4
	LD	R5,HEX_DIGIT_R5
	LD	R6,HEX_DIGIT_R6
	LD	R7,HEX_DIGIT_R7

	; restore again
	; THIS CODE WILL NOT WORK AS IS!

	RET


;
; Subroutine PRINT_CHAR
;   input: R2 -- 8-bit ASCII character to print to monitor
;   caller-saved registers: R7 (as always with LC-3)
;   callee-saved registers: all other registers
;

; This subroutine prints each line of the requested output array.
; PRINT_LOOP uses this subroutine in a loop to print each line.
;
; R1: Holds the value for choice 1
; R2: used to print a " " (space) and new line.
; R3: Used as the input for PRINT_CHAR
; R4: Holds the value for choice 2
; R5: Holds the value for choice 3
;
PRINT_LINE 
	ST	R1, PRINT_VALUE_R1
	ST	R2, PRINT_VALUE_R2
	ST	R6, PRINT_VALUE_R6
	ST	R4, PRINT_VALUE_R4
	ST	R5, PRINT_VALUE_R5
	ST  R7, PRINT_VALUE_R7

	LD R2, SPACE 		; sets R0 to space ASCII
	AND R3,R3,#0 		; clears R3
	ADD R3,R6,#0 		; sets R3 to the page counter
	JSR PRINT_HEX_DIGIT ; prints the value in R3
	LD R2, SPACE
	JSR PRINT_CHAR		; prints a space 
	AND R3,R3,#0 		; clears R3
	ADD R3,R1,#0 		; sets R3 to choice one
	JSR PRINT_HEX_DIGIT ; prints choice 1
	LD R2, SPACE
	JSR PRINT_CHAR		; prints space
	AND R3,R3,#0 		; clears R3
	ADD R3,R4,#0 		; sets R3 to choice 2
	JSR PRINT_HEX_DIGIT ; prints choice 2
	LD R2, SPACE
	JSR PRINT_CHAR		; prints space
	AND R3,R3,#0 		; clears R3
	ADD R3,R5,#0 		; sets R3 to choice 3
	JSR PRINT_HEX_DIGIT ; prints choice 3
	AND R2,R2,#0 		; clears R2
	ADD R2,R2,#10		; new line
	JSR PRINT_CHAR		; prints new line.

	LD	R1, PRINT_VALUE_R1
	LD	R2, PRINT_VALUE_R2
	LD	R6, PRINT_VALUE_R6
	LD	R4, PRINT_VALUE_R4
	LD	R5, PRINT_VALUE_R5
	LD  R7, PRINT_VALUE_R7
	RET		;


; Prints characters to the screen. Used instead of OUT.

; R0: temporary registed used to copy the request output
; 		char to DDR
; R2: Input. Contains the ASCII value of the char to
; 		be printed.
; 
PRINT_CHAR
	ST	R0,PRINT_CHAR_R0	; save R0 to memory
	ST	R7,PRINT_CHAR_R7	; save R7 to memory...why?
	ADD	R0,R2,#0		; copy from R2
START
	LDI R2, DSR		;
	BRzp START		;
	STI R0, DDR		;
		; restore R0 from memory
	LD	R0,PRINT_CHAR_R0
	LD	R7,PRINT_CHAR_R7	; restore R7 from memory...why?
	RET

; DATA FOR ALL SUBROUTINES AND FUNCTIONS::::::::
ASC_ZERO	.FILL x0030	; ASCII '0'
ASC_HIGH	.FILL x0037	; ASCII 'Adsd' - 10
DDR				.FILL xFE06
DSR				.FILL XFE04
DIGIT_R7		.BLKW #1
PRINT_CHAR_R0	.BLKW #1
PRINT_CHAR_R7	.BLKW #1
HEX_DIGIT_R2	.BLKW #1
HEX_DIGIT_R3	.BLKW #1
HEX_DIGIT_R4	.BLKW #1
HEX_DIGIT_R5	.BLKW #1
HEX_DIGIT_R6	.BLKW #1
HEX_DIGIT_R7	.BLKW #1
PRINT_VALUE_R1	.BLKW #1
PRINT_VALUE_R2	.BLKW #1
PRINT_VALUE_R6	.BLKW #1
PRINT_VALUE_R4	.BLKW #1
PRINT_VALUE_R5	.BLKW #1
PRINT_VALUE_R7	.BLKW #1
STRING_START 	.FILL x5000		; Address for the start of the database.
DATA			.FILL x4000		; Address for start of the array.
SPACE 			.FILL #32		; ASCII value for a space


; You may need to move these strings to be close to your game play loop.

;MP3: INTRO: My program will first upload each choice value into registers
;and will check if the first choice is negative, indicating the
;program is going to end. If it is not negative, it will print 
;the story text, followed by the prompt. Then the player must
;enter a key. First it will check if the key selected is 1, 2 or 3.
;If it is, then it read the value of that choice. If it is negative
;the choice is invalid, if it is correct, the value is multiplied
;by four and my code will then read the values at the page number. 
;This is followed by going back to the beginning of the program.
;If the selected key is invalid, the program will repeat the story
;test and the prompt.

;R0: Used to printing STRINGZ.
;R1: Has the value x4000, which is the addr for the start of the array
;R2: Used as the input for PRINT_CHAR and numerical value of the key pressed
;	We only care about 1,2,3, so if any other key will result in an invalid
;R3: Holds the value of choice 1
;R4: Holds the value of choice 2
;R5: Holds the value of choice 3
;R6: Temporary register. 
;R7:	Unused
	
LETS_PLAY
	AND R0, R0, #0		; clears R0
	AND R1, R1, #0		; clears R1
	AND R2, R2, #0		; clears R2
	AND R3, R3, #0		; clears R3
	AND R4, R4, #0		; clears R4
	AND R5, R5, #0		; clears R5
	AND R6, R6, #0		; clears R6
	LD R1, DATA			; R0 has the current array addr.
INTRO_STRING
	AND R0, R0, #0		; clear R0
	LEA R0,P3_START_STR ; R0 has the starting addr for the intro string
	PUTS				; prints the value at R0 and increments until NULL

END_CHECKER	
	LDR R3, R1, #1		; R3 has the value of choice 1
	BRn END_LAST_STR	; If the first choice is negative, ends the program
	LDR R4, R1, #2		; R4 has the value of choice 2
	LDR R5, R1, #3		; R5 has the value of choice 3
PRINT_PROMPT
	AND R6, R6, #0		; Clear R6
	ADD R6, R1, #0		; Gives R6 the value of R1
STORY_TEXT
	LDR R0, R6, #0		; R6 has the value of the addr of the string 
	PUTS				; Prints the story text of the requested page
ANSWER
	AND R0, R0, #0		; clears R0
	LEA R0,P3_PROMPT_STR ; R0 contains the string addr of the prompt string.
	PUTS				; prints the prompt string
	GETC				; waits for the player to type and key and stores it in R0
	AND R2, R2, #0		; clear R2
	ADD R2, R0, #0		; load R2 with the value the player types
	JSR PRINT_CHAR		; Printing the choice the player picks
	AND R2, R2, #0		; clears R2
	ADD R2, R2, #10		; R2 has the ascii value of a new line
	JSR PRINT_CHAR		; Prints a new line
	AND R2, R2, #0		; clears R2
	ADD R2, R2, #10		; R2 has the ascii value of a new line
	JSR PRINT_CHAR		; Prints a new line
INVALID_CHECK
	AND R2, R2, #0		; clear R2
	AND R6, R6, #0		; clears R6
	LD R6, ASCII_CHOICE	; loads R6 with -48
	ADD R2, R0, R6		; R2 has the numerical value of the key pressed
	AND R6, R6, #0		; clear R6
	ADD R6, R2, #-1		; see if the player pressed 1
	BRz CHOICE_ONE		; player pressed 1 because 1-1=0, go to choice_one
	AND R6, R6, #0		; clears R6
	ADD R6, R2, #-2		; see if the player pressed 2
	BRz CHOICE_TWO		; player pressed 2 because 2-2=0, go to choice_two
	AND R6, R6, #0		; clears R6
	ADD R6, R2, #-3		; see if player pressed 3
	BRz CHOICE_THREE	; player pressed 3 because 3-3=0, go to choice_three
INVALID
	AND R0, R0, #0		; clears R0
	LEA R0,P3_INVALID_STR ; R0 has the starting addr of the INVALID string
	PUTS				; prints the invalid string
REPEAT
	AND R6, R6, #0		; clear R6
	ADD R6, R1, #0		; R6 has the addr of the current page/string
	LDR R0, R1, #0		; R0 has the addr of the string to be printed
	PUTS				; prints the string at the current page
	BRnzp ANSWER		; Goes to allow the player to pick a choice.
CHOICE_ONE
	ADD R3, R3, #0		; calls the value of R3
	BRn INVALID			; if choice 1 is negative, do the invalid function
	LD R1, DATA			; R1 has the value x4000, where array starts
	ADD R1, R1, R3		;
	ADD R1, R1, R3		;
	ADD R1, R1, R3		;
	ADD R1, R1, R3		; This and the above 3 lines mutiple the choice value by 4
	BRnzp END_CHECKER	; Goes to the beginning and restarts with new page/choice info
CHOICE_TWO
	ADD R4, R4, #0		; calls the value of R4
	BRn INVALID			; if choice 2 is negative, do the invalid function
	LD R1, DATA			; R1 has the value x4000, where array starts
	ADD R1, R1, R4		;
	ADD R1, R1, R4		;
	ADD R1, R1, R4		;
	ADD R1, R1, R4		; This and the above 3 lines mutiple the choice value by 4
	BRnzp END_CHECKER	; Goes to the beginning and restarts with new page/choice info
CHOICE_THREE
	ADD R5, R5, #0		; calls the value of R5
	BRn INVALID			; if choice 3 is negative, do the invalid function
	LD R1, DATA			; R1 has the value x4000, where array starts
	ADD R1, R1, R5		;
	ADD R1, R1, R5		;
	ADD R1, R1, R5		;
	ADD R1, R1, R5		; This and the above 3 lines mutiple the choice value by 4
	BRnzp END_CHECKER	; Goes to the beginning and restarts with new page/choice info
END_LAST_STR
	LDR R0, R1, #0		; Loads R0 with the addr of the last string
	PUTS				; prints the last string of the story	
END	
	AND R0, R0, #0		; clears R0
	LEA R0, P3_END_STR	; Loads R0 with the addr of END_STR
	PUTS				; prints END_STR

HALT
	
ASCII_CHOICE	.FILL #-48

P3_START_STR	.STRINGZ "\n\n--- Starting adventure. ---\n\n"
P3_PROMPT_STR	.STRINGZ "Please enter your choice: "
P3_INVALID_STR	.STRINGZ "--- Invalid choice. ---\n\n"
P3_END_STR  	.STRINGZ "\n--- Ending adventure. ---\n\n"


   ; the directive below tells the assembler that the program is done
   ; (so do not write any code below it!)

   .END


