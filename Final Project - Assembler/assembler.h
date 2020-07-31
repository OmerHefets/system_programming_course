#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LABEL_SIZE 33 /* max size of label is 31, and added ':' and '/0' at the end of the label */

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

SymbolPtr add_symbol(char *label, int label_length, SymbolPtr head_symbol_list);
ExternPtr add_extern(char *label, int label_length, ExternPtr head_extern_list);
InstructionPtr add_instruction(InstructionPtr head_instruction_list);
DataPtr add_data(DataPtr head_data_list);

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