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
            printf("validate first arg: %d\n", validate_complex(arg1, TRUE));
            printf("validate second arg: %d\n", validate_double(arg2, TRUE));
            printf("validate third arg: %d\n", validate_complex(arg3, FALSE));
            printf("number of  arguments: %d", check_num_of_args_and_commas(after_func));
    }
    if (fgets(command_line, MAX_COMMAND_LINE, stdin) == NULL) {
        printf("\nerror. no stopping.\n");
    }
    return 0;
}