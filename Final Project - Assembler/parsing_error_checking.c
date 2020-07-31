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

void check_label_duplication();

void check_data_arguments();

void check_string_arguments();