/**
 * Header file for the assembler. this header includes all defined values, all declarations, and definitions of data structures, seperated by modules.
 * All function declaration has documentation, and specific important definitions has as well.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define EXIT_WITH_SUCCESS 0 /* usage for main function - return 0 if the program was successful*/
#define TRUE 1
#define FALSE 0
#define MAX_LABEL_SIZE 33 /* max size of label is 31, and added ':' and '/0' at the end of the label */
#define MAX_LINE 81 /* maxline is 80 + 1 char for a newline */
#define MAX_FILE_NAME 30 /* 30 chars for the file name */
#define MAX_FILE_NAME_WITH_SUFFIX 35 /* 30 chars for the file name and 5 chars for the suffix + '\0' */

/* definitons of specific values for a more clear code (instead of using TRUE and FALSE */
#define LABEL 1
#define COMMAND 2
#define EMPTY_OR_COMMENT 0
#define UNDEFINED 0
#define CODE 0
#define DATA 1
#define NONE -1
#define UNLIMITED -1
#define SRC 1
#define DEST 0
#define ENTRY 1
#define EXTERN 0
#define FIRST_OPERAND 0
#define SECOND_OPERAND 1
#define FIRST_LINE 1
#define NO_ARGUMENTS 0
#define ONLY_COMMAND_NO_FILES 1

/* reset the binary memory and data values */
#define RESET_COMMAND_VALUE 0
#define RESET_DATA_VALUE 0


/* defining possible suffixes for the function which adds a suffix to the filename */
#define FILENAME_SUFFIX 0
#define OBJECT_SUFFIX 1
#define ENTRY_SUFFIX 2
#define EXTERN_SUFFIX 3
#define AS_AND_OB_SUFFIX_LENGTH 3
#define ENT_AND_EXT_SUFFIX_LENGTH 4

/* as defined in the mmn, DC and IC are initialized with the values 0 and 100 accordingly */
#define DATA_MEMORY_START 0
#define INSTRUCTION_MEMORY_START 100

/* all four types of addressing's defined */
#define IMMEDIATE_ADDRESSING 0
#define DIRECT_ADDRESSING 1
#define RELATIVE_ADDRESSING 2
#define REGISTER_ADDRESSING 3

/* definitions for operations creating the binary machine code */
#define SHIFT_BITS_FROM_A_R_E_CODING 3 /* A_R_E codes are the first 3 bits */
#define SHIFT_BITS_TO_FUNCT 3 /* funct bits are the 3-7 bits */
#define SHIFT_BITS_TO_OPCODE 18 /* opcode bits are the 18-23 bits */
#define SHIFT_BITS_TO_SRC 13 /* source register and addressing is the 13-17 bits */
#define SHIFT_BITS_TO_DEST 8 /* destination register and addressing is the 8-12 bits */
#define DIRECT_OPERAND_BITS 8 /* set 4th bit on 5 bits word (for register and addressing) */
#define RELATIVE_OPERAND_BITS 16 /* same as above, set 5th bit on */
#define REGISTER_OPERAND_BITS 24 /* same as above, set 4th and 5th bit on */
#define A_BIT 4 /* third bit in a word, value of 4 */
#define R_BIT 2 /* second bit in a word, value of 2 */
#define E_BIT 1 /* first bit in a word, value of 1 */
#define MASK_24_BITS 0xFFFFFFUL /* sets in unsigned long 24 bits with value 1 */

/* defining sum of components of the assembler */
#define NUM_OF_REGISTERS 8
#define NUM_OF_DATA_OPERATIONS 4
#define NUM_OF_OPCODES 16
#define MAX_POSSIBLE_OPCODES 3

/* using the defined data structures from defined_data_structures.c as global data structures for the program */
extern char *registers[];
extern char *opcodes[];
extern char *data_operations[];
extern int opcodes_opcode[];
extern int opcodes_funct[];
extern int opcodes_first_operand[16][3];
extern int opcodes_second_operand[16][3];
extern int opcodes_number_of_operands[];

/* symbol table definition - as a linked list of structs */
typedef struct symbol_table *SymbolPtr;
typedef struct symbol_table {
    char label[MAX_LABEL_SIZE]; /* label of the symbol */
    unsigned long int memory; /* memory defined as 2^21 cells */
    unsigned char code_or_data; /* is the symbol code, data or defined none */
    unsigned char external; /* is the symbol external */
    unsigned char entry; /* is the symbol entry */
    SymbolPtr next;
} SymbolTable;

/* linked list of occurences of external labels in the file, for the extern file */
typedef struct extern_file *ExternPtr;
typedef struct extern_file {
    char label[MAX_LABEL_SIZE];
    unsigned long int memory; /* defined in the file as decimal number of 7 numbers, max 2^21 as defined */
    ExternPtr next;
} ExternFile;

