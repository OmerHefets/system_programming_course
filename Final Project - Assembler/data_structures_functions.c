/**
 * This module has all functions that work with the linked lists in the program: symbol list, instruction list, data list, and extern list.
 * The functions exist and are defined here for better seperation between data structures and code
 */

#include "assembler.h"

/* allocate a symbol struct */
SymbolPtr symbol_alloc(void)
{
    SymbolPtr ptr = (SymbolPtr) malloc(sizeof(SymbolTable));
    if (ptr == NULL) {
        fprintf(stdout, "Memory allocation for SymbolTable failed.\n");
        exit(0);
    }
    return ptr;
}

/* allocate an extern struct */
ExternPtr extern_alloc(void)
{
    ExternPtr ptr = (ExternPtr) malloc(sizeof(ExternFile));
    if (ptr == NULL) {
        fprintf(stdout, "Memory allocation for ExternFile failed.\n");
        exit(0);
    }
    return ptr;
}

/* allocate an instruction struct */
InstructionPtr instruction_alloc(void)
{
    InstructionPtr ptr = (InstructionPtr) malloc(sizeof(InstructionFile));
    if (ptr == NULL) {
        fprintf(stdout, "Memory allocation for InstructionFile failed.\n");
        exit(0);
    }
    return ptr;
}

/* allocate a data struct */
DataPtr data_alloc(void)
{
    DataPtr ptr = (DataPtr) malloc(sizeof(DataFile));
    if (ptr == NULL) {
        fprintf(stdout, "Memory allocation for DataFile failed.\n");
        exit(0);
    }
    return ptr;
}

