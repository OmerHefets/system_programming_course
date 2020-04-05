#include <stdio.h>
#include <string.h>
#include "complex.h"

int main()
{
    char command_line[MAX_COMMAND_LINE];
    char command_name[MAX_COMMAND_LINE];
    char arg1[MAX_COMMAND_LINE];
    char arg2[MAX_COMMAND_LINE];
    char arg3[MAX_COMMAND_LINE];
    char *no_white, *after_func, *after_arg;
    complex A, B, C, D, E, F;
    complex *complex_pointers[COMPLEX_NUMBER];
    complex_pointers[0] = &A;
    complex_pointers[1] = &B;
    complex_pointers[2] = &C;
    complex_pointers[3] = &D;
    complex_pointers[4] = &E;
    complex_pointers[5] = &F;
    reset_complexes(complex_pointers, COMPLEX_NUMBER);
    printf("\nlel %.2f %.2f lel\n", A.real, A.img);
    while(fgets(command_line, MAX_COMMAND_LINE, stdin) != NULL) {
            if (strcmp(command_line, "stop") == 0) {
                printf("\nstop!!!!\n.");
                return 0;
            }
            fputs(command_line, stdout);
            no_white = pass_white_chars(command_line);
            after_func = read_argument(no_white, command_name, FALSE);
            after_arg = read_argument(after_func, arg1, FALSE);
            after_arg = read_argument(after_arg, arg2, TRUE);
            after_arg = read_argument(after_arg, arg3, TRUE);
            printf("no white: %s\n", no_white);
            printf("function: %s\n", command_name);
            printf("after function: %s\n", after_func);
            printf("first arg: %s\n", arg1);
            printf("first arg length: %lu\n", strlen(arg1));
            printf("second arg: %s\n", arg2);
            printf("second arg length: %lu\n", strlen(arg2));
            printf("third arg: %s\n", arg3);
            printf("third arg length: %lu\n", strlen(arg3));
            printf("validate first arg: %d\n", validate_complex(arg1));
            printf("validate second arg: %d\n", validate_double(arg2));
            printf("validate third arg: %d\n", validate_complex(arg3));
            printf("number of  arguments: %d\n", check_num_of_args_and_commas(after_func));
            printf("validation read comp: %d\n", validate_read_abs_comp(after_func));
            execute_read_comp(after_func, complex_pointers);
            printf("\nlel %.2f %.2f lel\n", A.real, A.img);
    }
    if (fgets(command_line, MAX_COMMAND_LINE, stdin) == NULL) {
        printf("\nerror. no stopping.\n");
    }
    return 0;
}