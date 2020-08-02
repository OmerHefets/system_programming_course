#include "assembler.h"

void create_files(InstructionPtr head_instruction, DataPtr head_data, int ic, int dc)
{
    create_object_file(head_instruction, head_data, ic, dc);
    /*
    create_entry_file();
    create_extern_file();
    */
}

void create_object_file(InstructionPtr head_instruction, DataPtr head_data, int ic, int dc)
{
    FILE *ofp;
    char buffer[MAX_LINE];
    /* insert real filename */
    if ((ofp = fopen("output.txt", "w")) == NULL) {
            fprintf(stdout, "can\'t open a file for reading.\n");
    }
    sprintf(buffer, "\t%d\t%d\n", ic-100, dc);
    fputs(buffer, ofp);
    print_instructions_to_file(ofp, head_instruction);
    print_data_to_file(ofp, head_data);
    fclose(ofp);
}