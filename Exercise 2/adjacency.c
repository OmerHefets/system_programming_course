/**
 * This is the main module of the adjacency program. It's goal is to get a 2d matrix values from the user, print the matrix,
 * and then ask for 2 nodes in the tree, to check with the matrix if there is a valid path from the first one to the other one.
 * 
 * The function will keep asking the user for values to check path's, unless he insert the values (-1, -1) to exit the program.
 */

#include <stdio.h>
#include "adjacency.h"

int main()
{
    /* define a value that will hold if the program needs to ask the user again for path valus */
    int ask_for_path = TRUE;
    adjmat matrix;
    /* set the matrix values and print the matrix to the screen */
    set_adj_matrix(matrix);
    print_matrix(matrix);
    /* keep getting values to check path's from the user */
    while (ask_for_path) {
        ask_for_path = check_and_print_path(matrix);
        /* if the user will ther (-1, -1) then the function will return FALSE and check the param to FALSE */
        if (ask_for_path == FALSE) {
            printf("You entered values -1 and -1 to exit the program.\n");
        }
    }
    return 0;
}