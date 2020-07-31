#include "assembler.h"


int analyze_first_buffer(char *token, char *label, int *error_in_file)
{
    int local_error=TRUE;

    if (token == NULL || token[0] == ';') {
        return EMPTY_OR_COMMENT; /* empty line or comment line */
    } 
    else if (check_correct_label(token)) {
        local_error = FALSE;
        strncat(label, token, strlen(token)-1);
        return LABEL;
    } else if (check_command_exists(token)) {
        local_error = FALSE;
        return COMMAND;
    }
    if (local_error) {
        *error_in_file = TRUE;
        fprintf(stdout, "first argument inline is incorrect - not a defined label or command. \n");
    }
    return UNDEFINED; /* or return 0, need to think about it */
}

void parse_line_first_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, int *dc, int *ic)
{
    char *delim = " \t";
    char *token;
    int buffer_type, label_flag=FALSE;
    char optional_label[MAX_LABEL_SIZE];
    token = strtok(line, delim);
    buffer_type = analyze_first_buffer(token, optional_label, error_in_file);
    if (buffer_type ==  EMPTY_OR_COMMENT || buffer_type == UNDEFINED){
        return;
    }
    if (buffer_type == LABEL) {
        label_flag = TRUE;
        token = strtok(NULL, delim);
        if (!check_command_exists(token)) {
            fprintf(stdout, "command doesn't exist. \n");
            return;
        }
    }
    if (!strcmp(token, ".data") || !strcmp(token, ".string")) {
        parse_string_or_data_line(optional_label, token, label_flag, symbol_head, error_in_file, dc, line,
        token - line);
    } else if (!strcmp(token, ".entry") || !strcmp(token, ".extern")) {
        /*compile_entry_or_extern_line(token);*/
    } else { /* this is an operation */
        /*compile_operation_line(optional_label ,token, label_flag);*/
    }
}

void parse_string_or_data_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head, int* error_in_file, 
int *dc, char *line, int index_of_arguments)
{
    SymbolPtr added_symbol_ptr;
    if (label_flag == TRUE) {
        if (check_label_duplication_in_symbols(label, *symbol_head) == FALSE) {
            add_symbol(label, strlen(label), symbol_head, *dc, DATA, 0, 0);
        } else {  
            *error_in_file = TRUE;
            fprintf(stdout, "This label already exists! \n");
            return;
        }
    }
    if (!strcmp(command, ".data")) {
        /*compile_data_line(line, index_of_arguments, symbol_head, error_in_file, dc);*/
    } else {  /* buffer is ".string" */
        /*compile_string_line();*/
    }
}

/*
void compile_data_line(char *line, int index_of_arguments, SymbolPtr symbol_head, int* error_in_file, int *dc)
{
    make copy of corrent token
    if (check_data_arguments(copy_token) == TRUE) {
        ...code data in data memory + change DC...
    } else {
        *no_errors = FALSE;
        stdout(".....");
    }
}
*/