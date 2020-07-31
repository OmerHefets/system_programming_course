#include "assembler.h"

void first_pass(..., *no_errors)
{
    while(getline != EOF) {
        nituah_line_first(..., *no_errors);
    }
    update_data_symbols(symbols_table);
}



void compile_data_line()
{
    /* make copy of corrent token */
    if (check_data_arguments(copy_token) == TRUE) {
        ...code data in data memory + change DC...
    } else {
        *no_errors = FALSE;
        stdout(".....");
    }
}

void compile_string_line()
{
    /* make copy of corrent token */
    if (check_string_arguments(copy_token) == TRUE) {
        ...code string data in data memory + change DC...
    } else {
        *no_errors = FALSE;
        stdout(".........");
    }
}

void compile_entry_or_extern_line()
{
    /* optional: add warning if label exists */
    if buffer == ".entry" {
        return; /* void... */
    } else { /* the buffer is ".extern" */
        compile_extern_line();
    }
}

void compile_extern_line()
{
    /* make copy of corrent token */
    if (check_extern_arguments(copy_token) == TRUE) {
        /*...get parameter and make sure he's not in the symbol's list (OK if as an extern), add him or error*/
    } else {
        *no_errors = FALSE;
        stdout("....");
    }
}

void compile_operation_line()
{
    if (LABEL == TRUE) {
        if (check_label_duplication(*optional_label, *label_table) == TRUE) {
            insert_label();
        } else { /* this label already exists */
            *no_error = FALSE;
            stdout("this is the error...");
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