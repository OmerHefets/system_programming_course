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

void parse_line_first_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, ExternPtr *extern_head,
InstructionPtr *instruction_head, DataPtr *data_head, int *dc, int *ic)
{
    char *delim = " \t";
    char *token;
    int buffer_type, label_flag=FALSE;
    char optional_label[MAX_LABEL_SIZE] = "";
    char line_copy[MAX_LINE] = "";
    strncat(line_copy, line, strlen(line));
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
        parse_string_or_data_line(optional_label, token, label_flag, symbol_head, data_head, error_in_file,
        dc, line_copy, token + strlen(token) - line);
    } else if (!strcmp(token, ".entry") || !strcmp(token, ".extern")) {
        parse_entry_or_extern_line(token, extern_head, symbol_head, error_in_file, line_copy,
        token + strlen(token) - line);
    } else { /* this is an operation */
        parse_operation_line(optional_label, token, label_flag, symbol_head, instruction_head, error_in_file, ic,
        line_copy, token + strlen(token) - line);
    }
}

void parse_string_or_data_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head,
DataPtr *data_head, int* error_in_file, int *dc, char *line, int index_of_arguments)
{
    if (label_flag == TRUE) {
        if (check_label_duplication_in_symbols(label, *symbol_head) == FALSE) {
            add_symbol(symbol_head, label, strlen(label), *dc, DATA, FALSE, FALSE);
        } else {  
            *error_in_file = TRUE;
            fprintf(stdout, "This label already exists! \n");
            return;
        }
    }
    if (!strcmp(command, ".data")) {
        parse_data_line(line, index_of_arguments, data_head, error_in_file, dc);
    } else {  /* buffer is ".string" */
        parse_string_line(line, index_of_arguments, data_head, error_in_file, dc);
    }
}

void parse_data_line(char line[], int index_of_arguments, DataPtr *data_head, int* error_in_file, int *dc)
{
    char line_copy[MAX_LINE] = "";
    char *delim = " \t,";
    char *token;
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (check_data_arguments(line_copy) == TRUE) {
        token = strtok(line+index_of_arguments, delim);
        while (token != NULL) {
            add_data(data_head, *dc, atoi(token));
            token = strtok(NULL, delim);
            (*dc)++;
        }
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Wrong arguments for data: invalid arguments or commas.\n");
    }
}

void parse_string_line(char line[], int index_of_arguments, DataPtr *data_head, int* error_in_file, int *dc)
{
    char *delim = " \t";
    char *token;
    if (check_string_argument(line+index_of_arguments) == TRUE) {
        token = strtok(line+index_of_arguments, delim);
        token++;
        while (*token != '\"') {
            add_data(data_head, *dc, *token);
            token++;
            (*dc)++;
        }
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Wrong argument for string: invalid argument.\n");
    }
}

void parse_entry_or_extern_line(char *command, ExternPtr *extern_head, SymbolPtr *symbol_head, int* error_in_file,
char *line, int index_of_arguments)
{
    if (!strcmp(command, ".entry")) {
        return;
    } else {
        parse_extern_line(line, index_of_arguments, extern_head, symbol_head, error_in_file);
    }
}

void parse_extern_line(char *line, int index_of_arguments, ExternPtr *extern_head, SymbolPtr *symbol_head,
int *error_in_file)
{
    char line_copy[MAX_LINE] = "";
    char *delim = " \t";
    char *token;
    SymbolPtr optional_existing_label;
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (check_extern_argument(line_copy) == TRUE) {
        token = strtok(line+index_of_arguments, delim);
        if(check_label_duplication_in_symbols(token, *symbol_head) == FALSE) {
            add_symbol(symbol_head, token, strlen(token), 0, NONE, TRUE, FALSE);
        } else {
            optional_existing_label = get_symbol_by_label(*symbol_head, token);
            if (get_symbol_external(optional_existing_label) == FALSE) {
                *error_in_file = TRUE;
                fprintf(stdout, "This label already exists, and not as external.\n");
            }
        }
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Wrong argument for extern: invalid argument.\n");
    }
}

void parse_operation_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head,
InstructionPtr *instruction_head, int* error_in_file, int *ic, char *line, int index_of_arguments)
{
    char line_copy[MAX_LINE] = "";
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (label_flag == TRUE) {
        if (check_label_duplication_in_symbols(label, *symbol_head) == FALSE) {
            add_symbol(symbol_head, label, strlen(label), *ic, CODE, FALSE, FALSE);
        } else {  
            *error_in_file = TRUE;
            fprintf(stdout, "This label already exists! \n");
            return;
        }
    }
    if(check_instruction_arguments(line_copy, command)) {
        printf("success\n");
        /*...code the instructions that you can in the DB...*/
    } else {
        fprintf(stdout, "Invalid arguments for this opcode instruction \n");
    }
}






int get_command_index(char *command)
{
    int i;
    for (i=0 ; i < 16 ; i++) {
        if (!strcmp(command, opcodes[i])) {
            return i;
        }
    }
    return -1;
}

int get_operand_type(char *operand)
{
    char temp_operand[MAX_LABEL_SIZE] = "";
    char temp_operand2[MAX_LABEL_SIZE] = "";
    if (operand == NULL) {
        return NONE;
    }
    strncat(temp_operand, operand, strlen(operand));
    strncat(temp_operand, ":", 1);
    if (operand[0] == '#') {
        operand++;
        while (*operand != '\0' && *operand != '\n') {
            if(!isdigit(*operand)) {
                return NONE;
            }
            operand++;
        }
        return 0;
    } else if (check_correct_label(temp_operand)) {
        return 1;
    }
    strncat(temp_operand2, operand+1, strlen(operand)-1);
    strncat(temp_operand2, ":", 1);
    if (operand[0] == '&' && check_correct_label(temp_operand2)) {
        return 2;
    } else if (check_correct_register(operand)) {
        return 3;
    }
    return NONE;
}

int is_legal_operand_type(int *optional_operands, int operand_type)
{
    int i;
    for (i=0 ; i < 3 ; i++) {
        if (optional_operands[i] == operand_type) {
            return TRUE;
        }
    }
    return FALSE;
}