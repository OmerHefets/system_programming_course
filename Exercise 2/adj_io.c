#include <stdio.h>

#include "adjacency.h"

void set_adj_matrix(adjmat mat)
{
    int i, j, temp;
    printf("Please enter the values for the adjacency matrix. the Matrix is a %dx%d matrix, with values 0 / 1.\n", N, N);
    printf("Therefore, insert %d values in each row, seperated with space in between and finish the row with newline:\n", N);
    for (i=0 ; i < N ; i++) {
        for (j=0 ; j < N ; j++) {
            scanf("%d", &temp);
            mat[i][j] = temp;
        }
    }
}

void print_matrix(adjmat mat)
{
    int i, j;
    printf("The resulted matrix is:\n\t");
    for (i=0 ; i < N ; i++) {
        printf("%d\t", i);
    }
    printf("\n\n");
    for (i=0 ; i < N ; i++) {
        printf("%d\t", i);
        for (j=0 ; j < N ; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

int check_and_print_path(adjmat mat)
{
    int node_u, node_v, existing_path;
    printf("Please insert two indexes of nodes in tree, to check for path from the first node to the second one (-1 and -1 to exit):\n");
    scanf("%d", &node_u);
    scanf("%d", &node_v);
    if (node_u == -1 && node_v == -1) {
        return FALSE;
    }
    existing_path = path(mat, node_u, node_v);
    printf("The first index is: %d\n", node_u);
    printf("The second index is: %d\n", node_v);
    if (existing_path == TRUE) {
        printf("And there IS a path from %d to %d, as the value is TRUE\n", node_u, node_v);
    } else {
        printf("And there ISN'T a path from %d to %d, as the value is FALSE\n", node_u, node_v);
    }
    return TRUE;
}