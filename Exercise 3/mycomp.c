#include <stdio.h>
#include <string.h>
#include "complex.h"

int main()
{
    char command_line[MAX_COMMAND_LINE];
    char command_name[MAX_COMMAND_LINE];
    char *line_without_command;
    complex A, B, C, D, E, F;
    complex *complex_pointers[COMPLEX_NUMBER];
    complex_pointers[0] = &A;
    complex_pointers[1] = &B;
    complex_pointers[2] = &C;
    complex_pointers[3] = &D;
    complex_pointers[4] = &E;
    complex_pointers[5] = &F;
    reset_complexes(complex_pointers, COMPLEX_NUMBER);
    while(fgets(command_line, MAX_COMMAND_LINE, stdin) != NULL) {
        fputs(command_line, stdout);
        line_without_command = read_argument(command_line, command_name, FALSE);
        if (validate_command_and_execute(line_without_command, complex_pointers, command_name) == FALSE) {
            return 0;
        }
    }
    if (fgets(command_line, MAX_COMMAND_LINE, stdin) == NULL) {
        printf("Error: there is no ending condition to the script. stopping because of EOF\n");
    }
    return 0;
}