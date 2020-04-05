#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
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


int validate_command_and_execute(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE])
{
    if (strcmp(command_name, "read_comp") == 0) {
        if (validate_read_comp(s)) {
            execute_read_comp(s, pointers_array);
        }
    } else if (strcmp(command_name, "print_comp") == 0) {
        if (validate_print_abs_comp(s)) {
            execute_print_abs_comp(s, pointers_array, command_name);
        }
    } else if (strcmp(command_name, "add_comp") == 0) {
        if (validate_add_sub_mult_comp(s)) {
            execute_add_sub_mult_comp(s, pointers_array, command_name);
        }
    } else if (strcmp(command_name, "sub_comp") == 0) {
        if (validate_add_sub_mult_comp(s)) {
            execute_add_sub_mult_comp(s, pointers_array, command_name);
        } 
    } else if (strcmp(command_name, "mult_comp_real") == 0) {
        if (validate_mult_real_and_img(s)) {
            execute_mult_real_and_img(s, pointers_array, command_name);
        }
    } else if (strcmp(command_name, "mult_comp_img") == 0) {
        if (validate_mult_real_and_img(s)) {
            execute_mult_real_and_img(s, pointers_array, command_name);
        } 
    } else if (strcmp(command_name, "mult_comp_comp") == 0) {
        if (validate_add_sub_mult_comp(s)) {
            execute_add_sub_mult_comp(s, pointers_array, command_name);
        }
    } else if (strcmp(command_name, "abs_comp") == 0) {
        if (validate_print_abs_comp(s)) {
            execute_print_abs_comp(s, pointers_array, command_name);
        } 
    } else if (strcmp(command_name, "stop") == 0) {
        if (validate_stop(s)) {
            return FALSE;
        }
    } else {
        printf("invalid function name.\n");
        return TRUE;
    }
    return TRUE;
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
                printf("Invalid parameter - not a decimal number.\n");
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
            printf("Invalid parameter - not a defined complex number.\n");
            return INVALID;
        }
    }
    return VALID;
}

int validate_read_comp(char *s)
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

int validate_print_abs_comp(char *s)
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
    if (*s != '\n' || *s != '\0' || *s != EOF || s != NULL) {
        printf("Extraneous text after stop command.\n");
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

void execute_print_abs_comp(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE])
{
    int complex_index;
    char arg1[COMPLEX_LENGTH];
    char *p = s;
    p = read_argument(p, arg1, TRUE);
    complex_index = arg1[0] - A_ASCII_VALUE;
    if (strcmp(command_name, "print_comp") == 0) {
        print_complex(pointers_array[complex_index]);
    } else if (strcmp(command_name, "abs_comp") == 0) {
        abs_of_complex(pointers_array[complex_index]);
    }

}

void execute_add_sub_mult_comp(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE])
{
    int complex_index1, complex_index2;
    char arg1[COMPLEX_LENGTH];
    char arg2[COMPLEX_LENGTH];
    char *p = s;
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    complex_index1 = arg1[0] - A_ASCII_VALUE;
    complex_index2 = arg2[0] - A_ASCII_VALUE;
    if (strcmp(command_name, "add_comp") == 0) {
        add_complex_numbers(pointers_array[complex_index1], pointers_array[complex_index2]);
    } else if (strcmp(command_name, "sub_comp") == 0) {
        sub_complex_numbers(pointers_array[complex_index1], pointers_array[complex_index2]);
    } else if (strcmp(command_name, "mult_comp_comp") == 0) {
        multiply_complexes(pointers_array[complex_index1], pointers_array[complex_index2]);
    }
}

void execute_mult_real_and_img(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE])
{
    int complex_index;
    char arg1[COMPLEX_LENGTH];
    char arg2[MAX_COMMAND_LINE];
    char *p = s;
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    complex_index = arg1[0] - A_ASCII_VALUE;
    if (strcmp(command_name, "mult_comp_real") == 0) {
        multiply_complex_real(pointers_array[complex_index], atof(arg2));
    } else if (strcmp(command_name, "mult_comp_img") == 0) {
        multiply_complex_img(pointers_array[complex_index], atof(arg2));
    }
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

void print_complex(complex *number)
{
    if (number->img >= 0) {
        printf("%.2f + (%.2f)i\n", number->real, number->img);
    } else {
        printf("%.2f - (%.2f)i\n", number->real, fabs(number->img));
    }
}