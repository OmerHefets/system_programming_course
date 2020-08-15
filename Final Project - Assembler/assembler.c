#include "assembler.h"

int main(int argc, char *argv[])
{
    compile_multiple_files(argc, argv);
    return EXIT_WITH_SUCESS; 
}

void compile_multiple_files(int argc, char *argv[])
{
    FILE *ifp_first_pass, *ifp_second_pass;
    char *prog_name = *argv;
    char file_name[MAX_FILE_NAME_WITH_SUFFIX];
    if (argc == ONLY_COMMAND_NO_FILES) {
        fprintf(stdout, "The assembler didn't get any files.\n");
    }
    while (--argc > NO_ARGUMENTS) {
        if(!add_suffix_to_file(*++argv, file_name, FILENAME_SUFFIX)) {
            fprintf(stdout, "%s: can't open %s because file name is too long", prog_name, *argv);
        }
        else if (((ifp_first_pass = fopen(file_name, "r")) == NULL) || ((ifp_second_pass = fopen(file_name, "r")) == NULL)) {
            fprintf(stdout, "%s: can't open %s for reading\n", prog_name, *argv);
        } else {
            compile_file(ifp_first_pass, ifp_second_pass, *argv);
            fclose(ifp_first_pass);
            fclose(ifp_second_pass);
        }
        memset(file_name, UNDEFINED, strlen(file_name));
    }
}

void compile_file(FILE *ifp_first_pass, FILE *ifp_second_pass, char *file_name)
{
    SymbolPtr head_symbol = NULL;
    ExternPtr head_extern = NULL;
    InstructionPtr head_instruction = NULL;
    DataPtr head_data = NULL;
    int *dc, *ic, *errors_in_file, dcf = DATA_MEMORY_START, icf = INSTRUCTION_MEMORY_START, error = FALSE;
    dc = &dcf, ic = &icf, errors_in_file = &error;
    first_pass(ifp_first_pass, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, errors_in_file, file_name);

    if (*errors_in_file == FALSE) {
        *ic = INSTRUCTION_MEMORY_START;
        second_pass(ifp_second_pass, &head_symbol, &head_extern, &head_instruction, &head_data, ic, errors_in_file, file_name);
    }
    if (*errors_in_file == FALSE) {
        create_files(head_symbol, head_extern, head_instruction, head_data, *ic, *dc, file_name);
    }
    free_all_data_structures(&head_symbol, &head_extern, &head_instruction, &head_data);
}

void first_pass(FILE *ifp, SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data, int *dc, int *ic, int *errors_in_file, char *file_name)
{
    char command_line[MAX_LINE];
    int corrent_line = FIRST_LINE;
    while(fgets(command_line, MAX_LINE, ifp) != NULL) {
        parse_line_first_pass(command_line, errors_in_file, head_symbol, head_extern, head_instruction,
        head_data, dc, ic, corrent_line, file_name);
        corrent_line++;
    }
    update_data_memory_in_symbol_table(*head_symbol, *ic);
    update_data_memory_in_data_table(*head_data, *ic);
}

void second_pass(FILE *ifp, SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data, int *ic, int *errors_in_file, char *file_name)
{
    char command_line[MAX_LINE];
    int corrent_line = FIRST_LINE;
    while(fgets(command_line, MAX_LINE, ifp) != NULL) {
        parse_line_second_pass(command_line, errors_in_file, head_symbol, head_extern, head_instruction,
        head_data, ic, corrent_line, file_name);
        corrent_line++;
    }
}

void free_all_data_structures(SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data)
{
    free_symbol_list(head_symbol);
    free_extern_list(head_extern);
    free_instruction_list(head_instruction);
    free_data_list(head_data);
}
