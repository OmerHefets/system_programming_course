/**
 * This module defines all functions required for parsing a line in the second pass according to the algorithm defined in mmn14.
 * coding instruction lines for lines with labels as well.
 */

#include "assembler.h"

/* parses the first token in a line and analyzes it for further parsing */ 
void parse_line_second_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, ExternPtr *extern_head,
InstructionPtr *instruction_head, DataPtr *data_head, int *ic, int corrent_line, char *file_name)
{
    char *delim = " \t\n";
    char *token;
    int buffer_type;
    char line_copy[MAX_LINE] = "";
    int index_of_arguments;
    strncat(line_copy, line, strlen(line));
    token = strtok(line, delim);
    buffer_type = analyze_first_buffer_second_pass(token);
    /* analyze if the token is a comment line, label or a command.
    if it's a label, the optional label will store that label */
    if (buffer_type ==  EMPTY_OR_COMMENT || buffer_type == UNDEFINED){
        return; /* skip if comment. if it gets the UNDIFINED VALUE, the error was already defined in the buffer analysis. */
    }
    if (buffer_type == LABEL) { /* if a label exists, read another token which will be a command. no need to check for errors, that was made in the first pass */
        token = strtok(NULL, delim);
    }
    index_of_arguments = token+strlen(token)-line; /* get the index of pointer to the beginning of args inline */
    if (!strcmp(token, ".data") || !strcmp(token, ".string") || !strcmp(token, ".extern")) {
        return;
    } else if (!strcmp(token, ".entry")) {
        parse_entry_line_second_pass(*symbol_head, error_in_file, line_copy, index_of_arguments, corrent_line, file_name);
    } else { /* this is an operation */
        compile_instruction_line_second_pass(line_copy+index_of_arguments, token, *symbol_head,
        *instruction_head, extern_head, error_in_file, ic, corrent_line, file_name);
    }    
}

/* analyze the first buffer found in a line (for the second pass, with less error checking) */
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
    return UNDEFINED; /* second pass should not happen if the token is UNDEFINED in the first pass, so this return val should not be used */
}

/* parse an entry line and add its entry val to the required label */
void parse_entry_line_second_pass(SymbolPtr head_symbol, int *error_in_file, char *line, int index_of_arguments, 
int corrent_line, char *file_name)
{
    char line_copy[MAX_LINE] = "";
    char *delim = " \t\n";
    char *token;
    SymbolPtr optional_existing_label;
    strncat(line_copy, line+index_of_arguments, strlen(line));
    if (check_extern_argument(line_copy) == TRUE) { /* check the name of the entry arg - skipped during the first pass */
        token = strtok(line+index_of_arguments, delim);
        if(check_label_duplication_in_symbols(token, head_symbol) == TRUE) { /* make sure that this label already exists */
            optional_existing_label = get_symbol_by_label(head_symbol, token);
            edit_symbol_entry(optional_existing_label, TRUE); /* change entry to TRUE */
        } else {
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file %s: The label of entry doesn\'t exist in the file.\n", 
            corrent_line, file_name);
        }
    } else {
        *error_in_file = TRUE;
        fprintf(stdout, "Line %d in file %s: Invalid argument name for entry.\n", 
        corrent_line, file_name);
    }
}

/* get an instruction line and compile its arguments according to the command */
void compile_instruction_line_second_pass(char *args_line, char *command, SymbolPtr symbol_head,
InstructionPtr instruction_head, ExternPtr *extern_head, int *error_in_file, int *ic, int corrent_line, char *file_name)
{
    int num_of_operands = opcodes_number_of_operands[get_command_index(command)]; /* get number of existing operands to this opcode */
    (*ic)++;
    if (num_of_operands == 0) { /* using numbers here and not defined values for clearer code */
        return;
    } else if (num_of_operands == 1) {
        instruction_line_one_operand_second_pass(args_line, command, symbol_head, instruction_head,
        extern_head, error_in_file, ic, corrent_line, file_name);
    } else {
        instruction_line_two_operands_second_pass(args_line, command, symbol_head, instruction_head,
        extern_head, error_in_file, ic, corrent_line, file_name);
    }
}

