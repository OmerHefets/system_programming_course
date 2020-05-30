#include <stdio.h>
#include <stdlib.h>

/* constants for the modules */
#define NO_ARGUMENTS 1
#define INPUT_ARGUMENT 2
#define INPUT_OUTPUT_ARGUMENTS 3
#define PROGRAM_ARG 0
#define INPUT_ARG 1
#define OUTPUT_ARG 2
#define WORD_LENGTH 10

/* converts a number between 0-99 to the equivalent word in english */
void convert_number_to_string(FILE *ifp, FILE *ofp);