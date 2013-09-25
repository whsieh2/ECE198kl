   ;Sample_input for problem 3 of Midterm 1.
   ;Feel free to change this file

   .ORIG x4000

   .FILL xE9A1

   .END


;Below is the output from a correctly running
;implementation using sample_graph and sample_input


;linux-v1.ews.illinois.edu > lc3sim sample_graph.obj 
;
;Welcome to the LC-3 simulator.
;
;The contents of the LC-3 tools distribution, including sources, management
;tools, and data, are Copyright (c) 2003 Steven S. Lumetta.
;
;The LC-3 tools distribution is free software covered by the GNU General
;Public License, and you are welcome to modify it and/or distribute copies
;of it under certain conditions.  The file COPYING (distributed with the
;tools) specifies those conditions.  There is absolutely no warranty for
;the LC-3 tools distribution, as described in the file NO_WARRANTY (also
;distributed with the tools).
;
;Have fun.
;
;
;--- halting the LC-3 ---
;
;PC=x0494 IR=xB1AE PSR=x0400 (ZERO)
;R0=x0000 R1=x7FFF R2=x0000 R3=x0000 R4=x0000 R5=x0000 R6=x0000 R7=x0490 
;                   x0494 x0FF9 BRNZP TRAP_HALT
;Loaded "sample_graph.obj" and set PC to x7000
;(lc3sim) file sample_input.obj
;Loaded "sample_input.obj" and set PC to x4000
;(lc3sim) file traverse.obj
;Loaded "traverse.obj" and set PC to x3000
;(lc3sim) c
;
;
;--- halting the LC-3 ---
;
;PC=x0494 IR=xB1AE PSR=x0400 (ZERO)
;R0=x0000 R1=x7FFF R2=x0000 R3=x6011 R4=x0000 R5=x0000 R6=x0000 R7=x0490 
;                   x0494 x0FF9 BRNZP TRAP_HALT
;(lc3sim) dump x6000
;6000: 7000 7002 7004 7006 7006 7002 7000 7000 7002 7004 7000 7002  ............
;600C: 7000 7000 7000 7000 7002 0000 0000 0000 0000 0000 0000 0000  ............
;6018: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  ............
;6024: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  ............
;6030: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  ............
;603C: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  ............
;6048: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  ............
;6054: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000  ............
;(lc3sim) quit
;

