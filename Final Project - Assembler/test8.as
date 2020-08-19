; test 8: testing large numbers and showing the 24 bits masking mechanisem
; of the assembler and ingnoring everything else 
; we assume maxline input of 80 chars

; both these statements work with 2's complement method 
.data 5
.data -5

; this number is defined as 0001 0000 0000 0000 0000 0000 0000 
; masking it with 24 bits will produce value of 0
.data 16777216