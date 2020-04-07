/**
 * This module validates all the requested commands in the program: validating complex and correct real numbers,
 * validating amount of arguments and commas in a command line, and validating the correct amount and type of arguments.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "complex.h"

/* a function that returns the number of arguments in a string, and ERROR if the comma positioning isn't correct */
int check_num_of_args_and_commas(char *s)
{
    int count = 0, comma_count = 0;
    int i = 0;
    while (i < MAX_COMMAND_LINE && *s != '\0' && *s != '\n') {
        /* read white chars and count the commas until an argument */
        while ((*s == '\t' || *s == ' ' || *s == ',') && (i < MAX_COMMAND_LINE && *s != '\0' && *s != '\n')) {
            if (*s == ',') {
                comma_count++;
            }
            i++;
            s++;
        }
        /* after getting to the beginning of an argument, if the number of commas isn't one less the number of arguments,
        then there is not the right amount of commas and commas in the right place (between arguments) */
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
    /* return count = 0 if there are no arguments or commas at all */
    if (count == 0 && comma_count == 0) {
        return count;
    }
    /* edge case if commas appear at the end of the last argument, then its invalid an return an ERROR (-1) */
    else if (count - comma_count != 1) {
        return ERROR;
    }
    return count;
}

/* check if the number of arguments requested in a string is the same as the value.
checks for error values if the string is not correct, and prints the error to the screen as well. */
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

/* validate that a string is a valid double number (check for decimal seperator and minus sign as well 
return VALID if double and INVALID if not a double. */
int validate_double(char *s)
{
    int i = 0, arg_length; 
    int decimal_seperator = FALSE;
    arg_length = strlen(s);
    while (i < arg_length) {
        if (!isdigit(s[i])) {
            /* if it starts with a minus sign, then its still a valid number */
            if (i == 0 && s[i] == '-') {
                i++;
                continue;
            }
            /* only one decimal seperator is valid. if it's the first one, change the value that next ones will be incorrect */
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

/* validate that a string is a complex number. return VALID if true, INVALID if not */
int validate_complex(char *s)
{
    int arg_length; 
    arg_length = strlen(s);

    /* any string longer than 1 is incorrect because complex number size is 1 */
    if (arg_length > 1) {
        printf("Invalid parameter - not a defined complex number.\n");
        return INVALID;
    } else if (arg_length == 1) {
        /* valid string complex equals only to one of the existing complex numbers in the exercise */
        if (s[0] != 'A' && s[0] != 'B' && s[0] != 'C' && s[0] != 'D' && s[0] != 'E' && s[0] != 'F') {
            printf("Invalid parameter - not a defined complex number.\n");
            return INVALID;
        }
    }
    return VALID;
}

/* validating that the arguments in the read command are valid - complex and two numbers */
int validate_read_comp(char *s)
{
    char arg1[MAX_COMMAND_LINE];
    char arg2[MAX_COMMAND_LINE];
    char arg3[MAX_COMMAND_LINE];
    char *p = s;
    if (!validate_number_of_args_and_commas(READ_COMP_NUM_ARGS, s)) {
        return INVALID;
    }
    /* reading the arguments */
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    p = read_argument(p, arg3, TRUE);
    /* checking that the arguments are correct */
    if (validate_complex(arg1) && validate_double(arg2) && validate_double(arg3)) {
        return VALID;
    }
    return INVALID;
}

/* validating that the argument in the print/abs command is valid - complex */
int validate_print_abs_comp(char *s)
{
    char arg1[MAX_COMMAND_LINE];
    char *p = s;
    if (!validate_number_of_args_and_commas(PRINT_COMP_NUM_ARGS, s)) {
        return INVALID;
    }
    /* reading the argument */
    p = read_argument(p, arg1, TRUE);
    /* checking that the arguments are correct */
    if (validate_complex(arg1)) {
        return VALID;
    }
    return INVALID;
}

/* validating that the arguments in the add/sub/multiply command are valid - two complex numbers */
int validate_add_sub_mult_comp(char *s)
{
    char arg1[MAX_COMMAND_LINE];
    char arg2[MAX_COMMAND_LINE];
    char *p = s;
    if (!validate_number_of_args_and_commas(ADD_COMP_NUM_ARGS, s)) {
        return INVALID;
    }
    /* reading the arguments */
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    /* checking that the arguments are correct */
    if (validate_complex(arg1) && validate_complex(arg2)) {
        return VALID;
    }
    return INVALID;
}

/* validating that the arguments in the multiply real/img command are valid - complex and a number */
int validate_mult_real_and_img(char *s)
{
    char arg1[MAX_COMMAND_LINE];
    char arg2[MAX_COMMAND_LINE];
    char *p = s;
    if (!validate_number_of_args_and_commas(MULT_COMP_REAL_NUM_ARGS, s)) {
        return INVALID;
    }
    /* reading the arguments */
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    /* checking that the arguments are correct */
    if (validate_complex(arg1) && validate_double(arg2)) {
        return VALID;
    }
    return INVALID;
}

/* validating the stop command */
int validate_stop(char *s)
{
    /* check that there are only white chars after the stop */
    s = pass_white_chars(s);
    if (*s == '\0' || *s == EOF || s == NULL || *s == '\n') {
        return VALID;
    }
    printf("Extraneous text after stop command.\n");
    return INVALID;
}