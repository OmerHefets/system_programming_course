#include "assembler.h"

char *opcodes[NUM_OF_OPCODES] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", \
"red", "prn", "rts", "stop"};

int opcodes_opcode[NUM_OF_OPCODES] = {0, 1, 2, 2, 4, 5, 5, 5, 5, 9, 9, 9, 12, 13, 14, 15};

int opcodes_funct[NUM_OF_OPCODES] = {0, 0, 1, 2, 0, 1, 2, 3, 4, 1, 2, 3, 0, 0, 0, 0};

int opcodes_number_of_operands[NUM_OF_OPCODES] = {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};

int opcodes_first_operand[NUM_OF_OPCODES][MAX_POSSIBLE_OPCODES] = {{0, 1, 3}, {0, 1, 3}, {0, 1, 3}, {0, 1, 3}, {1, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}, 
{NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}, {NONE, NONE, NONE}, 
{NONE, NONE, NONE}, {NONE, NONE, NONE}};

int opcodes_second_operand[NUM_OF_OPCODES][MAX_POSSIBLE_OPCODES] = {{1, 3, NONE}, {0, 1, 3}, {1, 3, NONE}, {1, 3, NONE}, {1, 3, NONE}, {1, 3, NONE},
{1, 3, NONE}, {1, 3, NONE}, {1, 3, NONE}, {1, 2, NONE}, {1, 2, NONE}, {1, 2, NONE}, {1, 3, NONE}, {0, 1, 3},
{NONE, NONE, NONE}, {NONE, NONE, NONE}};

char *data_operations[NUM_OF_DATA_OPERATIONS] = {".data", ".string", ".entry", ".extern"};

char *registers[NUM_OF_REGISTERS] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};