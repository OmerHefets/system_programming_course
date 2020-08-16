/**
 * This modules has all functions for compiling an instruction line in the first pass only, and all functions for coding the instruction line to binary machine code.
 * the coding is done with masking the correct value of the specific bits of each part of the word: ARE, funct, registers and addressing method, opcode.
 */

#include "assembler.h"

/* get an instruction line and compile it according to the number of operands it has */
void compile_instruction_line(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head, int *ic)
{
    /* we already checked that the line is correct in the pass, so we assume that the number of arguments are correct */
    int num_of_operands = opcodes_number_of_operands[get_command_index(command)];
    if (num_of_operands == 0) { /* using numbers and not defined values because it is more readable like that */
        compile_instruction_line_zero_operands(command, symbol_head, instruction_head, ic);
    } else if (num_of_operands == 1) {
        compile_instruction_line_one_operand(args_line, command, symbol_head, instruction_head, ic);
    } else { /* there are 2 operands */
        compile_instruction_line_two_operands(args_line, command, symbol_head, instruction_head, ic);
    }
}

/* create machine code for line with with no operands */
void compile_instruction_line_zero_operands(char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head, int *ic)
{
    unsigned long int command_value = RESET_COMMAND_VALUE;
    code_are(&command_value, 'A'); /* code the A bit in the word */
    code_opcode(&command_value, command); /* code the opcode of the command */
    add_instruction(instruction_head, *ic, command_value); /* add the instruction with the command value to the instruction binary code list */
    (*ic)++; /* increase number of instruction lines by 1*/
}

/* create machine code for line with one operand */
void compile_instruction_line_one_operand(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head,
int *ic)
{
    char *delim = " \t\n";
    char *token;
    unsigned long int command_value = RESET_COMMAND_VALUE;
    token = strtok(args_line, delim); /* get operand name */
    /* code all the required fields in the word */
    code_are(&command_value, 'A');
    code_opcode(&command_value, command);
    code_funct(&command_value, command);
    code_addressing_and_register(&command_value, token, DEST);
    /* add the instruction */
    add_instruction(instruction_head, *ic, command_value);
    (*ic)++;
    /* code the operand as well (if possible) */
    compile_operand(token, instruction_head, ic);
}

/* create machine code for line with two operands */
void compile_instruction_line_two_operands(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head,
int *ic)
{
    char *delim = " \t,\n";
    char *token;
    char two_tokens[2][MAX_LABEL_SIZE] = {"", ""};
    unsigned long int command_value = RESET_COMMAND_VALUE;
    /* save the two operands in two tokens */
    token = strtok(args_line, delim);
    strncat(two_tokens[FIRST_OPERAND], token, strlen(token));
    token = strtok(NULL, delim);
    strncat(two_tokens[SECOND_OPERAND], token, strlen(token));
    /* code the required fields in the word */
    code_are(&command_value, 'A');
    code_opcode(&command_value, command);
    code_funct(&command_value, command);
    code_addressing_and_register(&command_value, two_tokens[FIRST_OPERAND], SRC);
    code_addressing_and_register(&command_value, two_tokens[SECOND_OPERAND], DEST);
    add_instruction(instruction_head, *ic, command_value);
    (*ic)++; /* add 1 to the instruction counter */
    /* code the operand as well (if possible) */
    compile_operand(two_tokens[0], instruction_head, ic);
    compile_operand(two_tokens[1], instruction_head, ic);
}

/* create machine code for an operand in the first pass, if possible. 
if not, binary code of 0 will be saved and revalued in the second pass */
void compile_operand(char *operand, InstructionPtr *instruction_head, int *ic)
{
    unsigned long int command_value = RESET_COMMAND_VALUE;
    unsigned long int operand_value;
    int operand_type = get_operand_type(operand);
    /* create the machine code only if the addressing method is immediate addressing */
    if (operand_type == IMMEDIATE_ADDRESSING) { 
        code_are(&command_value, 'A');
        operand_value = get_number_from_operand_adressing_zero(operand);
        command_value += (operand_value <<= SHIFT_BITS_FROM_A_R_E_CODING);
    } else if (operand_type == REGISTER_ADDRESSING) {
        return;
    }
    add_instruction(instruction_head, *ic, command_value);
    (*ic)++;
}

/* code the A_R_E bits to a word */
void code_are(unsigned long int *command, char a_r_e)
{
    if (a_r_e == 'A') {
        *command |= A_BIT; /* use or to turn the required bit to 1 as needed */
    } else if (a_r_e == 'R') {
        *command |= R_BIT;
    } else { /* the char is 'E' */
        *command |= E_BIT;
    }
}

/* code the funct value to a word */
void code_funct(unsigned long int *command, char *command_name)
{
    unsigned long int coded_funct = RESET_COMMAND_VALUE; /* reset funct value to zero */
    int index = get_command_index(command_name);
    coded_funct = opcodes_funct[index]; /* set funct value according to the opcode and its index (defined seperately) */
    coded_funct <<= SHIFT_BITS_TO_FUNCT; /* shift the bits to the funct position (5 bits left) */
    *command |= coded_funct;
}

/* code the opcode value to a word */
void code_opcode(unsigned long int *command, char *command_name)
{
    unsigned long int coded_opcode = RESET_COMMAND_VALUE;
    int index = get_command_index(command_name);
    coded_opcode = opcodes_opcode[index]; /* set the opcode value */
    coded_opcode <<= SHIFT_BITS_TO_OPCODE; /* shift the value to the 18-23 bits of the word */
    *command |= coded_opcode;
}

/* code the addressing method and number of register to a word */
void code_addressing_and_register(unsigned long int *command, char *operand, int src_or_dest)
{
    unsigned long int coded_value = RESET_COMMAND_VALUE;
    int operand_type = get_operand_type(operand);
    if (operand_type == IMMEDIATE_ADDRESSING) {
        return; /* method 0 and 000 in register value */
    } else if (operand_type == DIRECT_ADDRESSING) {
        coded_value = DIRECT_OPERAND_BITS; /* set method bits to 01 (value 8 in a 5 bits word) */
    } else if (operand_type == RELATIVE_ADDRESSING) {
        coded_value = RELATIVE_OPERAND_BITS; /* set method bits to 10 (value 16 in a 5 bits word) */
    } else { /* method 3*/
        coded_value = (REGISTER_OPERAND_BITS + get_register_index(operand)); /* 11 for method 3 + register number */
    }
    if (src_or_dest == SRC) {
        coded_value <<= SHIFT_BITS_TO_SRC; /* shift 13 if its source */
    } else {
        coded_value <<= SHIFT_BITS_TO_DEST; /* shift 8 if its the destination */
    }
    *command |= coded_value;
}
