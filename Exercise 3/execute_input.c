/**
 * This module executes all the requested commands, according to the specific arguments that each command requires.
 */

#include <string.h>
#include <stdlib.h>
#include "complex.h"

/* execture read command */
void execute_read_comp(char *s, complex **pointers_array)
{
    int complex_index;
    char arg1[COMPLEX_LENGTH];
    char arg2[MAX_COMMAND_LINE];
    char arg3[MAX_COMMAND_LINE];
    char *p = s;
    /* read arguments */
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    p = read_argument(p, arg3, TRUE);
    /* the correct index for the complex number the subtraction of the argument char from the A ascii value
    for example, if the argument is C then C's char value is 67' A is 65 and the correct index is 2. */
    complex_index = arg1[0] - A_ASCII_VALUE;
    read_complex(pointers_array[complex_index], atof(arg2), atof(arg3));
}

/* execute print/abs command */
void execute_print_abs_comp(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE])
{
    int complex_index;
    char arg1[COMPLEX_LENGTH];
    char *p = s;
    /* read argument */
    p = read_argument(p, arg1, TRUE);
    /* the correct index for the complex number the subtraction of the argument char from the A ascii value */
    complex_index = arg1[0] - A_ASCII_VALUE;
    if (strcmp(command_name, "print_comp") == 0) {
        print_complex(pointers_array[complex_index]);
    } else if (strcmp(command_name, "abs_comp") == 0) {
        abs_of_complex(pointers_array[complex_index]);
    }

}

/* execute add/sub/multiply command */
void execute_add_sub_mult_comp(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE])
{
    int complex_index1, complex_index2;
    char arg1[COMPLEX_LENGTH];
    char arg2[COMPLEX_LENGTH];
    char *p = s;
    /* read arguments */
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    /* the correct index for the complex numbers the subtraction of the argument char from the A ascii value */
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

/* execute muliply real/img command */
void execute_mult_real_and_img(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE])
{
    int complex_index;
    char arg1[COMPLEX_LENGTH];
    char arg2[MAX_COMMAND_LINE];
    char *p = s;
    /* read arguments */
    p = read_argument(p, arg1, TRUE);
    p = read_argument(p, arg2, TRUE);
    /* the correct index for the complex number the subtraction of the argument char from the A ascii value */
    complex_index = arg1[0] - A_ASCII_VALUE;
    if (strcmp(command_name, "mult_comp_real") == 0) {
        multiply_complex_real(pointers_array[complex_index], atof(arg2));
    } else if (strcmp(command_name, "mult_comp_img") == 0) {
        multiply_complex_img(pointers_array[complex_index], atof(arg2));
    }
}