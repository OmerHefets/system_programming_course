/** 
 * In this module are defined all functions needed for parsing lines in the first pass of the algorithm:
 * checking the line type (comment, command, data, etc.), adding labels to the symbols list, and coding the possible instruction lines
 * to the instruction list + all data
 */  

#include "assembler.h"

/* parses the first token in a line and decides the type of the line for further parsing and error checking */
void parse_line_first_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, ExternPtr *extern_head,
InstructionPtr *instruction_head, DataPtr *data_head, int *dc, int *ic, int corrent_line, char *file_name)
{
    char *delim = " \t\n";
    char *token;
    int buffer_type, label_flag=FALSE;
    char optional_label[MAX_LABEL_SIZE] = "";
    char line_copy[MAX_LINE] = "";
    strncat(line_copy, line, strlen(line));
    token = strtok(line, delim); /* get first token in line without whitespace chars*/
    /* analyze if the token is a comment line, label or a command.
    if it's a label, the optional label will store that label */
    buffer_type = analyze_first_buffer(token, optional_label, error_in_file, corrent_line, file_name);
    if (buffer_type ==  EMPTY_OR_COMMENT || buffer_type == UNDEFINED){
        return; /* skip if comment. if it gets the UNDIFINED VALUE, the error was already defined in the buffer analysis. */
    }
    if (buffer_type == LABEL) { /* if its a label, read another token that needs to be a command*/
        label_flag = TRUE; /* turn label flag to TRUE */
        token = strtok(NULL, delim);
        if (!check_command_exists(token)) { /* check for a valid command */
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file %s: command doesn't exist. \n", corrent_line, file_name);
            return;
        }
    }
    /* check command type for further parsing of operands for that command */
    if (!strcmp(token, ".data") || !strcmp(token, ".string")) {
        parse_string_or_data_line(optional_label, token, label_flag, symbol_head, data_head, error_in_file,
        dc, line_copy, token + strlen(token) - line, corrent_line, file_name);
    } else if (!strcmp(token, ".entry") || !strcmp(token, ".extern")) {
        parse_entry_or_extern_line(token, extern_head, symbol_head, error_in_file, line_copy,
        token + strlen(token) - line, corrent_line, file_name);
    } else { /* this is an operation */
        parse_operation_line(optional_label, token, label_flag, symbol_head, instruction_head, error_in_file, ic,
        line_copy, token + strlen(token) - line, corrent_line, file_name);
    }
}

/* analyze the first buffer found in a line */
int analyze_first_buffer(char *token, char *label, int *error_in_file, int corrent_line, char *file_name)
{
    int local_error=TRUE;

    if (token == NULL || token[0] == ';') {
        return EMPTY_OR_COMMENT; /* empty line or comment line */
    } 
    else if (check_correct_label(token)) {
        local_error = FALSE; /* turn local error to FALSE if the token is a correct label or command (afterwards checks for command) */
        strncat(label, token, strlen(token)-1);
        return LABEL;
    } else if (check_command_exists(token)) {
        local_error = FALSE;
        return COMMAND;
    }
    if (local_error) {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file %s: first argument inline is incorrect - not a defined label or command. \n",
        corrent_line, file_name);
    }
    return UNDEFINED; /* will return UNDEFINED only if there is an error in the token */
}

/* parse a line of string or data command */
void parse_string_or_data_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head,
DataPtr *data_head, int* error_in_file, int *dc, char *line, int index_of_arguments, int corrent_line, char *file_name)
{
    if (label_flag == TRUE) { /* if a labe exists, make sure that this label is unique */
        if (check_label_duplication_in_symbols(label, *symbol_head) == FALSE) {
            add_symbol(symbol_head, label, strlen(label), *dc, DATA, FALSE, FALSE);
        } else {  
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file %s: This label already exists.\n", corrent_line, file_name);
            return;
        }
    }
    if (!strcmp(command, ".data")) {
        parse_data_line(line, index_of_arguments, data_head, error_in_file, dc, corrent_line, file_name);
    } else {  /* buffer is ".string" */
        parse_string_line(line, index_of_arguments, data_head, error_in_file, dc, corrent_line, file_name);
    }
}

