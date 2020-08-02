#include "assembler.h"

SymbolPtr symbol_alloc(void)
{
    SymbolPtr ptr = (SymbolPtr) malloc(sizeof(SymbolTable));
    if (ptr == NULL) {
        fprintf(stdout, "Memory allocation for SymbolTable failed.\n");
        exit(0);
    }
    return ptr;
}

ExternPtr extern_alloc(void)
{
    ExternPtr ptr = (ExternPtr) malloc(sizeof(ExternFile));
    if (ptr == NULL) {
        fprintf(stdout, "Memory allocation for ExternFile failed.\n");
        exit(0);
    }
    return ptr;
}

InstructionPtr instruction_alloc(void)
{
    InstructionPtr ptr = (InstructionPtr) malloc(sizeof(InstructionFile));
    if (ptr == NULL) {
        fprintf(stdout, "Memory allocation for InstructionFile failed.\n");
        exit(0);
    }
    return ptr;
}

DataPtr data_alloc(void)
{
    DataPtr ptr = (DataPtr) malloc(sizeof(DataFile));
    if (ptr == NULL) {
        fprintf(stdout, "Memory allocation for DataFile failed.\n");
        exit(0);
    }
    return ptr;
}

void free_symbol_list(SymbolPtr head)
{
    SymbolPtr temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void free_extern_list(ExternPtr head)
{
    ExternPtr temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void free_instruction_list(InstructionPtr head)
{
    InstructionPtr temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void free_data_list(DataPtr head)
{
    DataPtr temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void add_symbol(SymbolPtr *head_symbol_list, char *label, int label_length, unsigned long int memory,
unsigned char code_or_data, unsigned char external, unsigned char entry)
{
    SymbolPtr symbol_ptr = symbol_alloc();
    SymbolPtr temp = *head_symbol_list;
    symbol_ptr->memory = memory;
    symbol_ptr->code_or_data = code_or_data;
    symbol_ptr->external = external;
    symbol_ptr->entry = entry;
    symbol_ptr->next = NULL;
    strncat(symbol_ptr->label, label, label_length);

    if (temp == NULL) {
        *head_symbol_list = symbol_ptr;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = symbol_ptr;
    }
}

void add_extern(ExternPtr *head_extern_list, char *label, int label_length, unsigned long int memory)
{
    ExternPtr extern_ptr = extern_alloc();
    ExternPtr temp = *head_extern_list;
    extern_ptr->memory = memory;
    extern_ptr->next = NULL;
    strncat(extern_ptr->label, label, label_length);

    if (temp == NULL) {
        *head_extern_list = extern_ptr;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = extern_ptr;
    }
}

void add_instruction(InstructionPtr *head_instruction_list, unsigned long int memory, unsigned long int command)
{
    InstructionPtr instruction_ptr = instruction_alloc();
    InstructionPtr temp = *head_instruction_list;
    instruction_ptr->memory = memory;
    instruction_ptr->command = command;
    instruction_ptr->next = NULL;

    if (temp == NULL) {
        *head_instruction_list = instruction_ptr;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = instruction_ptr;
    }
}

void add_data(DataPtr *head_data_list, unsigned long int memory, unsigned long int data)
{
    DataPtr data_ptr = data_alloc();
    DataPtr temp = *head_data_list;
    data_ptr->memory = memory;
    data_ptr->data = data;
    data_ptr->next = NULL;

    if (temp == NULL) {
        *head_data_list = data_ptr;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = data_ptr;
    }
}

SymbolPtr get_symbol_by_label(SymbolPtr head_symbol_list, char *label)
{
    SymbolPtr temp = head_symbol_list;
    while (temp != NULL) {
        if (!strcmp(temp->label, label)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

ExternPtr get_extern_by_label(ExternPtr head_extern_list, char *label)
{
    ExternPtr temp = head_extern_list;
    while (temp != NULL) {
        if (!strcmp(temp->label, label)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

InstructionPtr get_instruction_by_memory(InstructionPtr head_instruction_list, unsigned long int memory)
{
    InstructionPtr temp = head_instruction_list;
    while (temp != NULL) {
        if (temp->memory == memory) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

DataPtr get_data_by_memory(DataPtr head_data_ptr, unsigned long int memory)
{
    DataPtr temp = head_data_ptr;
    while (temp != NULL) {
        if (temp->memory == memory) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

char *get_symbol_label(SymbolPtr ptr)
{
    return ptr->label;
}

unsigned long int get_symbol_memory(SymbolPtr ptr)
{
    return ptr->memory;
}

unsigned char get_symbol_code_or_data(SymbolPtr ptr)
{
    return ptr->code_or_data;
}

unsigned char get_symbol_external(SymbolPtr ptr)
{
    return ptr->external;
}

unsigned char get_symbol_entry(SymbolPtr ptr)
{
    return ptr->entry;
}

char *get_extern_label(ExternPtr ptr)
{
    return ptr->label;
}

unsigned long int get_extern_memory(ExternPtr ptr)
{
    return ptr->memory;
}

unsigned long int get_instruction_memory(InstructionPtr ptr)
{
    return ptr->memory;
}

unsigned long int get_instruction_command(InstructionPtr ptr)
{
    return ptr->command;
}

unsigned long int get_data_memory(DataPtr ptr)
{
    return ptr->memory;
}

unsigned long int get_data_data(DataPtr ptr)
{
    return ptr->data;
}

void edit_symbol_memory(SymbolPtr ptr, unsigned long int new_memory)
{
    ptr->memory = new_memory;
}

void edit_symbol_code_or_data(SymbolPtr ptr, unsigned char new_code_or_data)
{
    ptr->code_or_data = new_code_or_data;
}

void edit_symbol_external(SymbolPtr ptr, unsigned char new_external)
{
    ptr->external = new_external;
}

void edit_symbol_entry(SymbolPtr ptr, unsigned char new_entry)
{
    ptr->entry = new_entry;
}

void edit_extern_memory(ExternPtr ptr, unsigned long int new_memory)
{
    ptr->memory = new_memory;
}

void edit_instruction_memory(InstructionPtr ptr, unsigned long int new_memory)
{
    ptr->memory = new_memory;
}

void edit_instruction_command(InstructionPtr ptr, unsigned long int new_command)
{
    ptr->command = new_command;
}

void edit_data_memory(DataPtr ptr, unsigned long int new_memory)
{
    ptr->memory = new_memory;
}

void edit_data_data(DataPtr ptr, unsigned long int new_data)
{
    ptr->data = new_data;
}

int check_label_duplication_in_symbols(char *label, SymbolPtr head_symbol_list)
{
    int duplication_exists = FALSE;
    SymbolPtr temp = head_symbol_list;
    while (temp != NULL) {
        if (!strcmp(temp->label, label)) {
            duplication_exists = TRUE;
        }
        temp = temp->next;
    }
    return duplication_exists;
}

void update_data_memory_in_symbol_table(SymbolPtr head_symbol_list, int ic)
{
    SymbolPtr temp = head_symbol_list;
    while (temp != NULL) {
        if (temp->code_or_data == DATA) {
            temp->memory += ic;
        }
        temp = temp->next;
    }
}

void update_data_memory_in_data_table(DataPtr head_data_list, int ic)
{
    DataPtr temp = head_data_list;
    while (temp != NULL) {
        temp->memory += ic;
        temp = temp->next;
    }
}