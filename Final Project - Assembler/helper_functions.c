/** 
 * General helper functions that relate to many parts of the code and make it easier to read
 */

#include "assembler.h"

/* get command index by the definition in defined_data_structures.c */
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

/* get register index by the definition in defined_data_structures.c */
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

/* check the addressing type of an operand */
int get_operand_type(char *operand)
{
    char temp_operand[MAX_LABEL_SIZE] = "";
    char temp_operand2[MAX_LABEL_SIZE] = "";
    if (operand == NULL) {
        return NONE;
    }
    strncat(temp_operand, operand, strlen(operand));
    strncat(temp_operand, ":", 1); /* concat ':' to a temoprary operand to check if it is a correct label */
    if (operand[0] == '#') { /* type 0 */
        operand++;
        if (check_data_argument(operand) == FALSE) { /* check that the rest of the operand is a correct number */
            return NONE;
        } else {
            return IMMEDIATE_ADDRESSING;
        }
    } else if (check_correct_label(temp_operand)) { /* check if its a label */
        return DIRECT_ADDRESSING;
    }
    /* check for type 2 - skip the first char that should be '&' and check if a valid label comes afterwards */
    strncat(temp_operand2, operand+1, strlen(operand)-1);
    strncat(temp_operand2, ":", 1);
    if (operand[0] == '&' && check_correct_label(temp_operand2)) {
        return RELATIVE_ADDRESSING;
    } else if (check_correct_register(operand)) { /* if the operand is a defined register (fixed value r0-r7)- it's type 3 */
        return REGISTER_ADDRESSING;
    }
    return NONE;
}

/* get a long number from a string that represents a number in the zero addressing method */
long get_number_from_operand_adressing_zero(char *operand)
{
    char num_in_string[MAX_LABEL_SIZE] = "";
    strncat(num_in_string, operand+1, strlen(operand)-1); /* start from the 2nd char (without '#') */
    return atol(num_in_string); /* change string to long int */
}