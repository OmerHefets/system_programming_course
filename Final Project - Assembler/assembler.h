#define MAX_LABEL_SIZE 33 /* max size of label is 31, and added ':' and '/0' at the end of the label */

typedef struct symbol_table *SymbolPtr;
typedef struct symbol_table {
    char label[MAX_LABEL_SIZE];
    unsigned long int memory :21; /* memory defined as 2^21 cells */
    unsigned int code_or_data :2; 
    unsigned int extern_or_entry :2;
    SymbolPtr next;
} SymbolTable;


typedef struct extern_file *ExternPtr;
typedef struct extern_file {
    char label[MAX_LABEL_SIZE];
    unsigned long int memory :21;
    ExternPtr next;
} ExternFile;


typedef struct instruction_file *InstructionPtr;
typedef struct instruction_file {
    unsigned long int memory :21;
    unsigned long int command :24; /* word size is 24 bits */
    InstructionPtr next;
} InstructionFile;


typedef struct data_file *DataPtr;
typedef struct data_file {
    unsigned long int memory: 21;
    unsigned long int data: 24;
    DataPtr next;
} DataFile;
