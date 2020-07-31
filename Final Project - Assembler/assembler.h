#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define MAX_LABEL_SIZE 33 /* max size of label is 31, and added ':' and '/0' at the end of the label */
#define MAX_LINE 80
#define LABEL 1
#define COMMAND 2
#define EMPTY_OR_COMMENT 0
#define UNDEFINED 0
#define CODE 0
#define DATA 1

extern char *registers[];
extern char *opcodes[];
extern char *data_operations[];

typedef struct symbol_table *SymbolPtr;
typedef struct symbol_table {
    char label[MAX_LABEL_SIZE];
    unsigned long int memory; /* memory defined as 2^21 cells */
    unsigned char code_or_data; 
    unsigned char external;
    unsigned char entry;
    SymbolPtr next;
} SymbolTable;


typedef struct extern_file *ExternPtr;
typedef struct extern_file {
    char label[MAX_LABEL_SIZE];
    unsigned long int memory;
    ExternPtr next;
} ExternFile;


typedef struct instruction_file *InstructionPtr;
typedef struct instruction_file {
    unsigned long int memory;
    unsigned long int command; /* word size is 24 bits */
    InstructionPtr next;
} InstructionFile;


typedef struct data_file *DataPtr;
typedef struct data_file {
    unsigned long int memory;
    unsigned long int data;
    DataPtr next;
} DataFile;


SymbolPtr symbol_alloc(void);
ExternPtr extern_alloc(void);
InstructionPtr instruction_alloc(void);
DataPtr data_alloc(void);

void free_symbol_list(SymbolPtr head);
void free_extern_list(ExternPtr head);
void free_instruction_list(InstructionPtr head);
void free_data_list(DataPtr head);

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


/* parsing error checking */
int check_correct_label(char *str);
int check_command_exists(char *str);

/* parsing */
int analyze_first_buffer(char *token, char *label, int *error_in_file);
void parse_line_first_pass(char *line, int *error_in_file, SymbolPtr *symbol_head, int *dc, int *ic);
void parse_string_or_data_line(char *label, char *command, int label_flag, SymbolPtr *symbol_head, int* error_in_file, 
int *dc, char *line, int index_of_arguments);
void parse_data_line(char *line, int index_of_arguments, SymbolPtr *symbol_head, int* error_in_file, int *dc);