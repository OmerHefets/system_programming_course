/**
 * This is the main module of the program. in this modules are defined all the functions for the assembler pipeline:
 * compiling multiple files, then on each file applying the first and the second pass, then free the memory of the linked lists.
 */

#include "assembler.h"

/* the main function of the program, calls the assembler with multiple files passed by the user with argv.
will return 0 (EXIT_WITH_SUCCESS) if the program succeed */
int main(int argc, char *argv[])
{
    compile_multiple_files(argc, argv);
    return EXIT_WITH_SUCCESS; 
}

/* gets all filed passed by the user, adds the ".as" suffix and compiles them one by one */
void compile_multiple_files(int argc, char *argv[])
{
    /* get two file pointers - one for each pass of the file */
    FILE *ifp_first_pass, *ifp_second_pass;
    char *prog_name = *argv;
    char file_name[MAX_FILE_NAME_WITH_SUFFIX];
    if (argc == ONLY_COMMAND_NO_FILES) { /* if we get no arguments, print that to the user */
        fprintf(stdout, "The assembler didn't get any files.\n");
    }
    while (--argc > NO_ARGUMENTS) {
        /* add suffix returns FALSE if filename is longer that the MAX defined (30 char without suffix).
        if the length is correct, it will add the ".as" suffix and procceed */
        if(!add_suffix_to_file(*++argv, file_name, FILENAME_SUFFIX)) { 
            fprintf(stdout, "%s: can't open %s because file name is too long", prog_name, *argv);
        }
        /* check opening for the file for both pointers */
        else if (((ifp_first_pass = fopen(file_name, "r")) == NULL) || ((ifp_second_pass = fopen(file_name, "r")) == NULL)) {
            fprintf(stdout, "%s: can't open %s for reading\n", prog_name, *argv);
        } else {
            compile_file(ifp_first_pass, ifp_second_pass, *argv);
            /* closing the file */
            fclose(ifp_first_pass);
            fclose(ifp_second_pass);
        }
        memset(file_name, UNDEFINED, strlen(file_name)); /* set the filename to NULL again, for the next filename */
    }
}

/* compile one file by the algorithm provided in mmn14 - two passes with error checking in each pass.
(will not proceed to the second pass if the first one fails with any error) then creates the files and free the memory */
void compile_file(FILE *ifp_first_pass, FILE *ifp_second_pass, char *file_name)
{
    /* defining pointer for the requested linked lists */
    SymbolPtr head_symbol = NULL;
    ExternPtr head_extern = NULL;
    InstructionPtr head_instruction = NULL;
    DataPtr head_data = NULL;
    /* define pointers the location in memory for data and instructions as initialized. set errors to false */
    int *dc, *ic, *errors_in_file, dcf = DATA_MEMORY_START, icf = INSTRUCTION_MEMORY_START, error = FALSE;
    dc = &dcf, ic = &icf, errors_in_file = &error;

    /* apply first pass */
    first_pass(ifp_first_pass, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, errors_in_file, file_name);

    /* only if no errors exist, apply the second pass */
    if (*errors_in_file == FALSE) {
        *ic = INSTRUCTION_MEMORY_START;
        second_pass(ifp_second_pass, &head_symbol, &head_extern, &head_instruction, &head_data, ic, errors_in_file, file_name);
    }
    /* if yet no errors exist, print requested files */
    if (*errors_in_file == FALSE) {
        create_files(head_symbol, head_extern, head_instruction, head_data, *ic, *dc, file_name);
    }
    /* free the dynamic allocated memory */
    free_all_data_structures(&head_symbol, &head_extern, &head_instruction, &head_data);
}

/* apply the first pass algorithm on a file */
void first_pass(FILE *ifp, SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data, int *dc, int *ic, int *errors_in_file, char *file_name)
{
    char command_line[MAX_LINE];
    int corrent_line = FIRST_LINE;
    /* parse lines until we reach the end of the file */
    while(fgets(command_line, MAX_LINE, ifp) != NULL) {
        parse_line_first_pass(command_line, errors_in_file, head_symbol, head_extern, head_instruction,
        head_data, dc, ic, corrent_line, file_name);
        corrent_line++; /* count line number for error checking */
    }
    /* update the data memory index according the number of instructions, as defined in the first pass */
    update_data_memory_in_symbol_table(*head_symbol, *ic);
    update_data_memory_in_data_table(*head_data, *ic);
}

/* apply the second pass algorithm on a file */
void second_pass(FILE *ifp, SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data, int *ic, int *errors_in_file, char *file_name)
{
    char command_line[MAX_LINE];
    int corrent_line = FIRST_LINE;
    /* parse lines until we reach the end of the file */
    while(fgets(command_line, MAX_LINE, ifp) != NULL) {
        parse_line_second_pass(command_line, errors_in_file, head_symbol, head_extern, head_instruction,
        head_data, ic, corrent_line, file_name);
        corrent_line++;
    }
}

/* free all the linked lists defined dynamically in the program - symbols, externals occurences, instructions and data binary code */
void free_all_data_structures(SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data)
{
    /* use free methods defined in the data_structures_functions module */
    free_symbol_list(head_symbol);
    free_extern_list(head_extern);
    free_instruction_list(head_instruction);
    free_data_list(head_data);
}
