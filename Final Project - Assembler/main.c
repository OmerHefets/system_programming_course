#include "assembler.h"

void test_symbol_data_structure()
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

void test_parse_line_first_pass()
{
    SymbolPtr ptr = NULL;
    char line[] = "         k  ";
    int *error, a=0;
    error = &a;
    parse_line_first_pass(line, error, ptr);

}

int main()
{
    test_parse_line_first_pass();
    return 0;
}