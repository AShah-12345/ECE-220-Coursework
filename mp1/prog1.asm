; partners: devdp2, loganeh2
; Aryan Shah, ECE 220 FA22
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
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



PRINT_HIST

; The purpose of this code is to modify existing code to print a histogram.
; Added code includes inserting an ASCII space, print the space, a binary
; to hexadecimal converter, and finally a converter to the histogram values.
; This binary to hexadecimal converter was written in LC3 from the given
; flowchart on the ECE 220 webpage. Logic in this program includes left
; shift to check if the most significant bit is one or zero, based on
; which will add a one to an output register, which also be left shifted.
; This will run through until 4 bits, then it will ensure that the output
; register has a value greater than 9. If so, the ASCII value for 'A' will
; be added, else the ASCII value for '0' will be added. This ensures
; that the OUT TRAP function outputs the proper char. This process
; repeats until all the 16 bits are outputted.

; Description of each register used:
; R0 holds ASCII value to char to be printed
; R1 used to figure out if char to be printed is letter or number, then adds to R0 accordingly
; R2 used as counter of bits printed starting at 4
; R3 is current memory address and is altered with a left shift when necessary
; R4 is counter of lines printed, starting at 27, decrementing each time the loop is completed
; R5 is used to print letter from histogram and a space afterwards and is also sometimes used as temporary counter as necessary
; R6 holds memory address of current hex to be printed to the monitor

LD R5, ASCII_AT ; loads ASCII value for @ symbol in R5
LD R4, HIST_LOOPS ; loads 27 into R4
LD R6, HIST_ADDR ; loads mem loc for current ASCII char

OUTPUT
	ADD R0, R5, #0 ; prints character in R5
	OUT ; prints out a character to the screen
	LD R0, SPACE ; print a space
	OUT ; prints out a space to the screen
	LDR R3, R6, #0 ; loads memory address at R6 into R3
	LD R2, BITCOUNT ; loads 4 as bit counter into R2
	AND R0, R0, #0 ; clear R0
NEXT_HEX
	LD R1, BITCOUNT ; loads 4 as bit counter into R1
LSHIFT_HEX
	ADD R0, R0, R0 ; left shift R0
	ADD R3, R3, #0 ; add 0 to R3 to put into PC
	BRzp LSHIFT_R3 ; MSB of R3 is 0 then add 0, if 1 add 1
	ADD R0, R0, #1 ; add 1 to R0 as stated above
LSHIFT_R3
	ADD R3, R3, R3 ; left shift R3
	ADD R1, R1, #-1 ; decrease bit counter by 1
	BRp LSHIFT_HEX ; loops back to LSHIFT_HEX if bits left to print
HEX_TO_ASCII
	ADD R0, R0, #-9 ; checks if R0 is < or equal to 9
	BRp ASCII_A ; branches to add 'A' if R0 > 9
ASCII_ZERO
	ADD R0, R0, #9 ; adds back 9 to R0
	ADD R0, R0, #15 ; adds ASCII '0' to R0, which is 48
	ADD R0, R0, #15 ; adds 15 to R0 to total to 30
	ADD R0, R0, #15 ; adds 15 to R0, to total to 45
	ADD R0, R0, #3 ; adds 3 to R0, to total to 48
	BR HEX_PRINT ; branches to print hex no matter value of R0
ASCII_A
	ADD R0, R0, #9 ; adds back 9 to R0
	ADD R0, R0, #15 ; adds ASCII 'A" to R0, which is 55
	ADD R0, R0, #15 ; adds 15 to R0, to total to 30
	ADD R0, R0, #15 ; adds 15 to R0, to total to 45
	ADD R0, R0, #10 ; adds 10 to R0, to total to 55
HEX_PRINT
	OUT ; prints output
	AND R0, R0, #0 ; clears R0
	ADD R2, R2, #-1 ; reduce digit counter by 1
	BRp NEXT_HEX ; branches to to NEXT_HEX to repeat it 4 times
NL
	AND R0, R0, #0 ; clear R0
	ADD R0, R0, #10 ; adds ASCII value for a space into R0
	OUT ; prints space

ADD R5, R5, #1 ; loads next char into R5
ADD R6, R6, #1 ; points to next character in the histogram
ADD R4, R4, #-1 ; subtracts amount of lines to be printed
BRp OUTPUT ; branch to output loop

DONE	HALT			; done

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
ASCII_AT	.FILL x40	; ASCII value for @ symbol
HIST_LOOPS	.FILL #27	; number of lines PRINT_HIST prints
SPACE		.FILL x20	; space ASCII value
BITCOUNT	.FILL #4	; Bit counter to loop 4 times

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."




	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
