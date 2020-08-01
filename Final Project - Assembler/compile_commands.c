#include "assembler.h"

void compile_instruction_line(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head, int *ic)
{
    int num_of_operands = opcodes_number_of_operands[get_command_index(command)];
    if (num_of_operands == 0) {
        compile_instruction_line_zero_operands(command, symbol_head, instruction_head, ic);
    } else if (num_of_operands == 1) {
        /*compile_instruction_line_one_operand();*/
    } else {
        /*compile_instruction_line_two_operands();*/
    }
}

void compile_instruction_line_zero_operands(char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head, int *ic)
{
    return;
    
}
/*
void compile_instruction_line_one_operand();

void compile_instruction_line_two_operands();
*/
unsigned long int code_are(unsigned long command, char a_r_e)
{
    if (a_r_e == 'A') {
        command |= 4;
    } else if (a_r_e == 'R') {
        command |= 2;
    } else {
        command |= 1;
    }
    return command;
}

unsigned long int code_funct(unsigned long command, char *command_name)
{
    unsigned long int coded_funct = 0;
    int index = get_command_index(command_name);
    coded_funct = opcodes_funct[index];
    coded_funct <<= 3;
    command |= coded_funct;
    return command;
}

unsigned long int code_opcode(unsigned long command, char *command_name)
{
    unsigned long int coded_opcode = 0;
    int index = get_command_index(command_name);
    coded_opcode = opcodes_opcode[index];
    coded_opcode <<= 18;
    command |= coded_opcode;
    return command;
}

unsigned long int code_src_addressing(unsigned long command, char *operand)