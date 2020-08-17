/**
 * This module has all functions that validates the input in all parsing required in the program:
 * parsing data lines, label names, various arguments to all commands (.data, .string, etc.)
 */

#include "assembler.h"

/* check if a token exists as a valid command from the defined data operations and opcodes */
int check_command_exists(char *str)
{
    int i, exists=FALSE;
    if (str == NULL) {
        return exists; /* no empty command exists */
    }
    for (i=0 ; i < NUM_OF_OPCODES ; i++) { /* search defined opcodes */
        if (!strcmp(opcodes[i], str)) {
            exists = TRUE; 
        }
    }
    for (i=0 ; i < NUM_OF_DATA_OPERATIONS ; i++) { /* search defined data operations */
        if (!strcmp(data_operations[i], str)) {
            exists = TRUE;
        }
    }
    return exists;
}

/* check if a token has a name of a defined register (r0-r7) */
int check_correct_register(char *str)
{
    int i, buffer_size;
    if (str == NULL) {
        return FALSE;
    }
    buffer_size = strlen(str);
    for (i=0 ; i < NUM_OF_REGISTERS ; i++) { /* iterate all defined register names */
        if (!strncmp(str, registers[i], buffer_size)) {
            return TRUE;
        }
    }
    return FALSE;
}

/* check if a token is a correct label */
int check_correct_label(char *str)
{
    int i=0;
    int buffer_size;
    char *temp_str = str;
    if (str == NULL) {
        return FALSE;
    }
    buffer_size = strlen(str);
    if (buffer_size >= MAX_LABEL_SIZE || !isalpha(str[0]) || str[buffer_size-1] != ':') {
        return FALSE; /* first char must be from the ABC alphabet, last char must be a ':' */
    }

    while (*temp_str != '\0' && *temp_str != '\n' && buffer_size-1 > i) {
        if (!isalnum(*temp_str)) { /* make sure all other chars in the token are alphanumerics */
            return FALSE;
        }
        temp_str++;
        i++;
    }

    /* check that the label name is not a predefined name of an opcode, register or data operation */
    for (i=0 ; i < NUM_OF_OPCODES ; i++) {
        if (!strncmp(str, opcodes[i], buffer_size-1)) {
            return FALSE;
        }
        if (i < NUM_OF_REGISTERS) {
            if (!strncmp(str, registers[i], buffer_size-1)) {
            return FALSE;
            }
            if (i < NUM_OF_DATA_OPERATIONS) {
                if (!strncmp(str, data_operations[i], buffer_size-1)) {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

/* check that all data arguments after .data operation are valid */
int check_data_arguments(char line[])
{
    char *delim = " \t,\n";
    char *token;
    if (check_number_of_commas(line, UNLIMITED)) { /* unlimited number of commas allowed, check seperation of arguments by commas */
        token = strtok(line, delim); 
        while (token != NULL) {
            if (!check_data_argument(token)) { /* get all tokens from the line, and parse the arguments one by one */
                return FALSE;
            }
            token = strtok(NULL, delim);
        }
    } else {
        return FALSE;
    }
    return TRUE; /* return true only if all arguments are valid */
}

/* check a single data argument - if he's written correctly */
int check_data_argument(char *arg)
{
    if (arg == NULL) {
        return FALSE;
    }
    if (arg[0] == '-' || arg[0] == '+') { 
        if (strlen(arg) == 1) { /* if first char is '+' or '-' make sure that it's not the only char */
            return FALSE;
        } 
    } else if (!isdigit(*arg)) { /* first char must be '+', '-', or a digit */
            return FALSE;
    }
    arg++;
    while (*arg != '\0' && *arg != '\n') {
        if (!isdigit(*arg)) { /* all other char must be digits, only integers without a fractional component */
            return FALSE;
        }
        arg++;
    }
    return TRUE;
}

/* check that a string argument is valid */
int check_string_argument(char *line)
{
    char *first_quotation, *last_quotation;
    first_quotation = strchr(line, '\"');
    last_quotation = strrchr(line, '\"');
    if (first_quotation == NULL || first_quotation == last_quotation ) {
        return FALSE; /* must have two quotation marks. string can be an empty string! */
    } else {
        last_quotation++; /* if a valid string exists, make sure that no other chars exists after that string */
        while (*last_quotation != '\0' && *last_quotation != '\n') {
            if (*last_quotation != ' ' && *last_quotation != '\t') {
                return FALSE;
            }
            last_quotation++;
        }
    }
    return TRUE;
}

/* check that an extern agrument is a valid argument */
int check_extern_argument(char *line)
{
    char *delim = " \t\n";
    char *token, temp_token[MAX_LABEL_SIZE] = "";
    token = strtok(line, delim);
    if (token == NULL) {
        return FALSE;
    }
    strncat(temp_token, token, strlen(token)); 
    strncat(temp_token, ":", 1);
    if(check_correct_label(temp_token)) { /* to be a valid argument it has to be a valid label */
        token = strtok(NULL, delim);
        if (token == NULL) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
}

/* check that requested amount of commas exist in the line, and that valid amount of arguments exits between each set of commas */
int check_number_of_commas(char *s, int requested_amount_commas)
{
    int args=0, commas=0, flag=FALSE; /* use flag to mark if its a real token and not a whitespace or comma (TRUE) or whitespace/comma (FALSE) */
    while (*s != '\0' && *s != '\n') {
        if ((flag == TRUE) && (*s == ' ' || *s == '\t')) {
            flag = FALSE; 
        } else if ((flag == FALSE) && (*s != ' ' && *s != '\t' && *s != ',')) {
            flag = TRUE;
            args++;
            if (args - commas != 1) { /* when an arg is found, it must be larger than 1 from number of commas */
                return FALSE;
            }
        } else if (*s == ',') {
            flag = FALSE;
            commas++;
            if (args - commas != 0) {
                return FALSE; /* when a comma is found, it must be as the number of args to that point */
            }
        }
        s++;
    }
    if (args - commas != 1) { /* number of arguments must be larger in 1 than number of commas */
        return FALSE;
    } else if (requested_amount_commas != UNLIMITED && commas != requested_amount_commas){
        return FALSE; /* only if the requested is unlimited the amount of commas can differ from the requested (which is unlimited == -1) */
    } else {
        return TRUE;
    }
}

/* check if instruction arguments are valid to a generic instruction */
int check_instruction_arguments(char *line, char *command)
{
    char *delim = " \t\n";
    char *token;
    /* if the instruction is "stop" or "rts", there must be no arguments afterwards */
    if (!strcmp(command, "stop") || !strcmp(command, "rts")) {
        token = strtok(line, delim);
        if (token == NULL) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    /* check that number of arguments after the specific command is valid  */
    if (check_number_of_commas(line, opcodes_number_of_operands[get_command_index(command)] - 1)) {
        if (opcodes_number_of_operands[get_command_index(command)] == 1) { /* if number of arguments is 1 */
            return check_one_operand_in_instruction(line, command); /* check that this operand is valid */
        } else {
            return check_two_operands_in_instruction(line, command); /* check that both operands are valid */
        }
    } else {
        return FALSE;
    }
}

/* check that a single operand in line is valid to that command */
int check_one_operand_in_instruction(char *line, char *command)
{
    char *delim = " ,\t";
    char *token;
    token = strtok(line, delim);
    if (get_operand_type(token) != NONE) { /* check that this operand is of a valid type (0-3) */
        /* if the type is valid, check that this type is valid to this specific command */
        if (is_legal_operand_type(opcodes_second_operand[get_command_index(command)], get_operand_type(token))) {
            return TRUE;
        }
    }
    return FALSE;
}

/* check that two operands in a line are valid to that command */
int check_two_operands_in_instruction(char *line, char *command)
{
    char *delim = " ,\t";
    char *token;
    token = strtok(line, delim);  
    /* same as in the single operand check - nested if's for double check of two operands.
    if the first one is correct, check the second one with strtok */  
    if (get_operand_type(token) != NONE) {
        if (is_legal_operand_type(opcodes_first_operand[get_command_index(command)], get_operand_type(token))) {
            token = strtok(NULL, delim); /* get the second token and check him in the same way */
            if (get_operand_type(token) != NONE) {
                if (is_legal_operand_type(opcodes_second_operand[get_command_index(command)], get_operand_type(token))) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

/* get the optional operands from predefined possible operands for this operand, and check if the type matches the possible operands 
for example, if in "add" opcode the operand is of type 0,1 or 3. */
int is_legal_operand_type(int *optional_operands, int operand_type)
{
    int i;
    for (i=0 ; i < MAX_POSSIBLE_OPCODES ; i++) {
        if (optional_operands[i] == operand_type) {
            return TRUE;
        }
    }
    return FALSE;
}

/* is filename length is of the defined length (predefined in the header file) */
int is_legal_filename_length(char *file_name)
{
    if(strlen(file_name) > MAX_FILE_NAME) {
        return FALSE;
    }
    return TRUE;
}