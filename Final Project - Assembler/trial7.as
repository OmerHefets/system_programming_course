; test second pass errors in arguments or incorrect lines

.entry LIST
.extern W

.entry DOESNTEXIST
MAIN: add r3, LIST
LOOP: prn #48
    lea W2, r6
    inc r6
    mov r3,K
    sub r1, r4
    bne END
    cmp K, #-6
    bne &W
    dec W
.entry MAIN_MAIN
    jmp &LOOP
    add L3, L3
END: stop

STR: .string "abcd"
LIST: .data 6,-9
    .data -100
K: .data 31
.extern L3