/* parse a data line */
void parse_data_line(char line[], int index_of_arguments, DataPtr *data_head, int* error_in_file, int *dc,
int corrent_line, char *file_name)
{
    char line_copy[MAX_LINE] = "";
    char *delim = " \t,\n";
    char *token;
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (check_data_arguments(line_copy) == TRUE) { /* if data arguments are valid, add them to the data list */
        token = strtok(line+index_of_arguments, delim);
        while (token != NULL) {
            /* important implementation note: data will be added to the data list as defined in the number,
            but only the first 24 bits will be used later and printed to the user.
            large numbers with more than 24 bits will lose their most left bits. */
            add_data(data_head, *dc, atol(token)); 
            token = strtok(NULL, delim);
            (*dc)++;
        }
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file %s: Wrong arguments for data: invalid arguments or commas.\n", 
        corrent_line, file_name);
    }
}

/* parse a string line */
void parse_string_line(char line[], int index_of_arguments, DataPtr *data_head, int* error_in_file, int *dc,
int corrent_line, char *file_name)
{
    char *delim = " \t\n";
    char *token;
    if (check_string_argument(line+index_of_arguments) == TRUE) { /* if the string is correct, add the chars to the data list */
        token = strtok(line+index_of_arguments, delim);
        token++;
        while (*token != '\"') {
            add_data(data_head, *dc, *token);
            token++;
            (*dc)++;
        }
        add_data(data_head, *dc, RESET_DATA_VALUE); /* add a '\0' char at the end of the list */
        (*dc)++;
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file %s: Wrong argument for string: invalid argument.\n", 
        corrent_line, file_name);
    }
}

/* parse a line with an extern or an entry command. ignore labels in these commands */
void parse_entry_or_extern_line(char *command, ExternPtr *extern_head, SymbolPtr *symbol_head, int* error_in_file,
char *line, int index_of_arguments, int corrent_line, char *file_name)
{
    if (!strcmp(command, ".entry")) {
        return; /* pass on entry commands on the first pass */
    } else {
        parse_extern_line(line, index_of_arguments, extern_head, symbol_head, error_in_file, corrent_line, file_name);
    }
}

/* parse extern line */
void parse_extern_line(char *line, int index_of_arguments, ExternPtr *extern_head, SymbolPtr *symbol_head,
int *error_in_file, int corrent_line, char *file_name)
{
    char line_copy[MAX_LINE] = "";
    char *delim = " \t\n";
    char *token;
    SymbolPtr optional_existing_label;
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (check_extern_argument(line_copy) == TRUE) { /* check extern value defined as a correct argument */
        token = strtok(line+index_of_arguments, delim);
        if(check_label_duplication_in_symbols(token, *symbol_head) == FALSE) {
            add_symbol(symbol_head, token, strlen(token), RESET_DATA_VALUE, NONE, TRUE, FALSE);
        } else {
            optional_existing_label = get_symbol_by_label(*symbol_head, token);
            if (get_symbol_external(optional_existing_label) == FALSE) { /* the symbol can already exist, but only as an extern. */
                *error_in_file = TRUE;
                fprintf(stdout, "Line %d in file %s: This label already exists, and not as external.\n", 
                corrent_line, file_name);
            } /* if this label already exists as an extern, the assembler will ignore it and continue */
        }
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file %s: Wrong argument for extern: invalid argument.\n", 
        corrent_line, file_name);
    }
}

/* parse an operation line with its arguments */
void parse_operation_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head, InstructionPtr *instruction_head, 
int* error_in_file, int *ic, char *line, int index_of_arguments, int corrent_line, char *file_name)
{
    char line_copy[MAX_LINE] = "";
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (label_flag == TRUE) {
        if (check_label_duplication_in_symbols(label, *symbol_head) == FALSE) { /* check that the label is unique */
            add_symbol(symbol_head, label, strlen(label), *ic, CODE, FALSE, FALSE);
        } else {  
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file %s: This label already exists.\n", corrent_line, file_name);
            return;
        }
    }
    if(check_instruction_arguments(line_copy, command)) { /* if the arguments are valid, continue to compile the line to machine code */
        compile_instruction_line(line+index_of_arguments, command, symbol_head, instruction_head, ic);
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file %s: Invalid arguments for this opcode instruction.\n", 
        corrent_line, file_name);
    }
}