/* free the symbol list */
void free_symbol_list(SymbolPtr *head)
{
    SymbolPtr temp;

    while (*head != NULL) { /* free all structs one by one */
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

/* free the extern list */
void free_extern_list(ExternPtr *head)
{
    ExternPtr temp;

    while (*head != NULL) { /* free all structs one by one */
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

/* free the instruction list */
void free_instruction_list(InstructionPtr *head)
{
    InstructionPtr temp;

    while (*head != NULL) { /* free all structs one by one */
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

/* free the data list */
void free_data_list(DataPtr *head)
{
    DataPtr temp;

    while (*head != NULL) { /* free all structs one by one */
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

/* add a symbol to the symbol list (to the linked list) */
void add_symbol(SymbolPtr *head_symbol_list, char *label, int label_length, unsigned long int memory,
unsigned char code_or_data, unsigned char external, unsigned char entry)
{
    SymbolPtr symbol_ptr = symbol_alloc(); /* allocate an empty symbol struct */
    SymbolPtr temp = *head_symbol_list;
    /* set all values of the struct */
    symbol_ptr->memory = memory;
    symbol_ptr->code_or_data = code_or_data;
    symbol_ptr->external = external;
    symbol_ptr->entry = entry;
    symbol_ptr->next = NULL;
    memset(symbol_ptr->label, UNDEFINED, strlen(symbol_ptr->label)); /* clear the label before copying to it */
    strncpy(symbol_ptr->label, label, label_length);

    /* append to the end of the list */
    if (temp == NULL) {
        *head_symbol_list = symbol_ptr;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = symbol_ptr;
    }
}

/* add an extern struct (with extern position in memory for the extern file */
void add_extern(ExternPtr *head_extern_list, char *label, int label_length, unsigned long int memory)
{
    ExternPtr extern_ptr = extern_alloc(); /* allocate an empty symbol struct */
    ExternPtr temp = *head_extern_list;
    /* set all values of the struct */
    extern_ptr->memory = memory;
    extern_ptr->next = NULL;
    memset(extern_ptr->label, UNDEFINED, strlen(extern_ptr->label));
    strncpy(extern_ptr->label, label, label_length);

    /* append to the end of the list */
    if (temp == NULL) {
        *head_extern_list = extern_ptr;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = extern_ptr;
    }
}

/* add an instruction to the linked list (with the machine code and memory) */
void add_instruction(InstructionPtr *head_instruction_list, unsigned long int memory, unsigned long int command)
{
    InstructionPtr instruction_ptr = instruction_alloc(); /* allocate instruction */
    InstructionPtr temp = *head_instruction_list;
    /* set values */
    instruction_ptr->memory = memory;
    instruction_ptr->command = command;
    instruction_ptr->next = NULL;

    /* append to the end of the list */
    if (temp == NULL) {
        *head_instruction_list = instruction_ptr;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = instruction_ptr;
    }
}

/* add a data coded in the machine code to the data linked list */
void add_data(DataPtr *head_data_list, unsigned long int memory, unsigned long int data)
{
    DataPtr data_ptr = data_alloc(); /* allocate data */
    DataPtr temp = *head_data_list;
    /* set values */ 
    data_ptr->memory = memory;
    data_ptr->data = data;
    data_ptr->next = NULL;

    /* append to the end of the list */
    if (temp == NULL) {
        *head_data_list = data_ptr;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = data_ptr;
    }
}

/* get symbol ptr by specific label */
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

/* get extern ptr by label */
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

/* get instruction ptr by memory */
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

/* get data ptr by memory */
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

/* get the label of a symbol */
char *get_symbol_label(SymbolPtr ptr)
{
    return ptr->label;
}

/* get the memory of a symbol */
unsigned long int get_symbol_memory(SymbolPtr ptr)
{
    return ptr->memory;
}

/* get if the symbol is code or data */
unsigned char get_symbol_code_or_data(SymbolPtr ptr)
{
    return ptr->code_or_data;
}

/* get if a symbol is an extern */
unsigned char get_symbol_external(SymbolPtr ptr)
{
    return ptr->external;
}

/* get if a symbol is an entry */
unsigned char get_symbol_entry(SymbolPtr ptr)
{
    return ptr->entry;
}

/* get the label of an extern */
char *get_extern_label(ExternPtr ptr)
{
    return ptr->label;
}

/* get the memory of an extern */
unsigned long int get_extern_memory(ExternPtr ptr)
{
    return ptr->memory;
}

/* get the memory of an instruction */
unsigned long int get_instruction_memory(InstructionPtr ptr)
{
    return ptr->memory;
}

/* get the command (machine code) of an instruction */
unsigned long int get_instruction_command(InstructionPtr ptr)
{
    return ptr->command;
}

/* get the memory of data struct */
unsigned long int get_data_memory(DataPtr ptr)
{
    return ptr->memory;
}

/* get the data (machine code) of a data struct */
unsigned long int get_data_data(DataPtr ptr)
{
    return ptr->data;
}

/* edit the memory of a symbol by ptr */
void edit_symbol_memory(SymbolPtr ptr, unsigned long int new_memory)
{
    ptr->memory = new_memory;
}

/* edit the value of code or data of a symbol by ptr */
void edit_symbol_code_or_data(SymbolPtr ptr, unsigned char new_code_or_data)
{
    ptr->code_or_data = new_code_or_data;
}

/* edit the extern value of a symbol */
void edit_symbol_external(SymbolPtr ptr, unsigned char new_external)
{
    ptr->external = new_external;
}

/* edit the entry value of a symbol */ 
void edit_symbol_entry(SymbolPtr ptr, unsigned char new_entry)
{
    ptr->entry = new_entry;
}

/* edit the memory of an extern by ptr */
void edit_extern_memory(ExternPtr ptr, unsigned long int new_memory)
{
    ptr->memory = new_memory;
}

/* edit the memory of an instruction by ptr */
void edit_instruction_memory(InstructionPtr ptr, unsigned long int new_memory)
{
    ptr->memory = new_memory;
}

/* edit the command (machine code) of an instruction */
void edit_instruction_command(InstructionPtr ptr, unsigned long int new_command)
{
    ptr->command = new_command;
}

/* edit the memory of a data struct */
void edit_data_memory(DataPtr ptr, unsigned long int new_memory)
{
    ptr->memory = new_memory;
}

/* edit the data (machine code) of a data struct */
void edit_data_data(DataPtr ptr, unsigned long int new_data)
{
    ptr->data = new_data;
}

/* check if a label already exists in the symbol table */
int check_label_duplication_in_symbols(char *label, SymbolPtr head_symbol_list)
{
    int duplication_exists = FALSE;
    SymbolPtr temp = head_symbol_list;
    while (temp != NULL) { /* iterate all structs in the symbols linked list and search for a match in label names */
        if (!strcmp(temp->label, label)) { 
            duplication_exists = TRUE;
        }
        temp = temp->next;
    }
    return duplication_exists;
}

/* update the data memory in the symbol table (done at the end of the first pass) */
void update_data_memory_in_symbol_table(SymbolPtr head_symbol_list, int ic)
{
    SymbolPtr temp = head_symbol_list;
    while (temp != NULL) {
        if (temp->code_or_data == DATA) {
            temp->memory += ic; /* update with the value of IC after adding all instructions */
        }
        temp = temp->next;
    }
}

/* update the data memory in the data table (at the end of the first pass) */
void update_data_memory_in_data_table(DataPtr head_data_list, int ic)
{
    DataPtr temp = head_data_list;
    while (temp != NULL) {
        temp->memory += ic; /* increase the starting memory of the data by the end of the instructions */
        temp = temp->next;
    }
}

/* print all instructions from a linked list to a file */
void print_instructions_to_file(FILE *ofp, InstructionPtr head_instruction)
{
    char buffer[MAX_LINE];
    InstructionPtr temp = head_instruction;
    while(temp != NULL) {
        /* print memory as 7 decimal digits. print command in hexa, and only its 24 first bits (so its masked with the 24 bit mask) */
        sprintf(buffer, "%07lu %06lx\n", temp->memory, (temp->command & MASK_24_BITS));
        fputs(buffer, ofp);
        temp = temp->next; /* iterate all instructions */
    }
}

/* print all data from the linked list to a file */
void print_data_to_file(FILE *ofp, DataPtr head_data)
{
    char buffer[MAX_LINE];
    DataPtr temp = head_data;
    while(temp != NULL) {
        /* print memory as 7 decimal digits. print command in hexa, and only its 24 first bits (so its masked with the 24 bit mask) */
        sprintf(buffer, "%07lu %06lx\n", temp->memory, (temp->data & MASK_24_BITS));
        fputs(buffer, ofp);
        temp = temp->next; /* iterate all data */
    }
}

/* search if an entry or if an extern symbol exists in the symbol list - choose between EXTERN and ENTRY */
int search_entry_or_extern_symbol(SymbolPtr head_symbol, int entry_or_extern)
{
    SymbolPtr temp = head_symbol;
    while (temp != NULL) {
        if (entry_or_extern == ENTRY) {
            if (temp->entry == TRUE) {
                return TRUE;
            }
        } else { /* search for extern and not for entry */
            if (temp->external == TRUE) {
                return TRUE;
            }
        }
        temp = temp->next;
    }
    return FALSE;
}

/* helper function that prints most important values of all symbols in the symbol list */
void print_symbol_list(SymbolPtr head)
{
    SymbolPtr temp = head;
    while (temp != NULL) {
        printf("name of label is: %s\n", temp->label);
        printf("memory value is: %lu\n", temp->memory);
        printf("code or data is: %d\n", temp->code_or_data);
        printf("external is: %d\n", temp->external);
        printf("entry is: %d\n", temp->entry);
        temp = temp->next;
    }
}

/* helper function that prints most important values of all extern appearances */
void print_extern_list(ExternPtr head)
{
    ExternPtr temp = head;
    while (temp != NULL) {
        printf("name of label is: %s\n", temp->label);
        printf("length of label is: %lu\n", strlen(temp->label));
        temp = temp->next;
    }
}