/* linked list of all instructions in the binary machine code */
typedef struct instruction_file *InstructionPtr;
typedef struct instruction_file {
    unsigned long int memory; /* 7 decimal numbers, defined up to 2^21 */
    unsigned long int command; /* word size is 24 bits */
    InstructionPtr next;
} InstructionFile;

/* linked list of all the data in the binary machine code */
typedef struct data_file *DataPtr;
typedef struct data_file {
    unsigned long int memory; /* 7 decimal numbers, defined up to 2^21 */
    unsigned long int data; /* word size is 24 bits */
    DataPtr next;
} DataFile;


/* declarations of functions in assembler.c */


/* gets all filed passed by the user, adds the ".as" suffix and compiles them one by one */
void compile_multiple_files(int argc, char *argv[]);

/* compile one file by the algorithm provided in mmn14 - two passes with error checking in each pass.
(will not proceed to the second pass if the first one fails with any error) then creates the files and free the memory */
void compile_file(FILE *ifp_first_pass, FILE *ifp_second_pass, char *file_name);

/* apply the first pass algorithm on a file */
void first_pass(FILE *ifp, SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data, int *dc, int *ic, int *errors_in_file, char *file_name);

/* apply the second pass algorithm on a file */
void second_pass(FILE *ifp, SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data, int *ic, int *errors_in_file, char *file_name);

/* free all the linked lists defined dynamically in the program - symbols, externals occurences, instructions and data binary code */
void free_all_data_structures(SymbolPtr *head_symbol, ExternPtr *head_extern, InstructionPtr *head_instruction,
DataPtr *head_data);


/* end of declarations of functions in assembler.c */



SymbolPtr symbol_alloc(void);
ExternPtr extern_alloc(void);
InstructionPtr instruction_alloc(void);
DataPtr data_alloc(void);

void free_symbol_list(SymbolPtr *head);
void free_extern_list(ExternPtr *head);
void free_instruction_list(InstructionPtr *head);
void free_data_list(DataPtr *head);

void add_symbol(SymbolPtr *head_symbol_list, char *label, int label_length, unsigned long int memory,
unsigned char code_or_data, unsigned char external, unsigned char entry);
void add_extern(ExternPtr *head_extern_list, char *label, int label_length, unsigned long int memory);
void add_instruction(InstructionPtr *head_instruction_list, unsigned long int memory, unsigned long int command);
void add_data(DataPtr *head_data_list, unsigned long int memory, unsigned long int data);

SymbolPtr get_symbol_by_label(SymbolPtr head_symbol_list, char *label);
ExternPtr get_extern_by_label(ExternPtr head_extern_list, char *label);
InstructionPtr get_instruction_by_memory(InstructionPtr head_instruction_list, unsigned long int memory);
DataPtr get_data_by_memory(DataPtr head_data_ptr, unsigned long int memory);


char *get_symbol_label(SymbolPtr ptr);
unsigned long int get_symbol_memory(SymbolPtr ptr);
unsigned char get_symbol_code_or_data(SymbolPtr ptr);
unsigned char get_symbol_external(SymbolPtr ptr);
unsigned char get_symbol_entry(SymbolPtr ptr);

char *get_extern_label(ExternPtr ptr);
unsigned long int get_extern_memory(ExternPtr ptr);

unsigned long int get_instruction_memory(InstructionPtr ptr);
unsigned long int get_instruction_command(InstructionPtr ptr);

unsigned long int get_data_memory(DataPtr ptr);
unsigned long int get_data_data(DataPtr ptr);

void edit_symbol_memory(SymbolPtr ptr, unsigned long int new_memory);
void edit_symbol_code_or_data(SymbolPtr ptr, unsigned char new_code_or_data);
void edit_symbol_external(SymbolPtr ptr, unsigned char new_external);
void edit_symbol_entry(SymbolPtr ptr, unsigned char new_entry);

void edit_extern_memory(ExternPtr ptr, unsigned long int new_memory);

void edit_instruction_memory(InstructionPtr ptr, unsigned long int new_memory);
void edit_instruction_command(InstructionPtr ptr, unsigned long int new_command);

void edit_data_memory(DataPtr ptr, unsigned long int new_memory);
void edit_data_data(DataPtr ptr, unsigned long int new_data);

int check_label_duplication_in_symbols(char *label, SymbolPtr head_symbol_list);
void update_data_memory_in_symbol_table(SymbolPtr head_symbol_list, int ic);
void update_data_memory_in_data_table(DataPtr head_data_list, int ic);
void print_instructions_to_file(FILE *ofp, InstructionPtr head_instruction);
void print_data_to_file(FILE *ofp, DataPtr head_data);
int search_entry_or_extern_symbol(SymbolPtr head_symbol, int entry_or_extern);
void print_symbol_list(SymbolPtr head);
void print_extern_list(ExternPtr head);


