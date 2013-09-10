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



; PUT YOUR CODE FROM PROGRAM 2 HERE (without copying .ORIG / .END)



; You may need to move these strings to be close to your game play loop.

P3_START_STR   .STRINGZ "\n\n--- Starting adventure. ---\n\n"
P3_PROMPT_STR  .STRINGZ "Please enter your choice: "
P3_INVALID_STR .STRINGZ "\n\n--- Invalid choice. ---\n\n"
P3_END_STR  .STRINGZ "\n\n--- Ending adventure. ---\n\n"

;
; Subroutine PRINT_FOUR_HEX
;   prints four one-byte hex values, separated by spaces
;   inputs: R0 -- page number (first value printed)
;           R2 -- pointer to following three values (in memory)
;   caller-saved registers: R7 (as always with LC-3)
;   callee-saved registers: all other registers
;

PRINT_FOUR_HEX

   ; R2 holds an ASCII SPACE (for printing with PRINT_CHAR)
   ; R3 holds the hex value to print (with PRINT_HEX_DIGIT)
   ; R4 holds the pointer to the value array (moved from input R2)
   ; R5 is a loop counter

   ST R2,PFH_R2      ; save registers
   ST R3,PFH_R3
   ST R4,PFH_R4
   ST R5,PFH_R5
   ST R7,PFH_R7

   ADD R3,R0,#0      ; print the first digit
   JSR PRINT_HEX_DIGIT

   AND R5,R5,#0      ; prepare for loop
   ADD R4,R2,#0
   LD R2,SPACE
PFHLOOP
   JSR PRINT_CHAR    ; print space, then hex value
   LDR R3,R4,#0
   JSR PRINT_HEX_DIGIT

   ADD R4,R4,#1      ; advance pointer
   ADD R5,R5,#1      ; done three yet?
   ADD R3,R5,#-3     ; R3 can be overwritten for now
   BRn PFHLOOP

   LD R2,PFH_R2      ; restore registers
   LD R3,PFH_R3
   LD R4,PFH_R4
   LD R5,PFH_R5
   LD R7,PFH_R7

   RET

   ; data for PRINT_FOUR_HEX

PFH_R2   .BLKW #1
PFH_R3   .BLKW #1
PFH_R4   .BLKW #1
PFH_R5   .BLKW #1
PFH_R7   .BLKW #1
SPACE    .FILL x0020




   ; the directive below tells the assembler that the program is done
   ; (so do not write any code below it!)

   .END


