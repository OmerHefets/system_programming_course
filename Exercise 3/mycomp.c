/**
 * This is the main module of the program. Inside the main reading and parsing the commands.
 * another function is declared in the main module as well: reset all complex numbers in the program (A-F).
 */

#include <stdio.h>
#include <string.h>
#include "complex.h"

int main()
{

    /* defining chars for reading the command line and command name - set to maxline. */
    char command_line[MAX_COMMAND_LINE];
    char command_name[MAX_COMMAND_LINE];
    /* pointer to the arguments, after reading the command from command line */
    char *line_without_command;
    /* defining the complex numbers in the exercise, and a pointer arr to them for easier access with other
    modules and functions */
    complex A, B, C, D, E, F;
    complex *complex_pointers[COMPLEX_NUMBER];
    complex_pointers[A_POS] = &A;
    complex_pointers[B_POS] = &B;
    complex_pointers[C_POS] = &C;
    complex_pointers[D_POS] = &D;
    complex_pointers[E_POS] = &E;
    complex_pointers[F_POS] = &F;
    /* reset the complex values to zero */
    reset_complexes(complex_pointers, COMPLEX_NUMBER);
    /* print the explanations + read command lines until getting a null. another exit condition with "stop" inside */
    user_interface();
    printf("Insert your command:\n");
    while(fgets(command_line, MAX_COMMAND_LINE, stdin) != NULL) {
        printf("The command was: ");
        fputs(command_line, stdout);
        line_without_command = read_argument(command_line, command_name, FALSE);
        /* if the validation is FALSE it means that the command was stop - so return 0 without errors */
        if (validate_command_and_execute(line_without_command, complex_pointers, command_name) == FALSE) {
            printf("\n");
            return 0;
        }
        printf("Insert your command:\n");
    }
    /* if the loop stopped because of EOF (null) and not because of the stop command - print an error and exit */
    if (fgets(command_line, MAX_COMMAND_LINE, stdin) == NULL) {
        printf("Error: there is no ending condition to the script. stopping because of EOF\n");
    }
    return 0;
}

/* resets all complex numbers inside an array of pointers to complex numbers */
void reset_complexes(complex **pointers_array, int array_size)
{
    int i;
    for (i = 0; i < array_size ; i++) {
        pointers_array[i]->real = 0;
        pointers_array[i]->img = 0;
    }
}