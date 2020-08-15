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
void test_parse_line_first_pass_instructions()
{
    SymbolPtr head_symbol = NULL;
    ExternPtr head_extern = NULL;
    InstructionPtr head_instruction = NULL;
    DataPtr head_data = NULL;
    int *dc, *ic;
    char line[] = " MAIN:   add  r3,LIST   ";
    char line2[] = " HELLO:   add  r3   ";
    char line3[] = "    ;add  #+10,r3     ";
    char line4[] = "  add  r3,#593    ";
    char line5[] = " .data 10,30,-20, -19, 50  ";
    char line6[] = " lel2:   bne  &a19    ";
    char line7[] = " lel3:   rts     ";
    char line8[] = " LE7L: .string \"abc\"  ";
    int *error, dcf=0, icf=100, is_error=0, corrent_line = 1;
    error = &is_error;
    dc = &dcf;
    ic = &icf;
    parse_line_first_pass(line, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    parse_line_first_pass(line2, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    parse_line_first_pass(line3, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    parse_line_first_pass(line4, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    parse_line_first_pass(line5, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    parse_line_first_pass(line6, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    parse_line_first_pass(line7, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    parse_line_first_pass(line8, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    printf("%s\n", get_symbol_label(head_symbol->next));
    printf("ic: %d\n", *ic);
    printf("dc: %d\n", *dc);
    printf("%lu\n", get_data_data(get_data_by_memory(head_data, 4)));
    free_symbol_list(&head_symbol);
    free_extern_list(&head_extern);
    free_instruction_list(&head_instruction);
    free_data_list(&head_data);
}

void test_parse_line_first_pass()
{
    SymbolPtr head_symbol = NULL;
    ExternPtr head_extern = NULL;
    InstructionPtr head_instruction = NULL;
    DataPtr head_data = NULL;
    int *dc, *ic, corrent_line = 1;
    char line[] = " MAIN:   add  r3,LIST   ";
    int *error, dcf=0, icf=0, is_error=0;
    error = &is_error;
    dc = &dcf;
    ic = &icf;
    parse_line_first_pass(line, error, &head_symbol, &head_extern, &head_instruction, &head_data, dc, ic, corrent_line);
    printf("%s\n", get_symbol_label(head_symbol));
    printf("%d\n", *dc);
    /*printf("%lu\n", get_data_data(head_data->next->next));*/
    free_symbol_list(&head_symbol);
    free_extern_list(&head_extern);
    free_instruction_list(&head_instruction);
    free_data_list(&head_data);
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

void test_get_command_index()
{
        char *comm = "mov";
        char *comm2 = "rts";
        char *comm3 = "stop";
        printf("%d\n", get_command_index(comm));
        printf("%d\n", get_command_index(comm2));
        printf("%d\n", get_command_index(comm3));
}

void test_get_operand_type()
{
        char *op1 = "r2";
        char *op2 = "r9";
        char *op3 = "#4h5";
        char *op4 = "&hello";
        char *op5 = "&5ello";
        char *op6 = "HELLO";
        char *op7 = "5eluklu8lo";
        char *op8 = "hel&*o";
        printf("%d\n", get_operand_type(op1));
        printf("%d\n", get_operand_type(op2));
        printf("%d\n", get_operand_type(op3));
        printf("%d\n", get_operand_type(op4));
        printf("%d\n", get_operand_type(op5));
        printf("%d\n", get_operand_type(op6));
        printf("%d\n", get_operand_type(op7));
        printf("%d\n", get_operand_type(op8));
}

void test_code_are()
{
    unsigned long int command = 0;
    char a= 'A', c='R';
    code_are(&command, a);
    code_are(&command, c);
    printf("%lu\n", command);
}

void test_get_register_index()
{
        char *reg1 = "r0";
        char *reg2 = "r4";
        char *reg3 = "r7";
        printf("%d\n", get_register_index(reg1));
        printf("%d\n", get_register_index(reg2));
        printf("%d\n", get_register_index(reg3));
}

int main(int argc, char *argv[])
{
    compile_multiple_files(argc, argv);
    return 0;
}