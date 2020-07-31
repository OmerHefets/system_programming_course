#include "assembler.h"

int main()
{
    SymbolPtr symbol_head = NULL;
    char label[] = "HELLO";
    char label2[] = "LELLO";

    symbol_head = add_symbol(label, 5, symbol_head);
    symbol_head = add_symbol(label2, 5, symbol_head);
    printf("%s\n", get_symbol_label(symbol_head->next));
    printf("%d\n", get_symbol_entry(symbol_head));
    edit_symbol_entry(symbol_head, 1);
    printf("%d\n", get_symbol_entry(symbol_head));
    free_symbol_list(symbol_head);
    return 0;
}