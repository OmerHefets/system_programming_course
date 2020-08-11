#include "assembler.h"

void compile_multiple_files(int argc, char *argv[])
{
    FILE *ifp;
    char *prog_name = argv[0];
    if (argc == 1) {
        fprintf(stdout, "The assembler didn't get any files.\n");
    }
    while (--argc > 0) {
        /* ADD SUFFIX FUNC */
        if ((ifp = fopen(*++argv, "r")) == NULL) {
            fprintf(stdout, "%s: can't open %s for reading\n", prog_name, argv[0]);
            exit(1);
        } else {
            compile_file(ifp);
            fclose(ifp);
        }
    }
}

void compile_file(FILE *ifp)
{
    /* print error by line in input */
    SymbolPtr head_symbol = NULL;
    ExternPtr head_extern = NULL;
    InstructionPtr head_instruction = NULL;
    DataPtr head_data = NULL;
    int *dc, *ic, *errors_in_file, dcf = 0, icf = 100, error = FALSE, pos;
    dc = &dcf, ic = &icf, errors_in_file = &error;
    pos = ftell(ifp);
    first_pass(ifp, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, errors_in_file);
    fseek(ifp, pos, SEEK_SET);

    if (*errors_in_file == FALSE) {
        *ic = 100;
        second_pass(ifp, &head_symbol, &head_extern, &head_instruction, &head_data, ic, errors_in_file);
    }
    if (*errors_in_file == FALSE) {
        create_files(head_symbol, head_extern, head_instruction, head_data, *ic, *dc);
    }
    free_all_data_structures(head_symbol, head_extern, head_instruction, head_data);
}

void first_pass(FILE *ifp, SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data, int *dc, int *ic, int *errors_in_file)
{
    char command_line[MAX_LINE];
    while(fgets(command_line, MAX_LINE, ifp) != NULL) {
        parse_line_first_pass(command_line, errors_in_file, head_symbol, head_extern, head_instruction,
        head_data, dc, ic);
    }
    update_data_memory_in_symbol_table(*head_symbol, *ic);
    update_data_memory_in_data_table(*head_data, *ic);
}

void second_pass(FILE *ifp, SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data, int *ic, int *errors_in_file)
{
    char command_line[MAX_LINE];
    while(fgets(command_line, MAX_LINE, ifp) != NULL) {
        parse_line_second_pass(command_line, errors_in_file, head_symbol, head_extern, head_instruction,
        head_data, ic);
    }
}

void free_all_data_structures(SymbolPtr head_symbol, ExternPtr head_extern, InstructionPtr head_instruction,
DataPtr head_data)
{
    free_symbol_list(head_symbol);
    free_extern_list(head_extern);
    free_instruction_list(head_instruction);
    free_data_list(head_data);
}
