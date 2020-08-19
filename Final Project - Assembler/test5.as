; test 5: T defined as entry and extern as well. 
; an ext file will be created because of .extern commands
; the file will be empty because of no usage of the .extern label
; we assume maxline input of 80 chars

mov r1, r2

.extern T
.entry T
.entry T

clr DATA
inc T
DATA: .data 10
.extern T
