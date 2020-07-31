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

void parse_line_first_pass(char *line, int *error_in_file, SymbolPtr symbol_head)
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
        printf("its data or string\n");
        parse_string_or_data_line(optional_label, token, label_flag, symbol_head);
    } else if (!strcmp(token, ".entry") || !strcmp(token, ".extern")) {
        printf("its entry or extern\n");
        /*compile_entry_or_extern_line(token);*/
    } else { /* this is an operation */
        printf("its an operation\n");
        /*compile_operation_line(optional_label ,token, label_flag);*/
    }
}

void parse_string_or_data_line(char *label, char *command, int label_flag, SymbolPtr symbol_head)
{
    if (label_flag == TRUE) {
        if (check_label_duplication(label, symbol_head) == FALSE) {
            insert_label();
        } else {  this label already exists 
            *no_error = FALSE;
            stdout("this is the error...");
            return;
        }
    }
    if buffer == ".data" {
        compile_data_line();
    } else {  buffer is ".string" 
        compile_string_line();
    }
}
