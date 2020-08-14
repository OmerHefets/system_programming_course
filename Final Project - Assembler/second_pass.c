#include "assembler.h"

void parse_line_second_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, ExternPtr *extern_head,
InstructionPtr *instruction_head, DataPtr *data_head, int *ic, int corrent_line)
{
    char *delim = " \t\n";
    char *token;
    int buffer_type;
    char line_copy[MAX_LINE] = "";
    int index_of_arguments;
    strncat(line_copy, line, strlen(line));
    token = strtok(line, delim);
    buffer_type = analyze_first_buffer_second_pass(token);
    if (buffer_type ==  EMPTY_OR_COMMENT || buffer_type == UNDEFINED){
        return;
    }
    if (buffer_type == LABEL) {
        token = strtok(NULL, delim);
    }
    index_of_arguments = token+strlen(token)-line;
    if (!strcmp(token, ".data") || !strcmp(token, ".string") || !strcmp(token, ".extern")) {
        return;
    } else if (!strcmp(token, ".entry")) {
        parse_entry_line_second_pass(*symbol_head, error_in_file, line_copy, index_of_arguments, corrent_line);
    } else { /* this is an operation */
        compile_instruction_line_second_pass(line_copy+index_of_arguments, token, *symbol_head,
        *instruction_head, extern_head, error_in_file, ic, corrent_line);
    }    
}

int analyze_first_buffer_second_pass(char *token)
{
    if (token == NULL || token[0] == ';') {
        return EMPTY_OR_COMMENT; /* empty line or comment line */
    } 
    else if (check_correct_label(token)) {
        return LABEL;
    } else if (check_command_exists(token)) {
        return COMMAND;
    }
    return UNDEFINED; /* or return 0, need to think about it */
}

void parse_entry_line_second_pass(SymbolPtr head_symbol, int *error_in_file, char *line, int index_of_arguments, int corrent_line)
{
    char line_copy[MAX_LINE] = "";
    char *delim = " \t\n";
    char *token;
    SymbolPtr optional_existing_label;
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (check_extern_argument(line_copy) == TRUE) {
        token = strtok(line+index_of_arguments, delim);
        if(check_label_duplication_in_symbols(token, head_symbol) == TRUE) {
            optional_existing_label = get_symbol_by_label(head_symbol, token);
            edit_symbol_entry(optional_existing_label, TRUE);
        } else {
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file: The label of entry doesn\'t exist in the file.\n", corrent_line);
        }
    }
}

void compile_instruction_line_second_pass(char *args_line, char *command, SymbolPtr symbol_head,
InstructionPtr instruction_head, ExternPtr *extern_head, int *error_in_file, int *ic, int corrent_line)
{
    int num_of_operands = opcodes_number_of_operands[get_command_index(command)];
    (*ic)++;
    if (num_of_operands == 0) {
        return;
    } else if (num_of_operands == 1) {
        instruction_line_one_operand_second_pass(args_line, command, symbol_head, instruction_head,
        extern_head, error_in_file, ic, corrent_line);
    } else {
        instruction_line_two_operands_second_pass(args_line, command, symbol_head, instruction_head,
        extern_head, error_in_file, ic, corrent_line);
    }
}

void instruction_line_one_operand_second_pass(char *args_line, char *command, SymbolPtr symbol_head, InstructionPtr instruction_head,
ExternPtr *extern_head, int *error_in_file ,int *ic, int corrent_line)
{
    char *delim = " \t\n";
    char *token;
    token = strtok(args_line, delim);
    compile_operand_second_pass(token, instruction_head, symbol_head, extern_head, error_in_file, ic, corrent_line);
}

void instruction_line_two_operands_second_pass(char *args_line, char *command, SymbolPtr symbol_head, InstructionPtr instruction_head,
ExternPtr *extern_head ,int *error_in_file, int *ic, int corrent_line)
{ 
    char *delim = " \t,\n";
    char *token;
    char two_tokens[2][MAX_LABEL_SIZE] = {"", ""};
    token = strtok(args_line, delim);
    strncat(two_tokens[0], token, 20);
    token = strtok(NULL, delim);
    strncat(two_tokens[1], token, 20);
    compile_operand_second_pass(two_tokens[0], instruction_head, symbol_head, extern_head, error_in_file, ic, corrent_line);
    compile_operand_second_pass(two_tokens[1], instruction_head, symbol_head, extern_head, error_in_file, ic, corrent_line);
}

void compile_operand_second_pass(char *operand, InstructionPtr instruction_head, SymbolPtr symbol_head,
ExternPtr *extern_head, int *error_in_file, int *ic, int corrent_line)
{
    unsigned long int command_value = 0;
    int operand_type = get_operand_type(operand);
    printf("%s\n", operand);
    if (operand_type == 1) {
        if (check_label_duplication_in_symbols(operand, symbol_head) == FALSE) {
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file: Label doesn\'t exists.\n", corrent_line);
        } else {
            command_value = get_symbol_memory(get_symbol_by_label(symbol_head, operand));
            command_value <<= 3;
            if (get_symbol_external(get_symbol_by_label(symbol_head, operand))) {
                code_are(&command_value, 'E');
            } else {
                code_are(&command_value, 'R');
            }
            edit_instruction_command(get_instruction_by_memory(instruction_head, *ic), command_value);
            if (get_symbol_external(get_symbol_by_label(symbol_head, operand)) == TRUE) {
                add_extern(extern_head, operand, strlen(operand), *ic);
            }
        }
    } else if (operand_type == 2) {
        if (check_label_duplication_in_symbols(operand+1, symbol_head) == FALSE) {
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file: Label doesn\'t exists.\n", corrent_line);
        } else {
            command_value = (get_symbol_memory(get_symbol_by_label(symbol_head, operand+1)) - *ic + 1);
            command_value <<= 3;
            code_are(&command_value, 'A');
            if (get_symbol_external(get_symbol_by_label(symbol_head, operand+1)) == TRUE) {
                *error_in_file = TRUE;
                fprintf(stdout, "Line %d in file: Using Adressing method 2 on an external label is incorrect.\n", corrent_line);
            } else {
                edit_instruction_command(get_instruction_by_memory(instruction_head, *ic), command_value);
            }
        }
    }
    if (operand_type != 3) {
        (*ic)++;
    }
}