/* parsing error checking */
int check_correct_label(char *str);
int check_correct_register(char *str);
int check_command_exists(char *str);
int check_number_of_commas(char *s, int requested_amount);
int check_data_arguments(char *line);
int check_data_argument(char *arg);
int check_string_argument(char *line);
int check_extern_argument(char *line);
int check_instruction_arguments(char *line, char *command);
int check_one_operand_in_instruction(char *line, char *command);
int check_two_operands_in_instruction(char *line, char *command);

/* parsing */
int analyze_first_buffer(char *token, char *label, int *error_in_file, int corrent_line, char *file_name);
void parse_line_first_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, ExternPtr *extern_head,
InstructionPtr *instruction_head, DataPtr *data_head, int *dc, int *ic, int corrent_line, char *file_name);
void parse_string_or_data_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head,
DataPtr *data_head, int* error_in_file, int *dc, char *line, int index_of_arguments, int corrent_line, char *file_name);
void parse_data_line(char *line, int index_of_arguments, DataPtr *data_head, int* error_in_file, int *dc, 
int corrent_line, char *file_name);
void parse_string_line(char line[], int index_of_arguments, DataPtr *data_head, int* error_in_file, int *dc, 
int corrent_line, char *file_name);
void parse_entry_or_extern_line(char *command, ExternPtr *extern_head, SymbolPtr *symbol_head, int* error_in_file,
char *line, int index_of_arguments, int corrent_line, char *file_name);
void parse_extern_line(char *line, int index_of_arguments, ExternPtr *extern_head, SymbolPtr *symbol_head,
int *error_in_file, int corrent_line, char *file_name);
void parse_operation_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head, InstructionPtr *instruction_head, 
int* error_in_file, int *ic, char *line, int index_of_arguments, int corrent_line, char *file_name);
int is_legal_filename_length(char *file_name);
int add_suffix_to_file(char *file_name, char *file_name_with_suffix, int suffix);


/* helper functions? */
int get_command_index(char *command);
int get_register_index(char *reg);
int get_operand_type(char *operand);
long get_number_from_operand_adressing_zero(char *operand);
int is_legal_operand_type(int *optional_operands, int operand_type);


/* compiling instructions */
void compile_instruction_line(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head, int *ic);
void compile_instruction_line_zero_operands(char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head, int *ic);
void compile_instruction_line_one_operand(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head,
int *ic);
void compile_instruction_line_two_operands(char *args_line, char *command, SymbolPtr *symbol_head, InstructionPtr *instruction_head,
int *ic);
void compile_operand(char *operand, InstructionPtr *instruction_head, int *ic);
void code_are(unsigned long int *command, char a_r_e);
void code_funct(unsigned long int *command, char *command_name);
void code_opcode(unsigned long int *command, char *command_name);
void code_addressing_and_register(unsigned long int *command, char *operand, int src_or_dest);


/* creating files */
void create_files(SymbolPtr head_symbol, ExternPtr head_extern, InstructionPtr head_instruction,
DataPtr head_data, int ic, int dc, char *file_name);
void create_object_file(InstructionPtr head_instruction, DataPtr head_data, int ic, int dc, char *file_name);
void create_entry_file(SymbolPtr head_symbol, char *file_name);
void create_extern_file(ExternPtr head_extern, SymbolPtr head_symbol, char *file_name);

/* second pass */
void parse_line_second_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, ExternPtr *extern_head,
InstructionPtr *instruction_head, DataPtr *data_head, int *ic, int corrent_line, char *file_name);
int analyze_first_buffer_second_pass(char *token);
void parse_entry_line_second_pass(SymbolPtr head_symbol, int *error_in_file, char *line, int index_of_arguments, 
int corrent_line, char *file_name);
void compile_instruction_line_second_pass(char *args_line, char *command, SymbolPtr symbol_head,
InstructionPtr instruction_head, ExternPtr *extern_head, int *error_in_file, int *ic, int corrent_line, char *file_name);
void instruction_line_one_operand_second_pass(char *args_line, char *command, SymbolPtr symbol_head, InstructionPtr instruction_head,
ExternPtr *extern_head, int *error_in_file ,int *ic, int corrent_line, char *file_name);
void instruction_line_two_operands_second_pass(char *args_line, char *command, SymbolPtr symbol_head, InstructionPtr instruction_head,
ExternPtr *extern_head ,int *error_in_file, int *ic, int corrent_line, char *file_name);
void compile_operand_second_pass(char *operand, InstructionPtr instruction_head, SymbolPtr symbol_head,
ExternPtr *extern_head, int *error_in_file, int *ic, int corrent_line, char *file_name);