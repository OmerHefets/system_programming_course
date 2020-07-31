#include "assembler.h"
/*
struct opcodess {
    char name[4];
    int opcode;
    int funct;
    int first_operands[3];
    int second_operands[3];
} opcodes_table[16] = {
    "mov", 0, 0, {{0, 1, 3}}, {{1, 3}},
    "cmp", 1, 0, {{0, 1, 3}}, {{0, 1, 3}},
    "add", 2, 1, {{0, 1, 3}}, {{1, 3}},
    "sub", 2, 2, {{0, 1, 3}}, {{1, 3}},
    "lea", 4, 0, {{1}}, {{1, 3}}, 
    "clr", 5, 1, {{-1}}, {{1, 3}},
    "not", 5, 2, {-1}, {1, 3},
    "inc", 5, 3, {-1}, {1, 3},
    "dec", 5, 4, {-1}, {1, 3},
    "jmp", 9, 1, {-1}, {1, 2},
    "bne", 9, 2, {-1}, {1, 2},
    "jsr", 9, 3, {-1}, {1, 2},
    "red", 12, 0, {-1}, {1, 3},
    "prn", 13, 0, {-1}, {0, 1, 3},
    "rts", 14, 0, {-1}, {-1},
    "stop", 15, 0, {-1}, {-1}
};
*/
char *opcodes[16] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", \
"red", "prn", "rts", "stop"};

char *data_operations[4] = {".data", ".string", ".entry", ".extern"};

char *registers[8] = {"r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8"};