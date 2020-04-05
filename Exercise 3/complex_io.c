#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "complex.h"

char* pass_white_chars(char *s)
{
    int count = 0;
    while ((*s == '\t' || *s == ' ') && (*s != '\0' && count < MAX_COMMAND_LINE)) {
        count++;
        s++;
    }
    return s;
}

char* pass_white_chars_and_commas(char *s)
{
    int count = 0;
    while ((*s == '\t' || *s == ' ' || *s == ',') && (*s != '\0' && count < MAX_COMMAND_LINE)) {
        count++;
        s++;
    }
    return s;
}

char* read_argument(char *s, char arg[MAX_COMMAND_LINE], int skip_commas)
{
    int i = 0;
    if (skip_commas) {
        s = pass_white_chars_and_commas(s);
    }
    else {
        s = pass_white_chars(s);
    }
    while ((*s != '\t' && *s != ' ' && *s != '\n' && *s != ',') && (*s != '\0' && i < MAX_COMMAND_LINE)) {
        arg[i] = *s;
        i++;
        s++;
    }
    if (i == MAX_COMMAND_LINE) {
        arg[--i] = '\0';
    } 
    else {
            arg[i] = '\0';
    }
    return s;
}


int check_num_of_args_and_commas(char *s)
{
    int count = 0, comma_count = 0;
    int i = 0;
    while (i < MAX_COMMAND_LINE && *s != '\0' && *s != '\n') {
        while ((*s == '\t' || *s == ' ' || *s == ',') && (i < MAX_COMMAND_LINE && *s != '\0' && *s != '\n')) {
            if (*s == ',') {
                comma_count++;
            }
            i++;
            s++;
        }
        if (i < MAX_COMMAND_LINE && *s != '\0' && *s != '\n') {
            count++;
            if (count - comma_count != 1) {
                return ERROR;
            }
            while ((*s != '\t' && *s != ' ' && *s != ',') && (i < MAX_COMMAND_LINE && *s != '\0')) {
                i++;
                s++;
            }
        }
    }
    if (count - comma_count != 1) {
        return ERROR;
    }
    return count;
}


int validate_command_and_execute(char *s, char command_name[MAX_COMMAND_LINE])
{
    if (strcmp(command_name, "read_comp") == 0) {
        /*
        validate_read_comp();
        execute_read_comp();
        */
    } else if (strcmp(command_name, "print_comp") == 0) {
        ;
    } else if (strcmp(command_name, "add_comp") == 0) {
        ;
    } else if (strcmp(command_name, "sub_comp") == 0) {
        ;
    } else if (strcmp(command_name, "mult_comp_real") == 0) {
        ;
    } else if (strcmp(command_name, "mult_comp_img") == 0) {
        ;
    } else if (strcmp(command_name, "mult_comp_comp") == 0) {
        ;
    } else if (strcmp(command_name, "abs_comp") == 0) {
        ;
    } else if (strcmp(command_name, "stop") == 0) {
        ;
    } else {
        printf("invalid function name.\n");
        return INVALID;
    }
    return 0;
}

int validate_number_of_args_and_commas(int args_num, char *s)
{
    int num_of_args = check_num_of_args_and_commas(s);
    if (num_of_args > args_num) {
        printf("Invalid number of arguments - too many arguments.\n");
        return INVALID;
    } else if (num_of_args < args_num && num_of_args >= 0) {
       printf("Invalid number of arguments - missing arguments.\n");
       return INVALID;
    }
    else if (num_of_args == ERROR) {
        printf("Invalid amount or position of commas.\n");
    }
    return VALID;
}


int validate_double(char *s)
{
    int i = 0, arg_length; 
    int decimal_seperator = FALSE;
    arg_length = strlen(s);
    while (i < arg_length) {
        if (!isdigit(s[i])) {
            if (i == 0 && s[i] == '-') {
                i++;
                continue;
            }
            if (!decimal_seperator && s[i] == '.') {
                decimal_seperator = TRUE;
            }
            else {
                return INVALID;
            }
        }
        i++;
    }
    return VALID;
}

int validate_complex(char *s)
{
    int arg_length; 
    arg_length = strlen(s);

    if (arg_length > 1) {
        return INVALID;
    } else if (arg_length == 1) {
        if (s[0] != 'A' && s[0] != 'B' && s[0] != 'C' && s[0] != 'D' && s[0] != 'E' && s[0] != 'F') {
            return INVALID;
        }
    }
    return VALID;
}

int validate_read_abs_comp(char *s)
{
    char arg1[MAX_COMMAND_LINE];
    char arg2[MAX_COMMAND_LINE];
    char arg3[MAX_COMMAND_LINE];
    char *p = s;
    if (!validate_number_of_args_and_commas(READ_COMP_NUM_ARGS, s)) {
        return INVALID;
    }
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    p = read_argument(p, arg3, TRUE);
    if (validate_complex(arg1) && validate_double(arg2) && validate_double(arg3)) {
        return VALID;
    }
    return INVALID;
}

int validate_print_comp(char *s)
{
    char arg1[MAX_COMMAND_LINE];
    char *p = s;
    if (!validate_number_of_args_and_commas(PRINT_COMP_NUM_ARGS, s)) {
        return INVALID;
    }
    p = read_argument(p, arg1, TRUE);
    if (validate_complex(arg1)) {
        return VALID;
    }
    return INVALID;
}

int validate_add_sub_mult_comp(char *s)
{
    char arg1[MAX_COMMAND_LINE];
    char arg2[MAX_COMMAND_LINE];
    char *p = s;
    if (!validate_number_of_args_and_commas(ADD_COMP_NUM_ARGS, s)) {
        return INVALID;
    }
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    if (validate_complex(arg1) && validate_complex(arg2)) {
        return VALID;
    }
    return INVALID;
}

int validate_mult_real_and_img(char *s)
{
    char arg1[MAX_COMMAND_LINE];
    char arg2[MAX_COMMAND_LINE];
    char *p = s;
    if (!validate_number_of_args_and_commas(MULT_COMP_REAL_NUM_ARGS, s)) {
        return INVALID;
    }
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    if (validate_complex(arg1) && validate_double(arg2)) {
        return VALID;
    }
    return INVALID;
}

int validate_stop(char *s)
{
    if (!validate_number_of_args_and_commas(STOP_NUM_ARGS, s)) {
        printf("boom.");
        return INVALID;
    }
    return VALID;
}

void execute_read_comp(char *s, complex **pointers_array)
{
    int complex_index;
    char arg1[COMPLEX_LENGTH];
    char arg2[MAX_COMMAND_LINE];
    char arg3[MAX_COMMAND_LINE];
    char *p = s;
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    p = read_argument(p, arg3, TRUE);
    complex_index = arg1[0] - A_ASCII_VALUE;
    read_complex(pointers_array[complex_index], atof(arg2), atof(arg3));
}

void reset_complexes(complex **pointers_array, int array_size)
{
    int i;
    for (i = 0; i < array_size ; i++) {
        pointers_array[i]->real = 0;
        pointers_array[i]->img = 0;
    }
}

void read_complex(complex *number, double real_value, double img_value)
{
    number->real = real_value;
    number->img = img_value;
}