#include "assembler.h"


int analyze_first_buffer(char *token, char *label, int *error_in_file, int corrent_line)
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
        fprintf(stdout, "Line %d in file: first argument inline is incorrect - not a defined label or command. \n",
        corrent_line);
    }
    return UNDEFINED; /* or return 0, need to think about it */
}

void parse_line_first_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, ExternPtr *extern_head,
InstructionPtr *instruction_head, DataPtr *data_head, int *dc, int *ic, int corrent_line)
{
    char *delim = " \t\n";
    char *token;
    int buffer_type, label_flag=FALSE;
    char optional_label[MAX_LABEL_SIZE] = "";
    char line_copy[MAX_LINE] = "";
    strncat(line_copy, line, strlen(line));
    token = strtok(line, delim);
    buffer_type = analyze_first_buffer(token, optional_label, error_in_file, corrent_line);
    if (buffer_type ==  EMPTY_OR_COMMENT || buffer_type == UNDEFINED){
        return;
    }
    if (buffer_type == LABEL) {
        label_flag = TRUE;
        token = strtok(NULL, delim);
        if (!check_command_exists(token)) {
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file: command doesn't exist. \n", corrent_line);
            return;
        }
    }
    if (!strcmp(token, ".data") || !strcmp(token, ".string")) {
        parse_string_or_data_line(optional_label, token, label_flag, symbol_head, data_head, error_in_file,
        dc, line_copy, token + strlen(token) - line, corrent_line);
    } else if (!strcmp(token, ".entry") || !strcmp(token, ".extern")) {
        parse_entry_or_extern_line(token, extern_head, symbol_head, error_in_file, line_copy,
        token + strlen(token) - line, corrent_line);
    } else { /* this is an operation */
        parse_operation_line(optional_label, token, label_flag, symbol_head, instruction_head, error_in_file, ic,
        line_copy, token + strlen(token) - line, corrent_line);
    }
}

void parse_string_or_data_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head,
DataPtr *data_head, int* error_in_file, int *dc, char *line, int index_of_arguments, int corrent_line)
{
    if (label_flag == TRUE) {
        if (check_label_duplication_in_symbols(label, *symbol_head) == FALSE) {
            add_symbol(symbol_head, label, strlen(label), *dc, DATA, FALSE, FALSE);
        } else {  
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file: This label already exists! \n", corrent_line);
            return;
        }
    }
    if (!strcmp(command, ".data")) {
        parse_data_line(line, index_of_arguments, data_head, error_in_file, dc, corrent_line);
    } else {  /* buffer is ".string" */
        parse_string_line(line, index_of_arguments, data_head, error_in_file, dc, corrent_line);
    }
}

void parse_data_line(char line[], int index_of_arguments, DataPtr *data_head, int* error_in_file, int *dc,
int corrent_line)
{
    char line_copy[MAX_LINE] = "";
    char *delim = " \t,\n";
    char *token;
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (check_data_arguments(line_copy) == TRUE) {
        token = strtok(line+index_of_arguments, delim);
        while (token != NULL) {
            add_data(data_head, *dc, atol(token));
            token = strtok(NULL, delim);
            (*dc)++;
        }
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file: Wrong arguments for data: invalid arguments or commas.\n", corrent_line);
    }
}

void parse_string_line(char line[], int index_of_arguments, DataPtr *data_head, int* error_in_file, int *dc,
int corrent_line)
{
    char *delim = " \t\n";
    char *token;
    if (check_string_argument(line+index_of_arguments) == TRUE) {
        token = strtok(line+index_of_arguments, delim);
        token++;
        while (*token != '\"') {
            add_data(data_head, *dc, *token);
            token++;
            (*dc)++;
        }
        add_data(data_head, *dc, 0);
        (*dc)++;
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file: Wrong argument for string: invalid argument.\n", corrent_line);
    }
}

void parse_entry_or_extern_line(char *command, ExternPtr *extern_head, SymbolPtr *symbol_head, int* error_in_file,
char *line, int index_of_arguments, int corrent_line)
{
    if (!strcmp(command, ".entry")) {
        return;
    } else {
        parse_extern_line(line, index_of_arguments, extern_head, symbol_head, error_in_file, corrent_line);
    }
}

void parse_extern_line(char *line, int index_of_arguments, ExternPtr *extern_head, SymbolPtr *symbol_head,
int *error_in_file, int corrent_line)
{
    char line_copy[MAX_LINE] = "";
    char *delim = " \t\n";
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
                fprintf(stdout, "Line %d in file: This label already exists, and not as external.\n", corrent_line);
            }
        }
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file: Wrong argument for extern: invalid argument.\n", corrent_line);
    }
}

void parse_operation_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head,
InstructionPtr *instruction_head, int* error_in_file, int *ic, char *line, int index_of_arguments, int corrent_line)
{
    char line_copy[MAX_LINE] = "";
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (label_flag == TRUE) {
        if (check_label_duplication_in_symbols(label, *symbol_head) == FALSE) {
            add_symbol(symbol_head, label, strlen(label), *ic, CODE, FALSE, FALSE);
        } else {  
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file: This label already exists. \n", corrent_line);
            return;
        }
    }
    if(check_instruction_arguments(line_copy, command)) {
        compile_instruction_line(line+index_of_arguments, command, symbol_head, instruction_head, ic);
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file: Invalid arguments for this opcode instruction \n", corrent_line);
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

int get_register_index(char *reg)
{
    int i;
    for (i=0 ; i < 8 ; i++) {
        if (!strcmp(reg, registers[i])) {
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
        if (check_data_argument(operand) == FALSE) {
            return NONE;
        } else {
            return 0;
        }
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

long get_number_from_operand_adressing_zero(char *operand)
{
    char num_in_string[MAX_LABEL_SIZE] = "";
    strncat(num_in_string, operand + 1, strlen(operand) - 1);
    return atol(num_in_string);
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

int is_legal_filename_length(char *file_name)
{
    if(strlen(file_name) > MAX_FILE_NAME) {
        return FALSE;
    }
    return TRUE;
}

int add_suffix_to_file(char *file_name, char *file_name_with_suffix, int suffix)
{
    if(is_legal_filename_length(file_name)) {
        strncpy(file_name_with_suffix, file_name, strlen(file_name));
        if (suffix == FILENAME_SUFFIX) {
            strncat(file_name_with_suffix, ".as", 3);
        } else if (suffix == OBJECT_OUTPUT) {
            strncat(file_name_with_suffix, ".ob", 3);
        } else if (suffix == ENTRY_OUTPUT) {
            strncat(file_name_with_suffix, ".ent", 4);
        } else if (suffix == EXTERN_OUTPUT) {
            strncat(file_name_with_suffix, ".ext", 4);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}