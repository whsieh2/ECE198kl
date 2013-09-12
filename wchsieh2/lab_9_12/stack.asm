   .ORIG x3000








   ;YOUR CODE GOES HERE
   ;USE THE PUSH AND POP SUBROUTINES PROVIDED 









   
STRING_START
   .STRINGZ "gg"

STORE_m
   .FILL x1

; PUSH subroutine pushes R1 onto the stack

PUSH
   
   ST R0, PUSH_R0
   ST R1, PUSH_R1
   ST R2, PUSH_R2
   ST R3, PUSH_R3
   ST R4, PUSH_R4
   ST R5, PUSH_R5
   ST R6, PUSH_R6
   
   LD R0, TOP
   ADD R0,R0,#-1
   STR R1,R0,#0
   ST R0, TOP
      
END_PUSH

   LD R0, PUSH_R0
   LD R1, PUSH_R1
   LD R2, PUSH_R2
   LD R3, PUSH_R3
   LD R4, PUSH_R4
   LD R5, PUSH_R5
   LD R6, PUSH_R6 

   RET

PUSH_R0  .BLKW #1
PUSH_R1  .BLKW #1
PUSH_R2  .BLKW #1
PUSH_R3  .BLKW #1
PUSH_R4  .BLKW #1
PUSH_R5  .BLKW #1
PUSH_R6  .BLKW #1
TOP      .FILL x3000
BOTTOM   .FILL x3000







; POP subroutine pops the top of the stack into R3

POP

   ST R0, POP_R0
   ST R1, POP_R1
   ST R2, POP_R2
   ST R3, POP_R3
   ST R4, POP_R4
   ST R5, POP_R5
   ST R6, POP_R6

   LD R0, TOP
   LD R1, BOTTOM
   NOT R2, R0
   ADD R2,R2,#1
   ADD R2,R2,R1
   BRNZ END_POP
   LDI R3,TOP
   ADD R0,R0,#1
   ST R0, TOP
      
END_POP

   LD R0, POP_R0
   LD R1, POP_R1
   LD R2, POP_R2
  ;LD R3, POP_R3  R3 is going to be overwritten with the popped value
   LD R4, POP_R4
   LD R5, POP_R5
   LD R6, POP_R6 

   RET

POP_R0  .BLKW #1
POP_R1  .BLKW #1
POP_R2  .BLKW #1
POP_R3  .BLKW #1
POP_R4  .BLKW #1
POP_R5  .BLKW #1
POP_R6  .BLKW #1

   .END
