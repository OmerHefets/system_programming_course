#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "complex.h"


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
        return INVALID;
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
        printf("Invalid parameter - not a defined complex number.\n");
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
    s = pass_white_chars(s);
    if (*s == '\0' || *s == EOF || s == NULL || *s == '\n') {
        return VALID;
    }
    printf("\nExtraneous text after stop command.\n");
    return INVALID;
}