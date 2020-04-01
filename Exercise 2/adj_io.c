/**
 * this module is responsible for all the functionallity about the input and output of the program.
 * includes functions to get the matrix values, print the matrix and ask and print the path's that the user ask about.
 */

#include <stdio.h>
#include "adjacency.h"

/**
 * Function that set the value of the adjacency matrix.
 * param mat - the matrix to set the values for
 * return - void
 */
void set_adj_matrix(adjmat mat)
{
    int i, j, temp;
    printf("Please enter the values for the adjacency matrix. the Matrix is a %dx%d matrix, with values 0 / 1.\n", N, N);
    printf("Therefore, insert %d values in each row, seperated with space in between and finish the row with newline:\n", N);
    for (i=0 ; i < N ; i++) {
        for (j=0 ; j < N ; j++) {
            /* scan the int seperately for each matrix index */
            scanf("%d", &temp);
            mat[i][j] = temp;
        }
    }
}


/**
 * prints a matrix
 * param mat - the matrix to be printed
 * return - void
 */
void print_matrix(adjmat mat)
{
    int i, j;
    printf("The resulted matrix is:\n\t");
    for (i=0 ; i < N ; i++) {
        printf("%d\t", i);
    }
    /* print 2 newlines for easy visualization of the matrix */
    printf("\n\n");
    for (i=0 ; i < N ; i++) {
        printf("%d\t", i);
        for (j=0 ; j < N ; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

/**
 * ask the user for a path, prints if the path exist or doesn't exist
 * param mat - the matrix to check for the path
 * return - TRUE (1) if the path was valid, then the main will ask for another path, FALSE (0) if the user entered -1,-1 (needs to exit the program)
 */
int check_and_print_path(adjmat mat)
{
    /* scan the nodes from the user */
    int node_u, node_v, existing_path;
    printf("Please insert two indexes of nodes in tree, to check for path from the first node to the second one (-1 and -1 to exit):\n");
    scanf("%d", &node_u);
    scanf("%d", &node_v);
    /* return FALSE if the user enters -1, -1 because he wants to exit the program (and dont continue with invaild values to the path call) */
    if (node_u == -1 && node_v == -1) {
        return FALSE;
    }
    /* check for existing path, and then print the results */
    existing_path = path(mat, node_u, node_v);
    printf("The first index is: %d\n", node_u);
    printf("The second index is: %d\n", node_v);
    if (existing_path == TRUE) {
        printf("And there IS a path from %d to %d, as the value is TRUE\n\n", node_u, node_v);
    } else {
        printf("And there ISN'T a path from %d to %d, as the value is FALSE\n\n", node_u, node_v);
    }
    /* if the user asked for a real path, return TRUE so the program will ask for another one */
    return TRUE;
}