; test first pass errors in arguments or incorrect lines

. entry LIST
 .ext ern W
.extern W^&#W


WW: add r4, K
.extern WW

a comment line without ; (this line will produce an error)

MAIN: add r3, #IST
*OOP: prn #48
MAIN: mov r1, K
SYSTEM: mooooov r2, r6
    lea W, r6, r2, r4
    inc &K
    mov r 3,K
    sub r1, 2r4
    bne END
    cmp K, #-6
    bne &E, ND
    dec .W
; The assembler will ignore the label and the exess definitions of MAIN
IGNORE: .entry MAIN
.entry MAIN
.entry MAIN
    jmp &LOOP
    add L3, L3
END: stop

STR: .string abcd"
LIST: .data +6,-9
    .data -10.0
K: .data 3.1
.extern L3
