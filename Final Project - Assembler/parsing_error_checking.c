#include "assembler.h"

int check_command_exists(char *str)
{
    int i, exists=FALSE;
    if (str == NULL) {
        return exists;
    }
    for (i=0 ; i < 16 ; i++) {
        if (!strcmp(opcodes[i], str)) {
            exists = TRUE;
        }
    }
    for (i=0 ; i < 4 ; i++) {
        if (!strcmp(data_operations[i], str)) {
            exists = TRUE;
        }
    }
    return exists;
}

int check_correct_register(char *str)
{
    int i, buffer_size;
    if (str == NULL) {
        return FALSE;
    }
    buffer_size = strlen(str);
    for (i=0 ; i < 8 ; i++) {
        if (!strncmp(str, registers[i], buffer_size)) {
            return TRUE;
        }
    }
    return FALSE;
}

int check_correct_label(char *str)
{
    int i=0;
    int buffer_size;
    char *temp_str = str;
    if (str == NULL) {
        return FALSE;
    }
    buffer_size = strlen(str);
    if (buffer_size > 32 || !isalpha(str[0]) || str[buffer_size-1] != ':') {
        return FALSE;
    }

    while (*temp_str != '\0' && *temp_str != '\n' && buffer_size-1 > i) {
        if (!isalnum(*temp_str)) {
            return FALSE;
        }
        temp_str++;
        i++;
    }

    for (i=0 ; i < 16 ; i++) {
        if (!strncmp(str, opcodes[i], buffer_size-1)) {
            return FALSE;
        }
        if (i < 8) {
            if (!strncmp(str, registers[i], buffer_size-1)) {
            return FALSE;
            }
            if (i < 4) {
                if (!strncmp(str, data_operations[i], buffer_size-1)) {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

int check_data_arguments(char line[])
{
    char *delim = " \t,\n";
    char *token;
    if (check_number_of_commas(line, UNLIMITED)) {
        token = strtok(line, delim);
        while (token != NULL) {
            if (!check_data_argument(token)) {
                return FALSE;
            }
            token = strtok(NULL, delim);
        }
    } else {
        return FALSE;
    }
    return TRUE;
}

int check_data_argument(char *arg)
{
    if (arg == NULL) {
        return FALSE;
    }
    if (arg[0] == '-' || arg[0] == '+') {
        if (strlen(arg) == 1) {
            return FALSE;
        } 
    } else if (!isdigit(*arg)) {
            return FALSE;
    }
    arg++;
    while (*arg != '\0' && *arg != '\n') {
        if (!isdigit(*arg)) {
            return FALSE;
        }
        arg++;
    }
    return TRUE;
}

int check_string_argument(char *line)
{
    char *first_quotation, *last_quotation;
    first_quotation = strchr(line, '\"');
    last_quotation = strrchr(line, '\"');
    if (first_quotation == NULL || first_quotation == last_quotation || (last_quotation - first_quotation < 2)) {
        return FALSE;
    }
    return TRUE;
}

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
    if(check_correct_label(temp_token)) {
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

int check_number_of_commas(char *s, int requested_amount_commas)
{
    int args=0, commas=0, flag=FALSE;
    while (*s != '\0' && *s != '\n') {
        if ((flag == TRUE) && (*s == ' ' || *s == '\t')) {
            flag = FALSE;
        } else if ((flag == FALSE) && (*s != ' ' && *s != '\t' && *s != ',')) {
            flag = TRUE;
            args++;
            if (args - commas != 1) {
                return FALSE;
            }
        } else if (*s == ',') {
            flag = FALSE;
            commas++;
            if (args - commas != 0) {
                return FALSE;
            }
        }
        s++;
    }
    if (args - commas != 1) {
        return FALSE;
    } else if (requested_amount_commas != UNLIMITED && commas != requested_amount_commas){
        return FALSE;
    } else {
        return TRUE;
    }
}

int check_instruction_arguments(char *line, char *command)
{
    char *delim = " \t\n";
    char *token;
    if (!strcmp(command, "stop") || !strcmp(command, "rts")) {
        token = strtok(line, delim);
        if (token == NULL) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    if (check_number_of_commas(line, opcodes_number_of_operands[get_command_index(command)] - 1)) {
        if (opcodes_number_of_operands[get_command_index(command)] == 1) {
            return check_one_operand_in_instruction(line, command);
        } else {
            return check_two_operands_in_instruction(line, command);
        }
    } else {
        return FALSE;
    }
}

int check_one_operand_in_instruction(char *line, char *command)
{
    char *delim = " ,\t";
    char *token;
    token = strtok(line, delim);
    if (get_operand_type(token) != NONE) {
        if (is_legal_operand_type(opcodes_second_operand[get_command_index(command)], get_operand_type(token))) {
            return TRUE;
        }
    }
    return FALSE;
}

int check_two_operands_in_instruction(char *line, char *command)
{
    char *delim = " ,\t";
    char *token;
    token = strtok(line, delim);    
    if (get_operand_type(token) != NONE) {
        if (is_legal_operand_type(opcodes_first_operand[get_command_index(command)], get_operand_type(token))) {
            token = strtok(NULL, delim);
            if (get_operand_type(token) != NONE) {
                if (is_legal_operand_type(opcodes_second_operand[get_command_index(command)], get_operand_type(token))) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}