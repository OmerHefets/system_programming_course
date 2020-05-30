/**
 * This is the main module that runs the code - the main function checks for the number of arguments
 * (command line arguments) and sends to input and output files accordingly
 */

#include "numbers.h"

/* check the number of arguments and perform the conversion */
int main(int argc, char *argv[])
{
    FILE *ifp;
    FILE *ofp;
    char *prog_name = argv[PROGRAM_ARG];
    
    /* if there are no arguments, use stdin, stdout */
    if (argc == NO_ARGUMENTS) {
        convert_number_to_string(stdin, stdout);
    }
    /* if only one argument and this argument can be opened, use it as an input file and send the output to stdout */
    else if (argc == INPUT_ARGUMENT) {
        if ((ifp = fopen(argv[INPUT_ARG], "r")) == NULL){
            fprintf(stderr, "%s: can't open %s for reading\n", prog_name, argv[INPUT_ARG]);
        } else {
            convert_number_to_string(ifp, stdout);
            fclose(ifp);
        }
    /* if there are two arguments, send the output to the second argument */
    } else if (argc == INPUT_OUTPUT_ARGUMENTS) {
        /* check that the arguments can be opened*/
        if ((ifp = fopen(argv[INPUT_ARG], "r")) == NULL){
            fprintf(stderr, "%s: can't open %s for reading\n", prog_name, argv[INPUT_ARG]);
            exit(1);
        } else if ((ofp = fopen(argv[OUTPUT_ARG], "w")) == NULL) {
            fprintf(stderr, "%s: can't open %s for writing\n", prog_name, argv[OUTPUT_ARG]);
        } else {
            convert_number_to_string(ifp, ofp);
            fclose(ifp);
            fclose(ofp);
        }
    /* if more than 2 arguments exist, the input is invalid */
    } else if (argc > INPUT_OUTPUT_ARGUMENTS) {
        fprintf(stderr, "%s: too many arguments in command line (maximum of additional 2 arguments for io\n", prog_name);
        exit(2);
    }
    return 0;
}