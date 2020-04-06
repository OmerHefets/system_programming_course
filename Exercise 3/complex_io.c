#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
    if (count == 0 && comma_count == 0) {
        return count;
    }
    else if (count - comma_count != 1) {
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


void print_complex(complex *number)
{
    if (number->img >= 0) {
        printf("%.2f + (%.2f)i\n", number->real, number->img);
    } else {
        printf("%.2f - (%.2f)i\n", number->real, fabs(number->img));
    }
}