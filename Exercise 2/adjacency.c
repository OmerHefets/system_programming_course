#include <stdio.h>
#include "adjacency.h"

int main()
{
    int ask_for_path = TRUE;
    adjmat matrix;
    set_adj_matrix(matrix);
    print_matrix(matrix);
    while (ask_for_path) {
        ask_for_path = check_and_print_path(matrix);
        if (ask_for_path == FALSE) {
            printf("You entered values -1 and -1 to exit the program.\n");
        }
    }
    return 0;
}