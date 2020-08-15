#include "assembler.h"

void compile_instruction_line(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head, int *ic)
{
    int num_of_operands = opcodes_number_of_operands[get_command_index(command)];
    if (num_of_operands == 0) {
        compile_instruction_line_zero_operands(command, symbol_head, instruction_head, ic);
    } else if (num_of_operands == 1) {
        compile_instruction_line_one_operand(args_line, command, symbol_head, instruction_head, ic);
    } else {
        compile_instruction_line_two_operands(args_line, command, symbol_head, instruction_head, ic);
    }
}

void compile_instruction_line_zero_operands(char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head, int *ic)
{
    unsigned long int command_value = RESET_COMMAND_VALUE;
    code_are(&command_value, 'A');
    code_opcode(&command_value, command);
    add_instruction(instruction_head, *ic, command_value);
    (*ic)++;
}

void compile_instruction_line_one_operand(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head,
int *ic)
{
    char *delim = " \t\n";
    char *token;
    unsigned long int command_value = RESET_COMMAND_VALUE;
    token = strtok(args_line, delim);
    code_are(&command_value, 'A');
    code_opcode(&command_value, command);
    code_funct(&command_value, command);
    code_addressing_and_register(&command_value, token, DEST);
    add_instruction(instruction_head, *ic, command_value);
    (*ic)++;
    compile_operand(token, instruction_head, ic);
}


void compile_instruction_line_two_operands(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head,
int *ic)
{
    char *delim = " \t,\n";
    char *token;
    char two_tokens[2][MAX_LABEL_SIZE] = {"", ""};
    unsigned long int command_value = RESET_COMMAND_VALUE;
    token = strtok(args_line, delim);
    strncat(two_tokens[FIRST_OPERAND], token, strlen(token));
    token = strtok(NULL, delim);
    strncat(two_tokens[SECOND_OPERAND], token, strlen(token));
    code_are(&command_value, 'A');
    code_opcode(&command_value, command);
    code_funct(&command_value, command);
    code_addressing_and_register(&command_value, two_tokens[FIRST_OPERAND], SRC);
    code_addressing_and_register(&command_value, two_tokens[SECOND_OPERAND], DEST);
    add_instruction(instruction_head, *ic, command_value);
    (*ic)++;
    compile_operand(two_tokens[0], instruction_head, ic);
    compile_operand(two_tokens[1], instruction_head, ic);
}


void compile_operand(char *operand, InstructionPtr *instruction_head, int *ic)
{
    unsigned long int command_value = RESET_COMMAND_VALUE;
    unsigned long int operand_value;
    int operand_type = get_operand_type(operand);
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

void code_are(unsigned long int *command, char a_r_e)
{
    if (a_r_e == 'A') {
        *command |= A_BIT;
    } else if (a_r_e == 'R') {
        *command |= R_BIT;
    } else {
        *command |= E_BIT;
    }
}

void code_funct(unsigned long int *command, char *command_name)
{
    unsigned long int coded_funct = RESET_COMMAND_VALUE;
    int index = get_command_index(command_name);
    coded_funct = opcodes_funct[index];
    coded_funct <<= SHIFT_BITS_TO_FUNCT;
    *command |= coded_funct;
}

void code_opcode(unsigned long int *command, char *command_name)
{
    unsigned long int coded_opcode = RESET_COMMAND_VALUE;
    int index = get_command_index(command_name);
    coded_opcode = opcodes_opcode[index];
    coded_opcode <<= SHIFT_BITS_TO_OPCODE;
    *command |= coded_opcode;
}

void code_addressing_and_register(unsigned long int *command, char *operand, int src_or_dest)
{
    unsigned long int coded_value = RESET_COMMAND_VALUE;
    int operand_type = get_operand_type(operand);
    if (operand_type == IMMEDIATE_ADDRESSING) {
        return;
    } else if (operand_type == DIRECT_ADDRESSING) {
        coded_value = DIRECT_OPERAND_BITS;
    } else if (operand_type == RELATIVE_ADDRESSING) {
        coded_value = RELATIVE_OPERAND_BITS;
    } else {
        coded_value = (REGISTER_OPERAND_BITS + get_register_index(operand));
    }
    if (src_or_dest == SRC) {
        coded_value <<= SHIFT_BITS_TO_SRC;
    } else {
        coded_value <<= SHIFT_BITS_TO_DEST;
    }
    *command |= coded_value;
}
