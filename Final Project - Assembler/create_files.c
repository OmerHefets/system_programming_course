#include "assembler.h"

void create_files(SymbolPtr head_symbol, ExternPtr head_extern, InstructionPtr head_instruction,
DataPtr head_data, int ic, int dc, char *file_name)
{
    create_entry_file(head_symbol, file_name);
    create_object_file(head_instruction, head_data, ic, dc, file_name);
    create_extern_file(head_extern, head_symbol, file_name);
}

void create_entry_file(SymbolPtr head_symbol, char *file_name)
{
    FILE *ofp;
    SymbolPtr temp = head_symbol;
    char buffer[MAX_LINE], file_name_with_suffix[MAX_FILE_NAME_WITH_SUFFIX] = "";
    add_suffix_to_file(file_name, file_name_with_suffix, ENTRY_OUTPUT);
    if (search_entry_or_extern_symbol(head_symbol, ENTRY)) {
        if ((ofp = fopen(file_name_with_suffix, "w")) == NULL) {
            fprintf(stdout, "can\'t open a file for reading.\n");
        } else {
            while (temp != NULL) {
                if (temp->entry == TRUE) {
                    sprintf(buffer, "%s %07lu\n", temp->label, temp->memory);
                    fputs(buffer, ofp);
                }
                temp = temp->next;
            }
            fclose(ofp);
        }
    }
}

void create_extern_file(ExternPtr head_extern, SymbolPtr head_symbol, char *file_name)
{
    FILE *ofp;
    ExternPtr temp = head_extern;
    char buffer[MAX_LINE], file_name_with_suffix[MAX_FILE_NAME_WITH_SUFFIX] = "";
    add_suffix_to_file(file_name, file_name_with_suffix, EXTERN_OUTPUT);
    /* as requested, we create a file */
    if (search_entry_or_extern_symbol(head_symbol, EXTERN)) {
        if ((ofp = fopen(file_name_with_suffix, "w")) == NULL) {
            fprintf(stdout, "can\'t open a file for reading.\n");
        } else {
            while (temp != NULL) {
                sprintf(buffer, "%s %07lu\n", temp->label, temp->memory);
                fputs(buffer, ofp);
                temp = temp->next;
                }
            fclose(ofp);
        }
    }
}

void create_object_file(InstructionPtr head_instruction, DataPtr head_data, int ic, int dc, char *file_name)
{
    FILE *ofp;
    char buffer[MAX_LINE], file_name_with_suffix[MAX_FILE_NAME_WITH_SUFFIX] = "";
    add_suffix_to_file(file_name, file_name_with_suffix, OBJECT_OUTPUT);
    if ((ofp = fopen(file_name_with_suffix, "w")) == NULL) {
            fprintf(stdout, "can\'t open a file for reading.\n");
    } else {
        sprintf(buffer, "\t%d\t%d\n", ic-100, dc);
        fputs(buffer, ofp);
        print_instructions_to_file(ofp, head_instruction);
        print_data_to_file(ofp, head_data);
        fclose(ofp);
    }
}