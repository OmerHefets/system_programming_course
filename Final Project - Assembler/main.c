#include "assembler.h"
/*
void test_symbol_data_structure()
{
    SymbolPtr temp, symbol_head = NULL;
    char label[] = "HELLO";
    char label2[] = "LELLO";

    add_symbol(label, 5, &symbol_head);
    add_symbol(label2, 5, &symbol_head);
    if (symbol_head == NULL) {
        printf("shit\n");
    }
    printf("%s\n", get_symbol_label(symbol_head->next));
    printf("%d\n", get_symbol_entry(symbol_head));
    edit_symbol_entry(symbol_head, 1);
    printf("%d\n", get_symbol_entry(symbol_head));
    printf("duplication: %d\n", check_label_duplication_in_symbols("LELLO", symbol_head));
    temp = get_symbol_by_label(symbol_head, "HELLO");
    printf("%d\n", get_symbol_entry(temp));
    free_symbol_list(symbol_head);
}

void test_check_correct_label()
{
    char label1[] = "               ta: h fjksdh fjksdfh kjdfh";
    char label2[] = "2HELLO: fjdklsjf";
    char label3[] = "HELLO FJDKL FJSDK";
    char label4[] = "FSDJKLJFSKLFJSDKLFJSLDKFJSLKFJSLDKFJSKLFJSDKLFJSDLKFJSLKF:";
    char label5[] = "   MAIN45s: ";
    char *s = " \t";
    char *token1, *token2, *token3, *token4, *token5;
    token1 = strtok(label1, s);
    token2 = strtok(label2, s);
    token3 = strtok(label3, s);
    token4 = strtok(label4, s);
    token5 = strtok(label5, s);
    if (check_correct_label(token1)) {
            printf("%s is a correct label\n", token1);
    } else {
            printf("%s isnt a correct label\n", token1);
    }
    if (check_correct_label(token2)) {
            printf("%s is a correct label\n", token2);
    } else {
            printf("%s isnt a correct label\n", token2);
    }
    if (check_correct_label(token3)) {
            printf("%s is a correct label\n", token3);
    } else {
            printf("%s isnt a correct label\n", token3);
    }
    if (check_correct_label(token4)) {
            printf("%s is a correct label\n", token4);
    } else {
            printf("%s isnt a correct label\n", token4);
    }
    if (check_correct_label(token5)) {
            printf("%s is a correct label\n", token5);
    } else {
            printf("%s isnt a correct label\n", token5);
    }
}

void test_analyze_first_buffer()
{
    char label[MAX_LABEL_SIZE];
    int *a, result,b=0;
    char line1[] = "HELLO:";
    char line2[] = "2ELLO:";
    char line3[] = ".data";
    char line4[] = "mov:";
    char line5[] = "r8:";
    char line6[] = "r9:";
    a = &b;
    result = analyze_first_buffer(line1, label, a);
    printf("%d\n", result);
    result = analyze_first_buffer(line2, label, a);
    printf("%d\n", result);
    result = analyze_first_buffer(line3, label, a);
    printf("%d\n", result);
    result = analyze_first_buffer(line4, label, a);
    printf("%d\n", result);
    result = analyze_first_buffer(line5, label, a);
    printf("%d\n", result);
    result = analyze_first_buffer(line6, label, a);
    printf("%d\n", result);
}
*/
void test_parse_line_first_pass()
{
    SymbolPtr head_symbol = NULL;
    ExternPtr head_extern = NULL;
    InstructionPtr head_instruction = NULL;
    DataPtr head_data = NULL;
    int *dc, *ic;
    char line[] = " hello: .data  +5, 4,-8 , -4,8 ,4,4, 9, 10  ";
    int *error, dcf=0, icf=0, is_error=0;
    error = &is_error;
    dc = &dcf;
    ic = &icf;
    parse_line_first_pass(line, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic);
    printf("%s\n", get_symbol_label(head_symbol));
    printf("%d\n", *dc);
    printf("%lu\n", get_data_memory(head_data->next->next->next));
    free_symbol_list(head_symbol);
    free_extern_list(head_extern);
    free_instruction_list(head_instruction);
    free_data_list(head_data);
}

void test_check_number_of_commas()
{
        char *line = "  -1 , +5, 4,8 , 4,8 ,4,4, 9, 10   ";
        if (check_number_of_commas(line, UNLIMITED)) {
                printf("the string: %s is valid\n", line);
        } else {
                printf("the string: %s is invalid\n", line);
        }
}

void test_check_data_arguments()
{
        char line[] = "  -1 , +5, 4,8   ";
        char line_copy[MAX_LINE] = "";
        strncat(line_copy, line, strlen(line));
        if (check_data_arguments(line_copy)) {
                printf("the string: %s is valid\n", line);
        } else {
                printf("the string: %s is invalid\n", line);
        }    
}

int main()
{
    test_parse_line_first_pass();
    return 0;
}