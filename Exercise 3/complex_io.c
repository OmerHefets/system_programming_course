/**
 * This module is responsible for the main input-output functions of the program:
 * input - parsing the strings (the commands) and processing the commands (validating and executing)
 * output - printing interface to the user and printing errors and defined function for printing complex numbers
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "complex.h"

/* gets a pointer to a string and returns a pointer to the first char in the string that isn't a white char (tab or space) */
char* pass_white_chars(char *s)
{
    int count = 0;
    while ((*s == '\t' || *s == ' ') && (*s != '\0' && count < MAX_COMMAND_LINE)) {
        count++;
        s++;
    }
    return s;
}

/* gets a pointer to a string and returns a pointer to the first char in the string that isn't a white char (tab or space) or comma */
char* pass_white_chars_and_commas(char *s)
{
    int count = 0;
    while ((*s == '\t' || *s == ' ' || *s == ',') && (*s != '\0' && count < MAX_COMMAND_LINE)) {
        count++;
        s++;
    }
    return s;
}

/* reading an argument (that is not a white char or comma) into an arg string that is passed to the function.
will skip commas in search for the argument if skip_commas is 1. returns a pointer to the end of the argument. */
char* read_argument(char *s, char arg[MAX_COMMAND_LINE], int skip_commas)
{
    int i = 0;
    /* will skip commas as well if skip_commas is 1 (TRUE) */
    if (skip_commas) {
        s = pass_white_chars_and_commas(s);
    }
    else {
        s = pass_white_chars(s);
    }
    /* read the argument while its valid chars for the argument */
    while ((*s != '\t' && *s != ' ' && *s != '\n' && *s != ',') && (*s != '\0' && i < MAX_COMMAND_LINE)) {
        arg[i] = *s;
        i++;
        s++;
    }
    /* if the argument was too long, make sure to put the ending char one char before
    (this command will not be valid because there is empty memory in the line for other commands / args) */
    if (i == MAX_COMMAND_LINE) {
        i--;
        arg[i] = '\0';
    } 
    else {
        arg[i] = '\0';
    }
    return s;
}

/* gets the arguments line (after command) and validates it - if the command and arguments are valid then execute the requested command.
if the command is invalid, printing an error (with the validation functions).
returns 1 (TRUE) if the command was valid or invalid - so the program will ask for another command. 
returns 0 (FALSE) only if the command was "stop" and a valid stop - then returns 0 to finish the program. */
int validate_command_and_execute(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE])
{
    /* if conditions that works the following way: if the command name is equal to a valid command, 
    validate if the command arguments are correct. if they are correct execute the command with these argument.*/
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
    /* will return FALSE (0) and finish the program if the command was a valid stop. */
    } else if (strcmp(command_name, "stop") == 0) {
        if (validate_stop(s)) {
            return FALSE;
        }
    /* for empty lines, keep reading the line*/
    } else if (strlen(command_name) == 0) {
        return TRUE;
    }
    /* if the function name is not correct, print that to the screen and return TRUE so the program will ask for another command.*/
     else {
        printf("invalid function name.\n");
        return TRUE;
    }
    return TRUE;
}

/* print a complex number in the format: real_part + (img_part)i */
void print_complex(complex *number)
{
    /* set the values again to zero to avoid situation of program printing -0 (multiplication of negative number and zero) */
    if (number->img == 0) {
        number->img = 0;
    }
    if (number->real == 0) {
        number->real = 0;
    }
    /* print with the correct format according to the values of the imaginary part */
    if (number->img >= 0) {
        printf("%.2f + (%.2f)i\n", number->real, number->img);
    }
    else {
        printf("%.2f - (%.2f)i\n", number->real, fabs(number->img));
    }
}

/* prints all the explanations to the user */
void user_interface()
{
    printf("Hello. this program executes commands on complex numbers as you define.\n");
    printf("There are six complex numbers defined in this program: A, B, C, D, E, F. It's not possible to define more.\n");
    printf("All complexes are reset to zero at the beginning. When reqested to, insert a command in the following way:\n");
    printf("\"command_name\" \"arg1\", \"arg2\", \"arg3\"\n");
    printf("make sure to have a comma between each argument, and not at the end / before the first arg. white chars are ignored everywhere.\n");
    printf("The following commands are possible: reading complex, printing complex, adding, subtracting, multiplying or abs:\n");
    printf("Reading a number: \"read_comp\" \"complex_name\", \"number_arg\", \"number_arg\"\n");
    printf("Printing a number: \"print_comp\" \"complex_name\"\n");
    printf("Adding two numbers: \"add_comp\" \"complex_name\", \"complex_name\"\n");
    printf("Subtracting two numbers: \"sub_comp\" \"complex_name\", \"complex_name\"\n");
    printf("Multiplying a complex number with a real number: \"mult_comp_real\" \"complex_name\", \"number_arg\"\n");
    printf("Multiplying a complex number with an imaginary number:\"mult_comp_img\" \"complex_name\", \"number_arg\"\n");
    printf("Multiplying two complex numbers: \"mult_comp_comp\" \"complex_name\", \"complex_name\"\n");
    printf("Calculate the abs of the complex number: \"abs_comp\" \"complex_name\"\n");
    printf("Stop the program: \"stop\"\n");
}