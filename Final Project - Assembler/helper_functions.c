#include "assembler.h"

int get_command_index(char *command)
{
    int i;
    for (i=0 ; i < NUM_OF_OPCODES ; i++) {
        if (!strcmp(command, opcodes[i])) {
            return i;
        }
    }
    return NONE;
}

int get_register_index(char *reg)
{
    int i;
    for (i=0 ; i < NUM_OF_REGISTERS ; i++) {
        if (!strcmp(reg, registers[i])) {
            return i;
        }
    }
    return NONE;
}

int get_operand_type(char *operand)
{
    char temp_operand[MAX_LABEL_SIZE] = "";
    char temp_operand2[MAX_LABEL_SIZE] = "";
    if (operand == NULL) {
        return NONE;
    }
    strncat(temp_operand, operand, strlen(operand));
    strncat(temp_operand, ":", 1);
    if (operand[0] == '#') {
        operand++;
        if (check_data_argument(operand) == FALSE) {
            return NONE;
        } else {
            return IMMEDIATE_ADDRESSING;
        }
    } else if (check_correct_label(temp_operand)) {
        return DIRECT_ADDRESSING;
    }
    strncat(temp_operand2, operand+1, strlen(operand)-1);
    strncat(temp_operand2, ":", 1);
    if (operand[0] == '&' && check_correct_label(temp_operand2)) {
        return RELATIVE_ADDRESSING;
    } else if (check_correct_register(operand)) {
        return REGISTER_ADDRESSING;
    }
    return NONE;
}

long get_number_from_operand_adressing_zero(char *operand)
{
    char num_in_string[MAX_LABEL_SIZE] = "";
    strncat(num_in_string, operand+1, strlen(operand)-1);
    return atol(num_in_string);
}