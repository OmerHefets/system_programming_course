; test 4: mixed code and data, no labels (from test 2 + test 3)
; we assume maxline input of 80 chars

add r2, r1
        .data 4

.string "lelele"
mov #5  , r0
  STR:        .data 100, +40, -5, -10
sub #-200   , r5

.data 8
     T:  .string "123"

mov r7 , r1

; fjdkfj8888888888888888888888  