#include "adjacency.h"

int path(adjmat mat, int u, int v)
{
    int boolean_value = FALSE;
    recursive_path(mat, u, v, &boolean_value);
    return boolean_value;
}

void recursive_path(adjmat mat, int u, int v, int *bool)
{
    int j;
    if (mat[u][v] == 1) {
        *bool = TRUE;
    }
    for (j=0 ; j < N ; j++) {
        if (mat[u][j] == 1) {
            recursive_path(mat, j, v, bool);
        }
    }
}