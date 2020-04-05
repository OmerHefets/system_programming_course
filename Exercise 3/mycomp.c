#include <stdio.h>
#include <string.h>
#include "complex.h"

int main()
{
    char command_line[MAX_COMMAND_LINE];
    char command_name[MAX_COMMAND_LINE];
    char *no_white, *after_func;
    while(fgets(command_line, MAX_COMMAND_LINE, stdin) != NULL) {
            if (strcmp(command_line, "stop") == 0) {
                printf("\nstop!!!!\n.");
                return 0;
            }
            
            fputs(command_line, stdout);
            no_white = read_white_chars(command_line);
            read_function(no_white, command_name);
            after_func = read_argument(no_white);
            printf("no white: %s\n", no_white);
            printf("function: %s\n", command_name);
            printf("after function: %s\n", after_func);
            printf("num of args: %d\n", check_num_of_args(after_func));
    }
    if (fgets(command_line, MAX_COMMAND_LINE, stdin) == NULL) {
        printf("\nerror. no stopping.\n");
    }
    return 0;
}