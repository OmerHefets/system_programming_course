#include "assembler.h"

void first_pass(..., *no_errors)
{
    while(getline != EOF) {
        nituah_line_first(..., *no_errors);
    }
    update_data_symbols(symbols_table);
}



void parse_operation_line(char *line, int *error_in_file, SymbolPtr *symbol_head, ExternPtr *extern_head,
InstructionPtr *instruction_head, DataPtr *data_head, int *dc, int *ic)
{
    if (label_flag == TRUE) {
        if (check_label_duplication_in_symbols(label, *symbol_head) == FALSE) {
            add_symbol(symbol_head, label, strlen(label), *ic, CODE, 0, 0);
        } else {  
            *error_in_file = TRUE;
            fprintf(stdout, "This label already exists! \n");
            return;
        }
    }
    if (check_if_operation_exists(buffer) == TRUE) {
        if(check_operation_arguments(buffer, token)) {
            ...code the instructions that you can in the DB...
        } else {
            /* first error */
        }
    } else {
        /* second error */
    }
}
