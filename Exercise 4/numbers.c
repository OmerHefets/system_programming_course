#include "numbers.h"

int main(int argc, char *argv[])
{
    FILE *ifp;
    FILE *ofp;
    char *prog_name = argv[PROGRAM_ARG];
    
    if (argc == NO_ARGUMENTS) {
        convert_number_to_string(stdin, stdout);
    }
    else if (argc == INPUT_ARGUMENT) {
        if ((ifp = fopen(argv[INPUT_ARG], "r")) == NULL){
            fprintf(stderr, "%s: can't open %s for reading\n", prog_name, argv[INPUT_ARG]);
        } else {
            convert_number_to_string(ifp, stdout);
            fclose(ifp);
        }
    } else if (argc == INPUT_OUTPUT_ARGUMENTS) {
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
    } else if (argc > INPUT_OUTPUT_ARGUMENTS) {
        fprintf(stderr, "%s: too many arguments in command line (maximum of additional 2 arguments for io\n", prog_name);
        exit(2);
    }
    return 0;
}