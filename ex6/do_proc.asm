;----------------------------
; SystemC
; do_proc.asm
; risc assembly file
; generated from do_proc.cpp
;----------------------------

; Scans addresses between 0 and 31, and copies values greater than 127 
; up into an area of memory starting at address 32

;variable locations: -  16 registers reg[15] is Z location
;-------------------
;0   data 
;1     mi 
;2      i  
;3   dest
;4   MemStatusReg
;15     Z

; Scan until we reach the end-of-data marker (255)

LDA   0  ;0 
MOVF  0  ;1 data = 0
MOVF  2  ;2 i = 0

LDA  32  ;3
MOVF  1  ;4 mi = 0
MOVF  3  ;5 dest = 32
LDA  255 ;6
MOVF  4  ;7 MemStatusReg = 255

MOVAX 4  ;8 
MOVF  0  ;9 read memory from MemStatusReg into data

MOVA  0  ;10 A = data
DEC      ;11 --A
SZ       ;12 skip if (data == 1)
JMP  15  ;13 

JMP  21  ;14 break

LDA   0  ;15
JMP   8  ;16 loop

INC      ;17
INC      ;18
INC      ;19
INC      ;20

; mi contains the location of the marker
; copy values with MSB set to the area above address dest

LDA   0  ;21 
MOVF  2  ;22 i = 0;

MOVAX 2  ;23 
MOVF  0  ;24 read memory from address i into data

LDA 127  ;25 
SGE   0  ;26 skip if (127 >= data)
JMP  29  ;27

JMP  34  ;28

MOVA  0  ;29 
MOVXA 3  ;30 write data into memory at address dest

MOVA  3  ;31
INC      ;32
MOVF  3  ;33 ++ dest

MOVA  2  ;34 
INC      ;35 
MOVF  2  ;36 ++i;

MOVA  2  ;37 
SGE   1  ;38 skip if (i >= mi)       
JMP  23  ;39

; Finally, clear the marker

LDA   1  ;36
MOVXA 4  ;37 write 1 into MemStatusReg

JMP   0  ;38
