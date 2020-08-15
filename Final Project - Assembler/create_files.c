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
    char buffer[MAX_LINE] = "", file_name_with_suffix[MAX_FILE_NAME_WITH_SUFFIX] = "";
    add_suffix_to_file(file_name, file_name_with_suffix, ENTRY_SUFFIX);
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
    char buffer[MAX_LINE] = "", file_name_with_suffix[MAX_FILE_NAME_WITH_SUFFIX] = "";
    add_suffix_to_file(file_name, file_name_with_suffix, EXTERN_SUFFIX);
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
    char buffer[MAX_LINE] = "", file_name_with_suffix[MAX_FILE_NAME_WITH_SUFFIX] = "";
    add_suffix_to_file(file_name, file_name_with_suffix, OBJECT_SUFFIX);
    if ((ofp = fopen(file_name_with_suffix, "w")) == NULL) {
            fprintf(stdout, "can\'t open a file for reading.\n");
    } else {
        sprintf(buffer, "\t%d\t%d\n", ic-INSTRUCTION_MEMORY_START, dc);
        fputs(buffer, ofp);
        print_instructions_to_file(ofp, head_instruction);
        print_data_to_file(ofp, head_data);
        fclose(ofp);
    }
}

int add_suffix_to_file(char *file_name, char *file_name_with_suffix, int suffix)
{
    if(is_legal_filename_length(file_name)) {
        strncpy(file_name_with_suffix, file_name, strlen(file_name));
        if (suffix == FILENAME_SUFFIX) {
            strncat(file_name_with_suffix, ".as", AS_AND_OB_SUFFIX_LENGTH);
        } else if (suffix == OBJECT_SUFFIX) {
            strncat(file_name_with_suffix, ".ob", AS_AND_OB_SUFFIX_LENGTH);
        } else if (suffix == ENTRY_SUFFIX) {
            strncat(file_name_with_suffix, ".ent", ENT_AND_EXT_SUFFIX_LENGTH);
        } else if (suffix == EXTERN_SUFFIX) {
            strncat(file_name_with_suffix, ".ext", ENT_AND_EXT_SUFFIX_LENGTH);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}