/* parse and code a command line with one argument */
void instruction_line_one_operand_second_pass(char *args_line, char *command, SymbolPtr symbol_head, InstructionPtr instruction_head,
ExternPtr *extern_head, int *error_in_file ,int *ic, int corrent_line, char *file_name)
{
    char *delim = " \t\n";
    char *token;
    token = strtok(args_line, delim); /* get the argument */
    compile_operand_second_pass(token, instruction_head, symbol_head, extern_head, error_in_file, ic, 
    corrent_line, file_name);
}

/* parse and code a command line with two arguments */
void instruction_line_two_operands_second_pass(char *args_line, char *command, SymbolPtr symbol_head, InstructionPtr instruction_head,
ExternPtr *extern_head ,int *error_in_file, int *ic, int corrent_line, char *file_name)
{ 
    char *delim = " \t,\n";
    char *token;
    char two_tokens[2][MAX_LABEL_SIZE] = {"", ""}; /* define 2d array for the two arguments */
    token = strtok(args_line, delim); /* get first argument */
    strncat(two_tokens[FIRST_OPERAND], token, MAX_LABEL_SIZE);
    token = strtok(NULL, delim); /* get second argument */
    strncat(two_tokens[SECOND_OPERAND], token, MAX_LABEL_SIZE);
    compile_operand_second_pass(two_tokens[FIRST_OPERAND], instruction_head, symbol_head, extern_head, error_in_file, ic, 
    corrent_line, file_name);
    compile_operand_second_pass(two_tokens[SECOND_OPERAND], instruction_head, symbol_head, extern_head, error_in_file, ic, 
    corrent_line, file_name);
}

/* gets an operand and codes it to machine code if needed */
void compile_operand_second_pass(char *operand, InstructionPtr instruction_head, SymbolPtr symbol_head,
ExternPtr *extern_head, int *error_in_file, int *ic, int corrent_line, char *file_name)
{
    unsigned long int command_value = RESET_COMMAND_VALUE;
    int operand_type = get_operand_type(operand);
    if (operand_type == DIRECT_ADDRESSING) {
        if (check_label_duplication_in_symbols(operand, symbol_head) == FALSE) { /* label must already exist */
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file %s: Label doesn\'t exists.\n", corrent_line, file_name);
        } else {
            command_value = get_symbol_memory(get_symbol_by_label(symbol_head, operand)); /* get the memory address of that label from the symbol table + assign to the machine code  */
            command_value <<= SHIFT_BITS_FROM_A_R_E_CODING;
            if (get_symbol_external(get_symbol_by_label(symbol_head, operand))) { /* get if the label is external to know what A_R_E bit to turn on */
                code_are(&command_value, 'E');
            } else {
                code_are(&command_value, 'R');
            }
            edit_instruction_command(get_instruction_by_memory(instruction_head, *ic), command_value); /* edit instruction by ic of that specific instruction */
            if (get_symbol_external(get_symbol_by_label(symbol_head, operand)) == TRUE) {
                add_extern(extern_head, operand, strlen(operand), *ic); /* if this label was external as well, we will save its ic for the .ext file in the extern list */
            }
        }
    } else if (operand_type == RELATIVE_ADDRESSING) {
        if (check_label_duplication_in_symbols(operand+1, symbol_head) == FALSE) { /* start to read the operation from the second char since first one is '&' */
            *error_in_file = TRUE;
            fprintf(stdout, "Line %d in file %s: Label doesn\'t exists.\n", corrent_line, file_name);
        } else {
            command_value = (get_symbol_memory(get_symbol_by_label(symbol_head, operand+1)) - *ic + 1); /* gets the distance of the label from current IC, as requested  */
            command_value <<= SHIFT_BITS_FROM_A_R_E_CODING;
            code_are(&command_value, 'A'); /* code 'A' to this addressing method */
            if (get_symbol_external(get_symbol_by_label(symbol_head, operand+1)) == TRUE) {
                *error_in_file = TRUE;
                fprintf(stdout, "Line %d in file %s: Using Adressing method 2 on an external label is incorrect.\n", 
                corrent_line, file_name); /* using relative addressing with extern is defined as an error */
            } else {
                edit_instruction_command(get_instruction_by_memory(instruction_head, *ic), command_value); /* add the new command value (machine code) */
            }
        }
    }
    if (operand_type != REGISTER_ADDRESSING) { /* addressing of type 3 is being ignored since was coded in the first pass */
        (*ic)++;
    }
}