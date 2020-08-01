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

int check_correct_label(char *str)
{
    int i;
    int buffer_size;
    if (str == NULL) {
        return FALSE;
    }
    buffer_size = strlen(str);
    if (buffer_size > 32 || !isalpha(str[0]) || str[buffer_size-1] != ':') {
        return FALSE;
    }

    for (i=0 ; i < 16 ; i++) {
        if (!strncmp(str, opcodes[i], buffer_size-1)) {
            return FALSE;
        }
    }
    for (i=0 ; i < 8 ; i++) {
        if (!strncmp(str, registers[i], buffer_size-1)) {
            return FALSE;
        }
    }
    for (i=0 ; i < 4 ; i++) {
        if (!strncmp(str, data_operations[i], buffer_size-1)) {
            return FALSE;
        }
    }
    return TRUE;
}

int check_data_arguments(char line[])
{
    char *delim = " \t,";
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

void check_string_arguments();

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