/**
 * this module holds the functions required to calculate if a path in a matrix is valid or not, recursively
 * comments inside the functions to explain the recursion
 */

#include "adjacency.h"

/**
 * a function that sets a boolean value for path and calls a recursive function for the check.
 * param mat - the matrix to check the path for
 * param u - the node that the path starts from
 * param v - the node that the path needs to get to
 * return - TRUE (1) if there is a path, and FALSE (0) otherwise
 */
int path(adjmat mat, int u, int v)
{
    /* set a int value to return is there is path or not */
    int boolean_value = FALSE;
    /* call the recursive function with the value address and not value, so the same value will be changed inside the recursive calls */
    recursive_path(mat, u, v, &boolean_value);
    return boolean_value;
}

/**
 * this recursive function checks for a valid path in its own height, and if not, checks for a path in her sons
 * param mat - the matrix to check the path for
 * param u - the node that the path starts from
 * param v - the node that the path needs to get to
 * param *bool - pointer to the boolean value that was defined in the path function
 * return - void
 */
void recursive_path(adjmat mat, int u, int v, int *bool)
{
    int j;
    /* if the value is 1 then by the matrix rules the path is valid and one of the sons is the requested node */
    if (mat[u][v] == 1) {
        *bool = TRUE;
    }
    /* check for all the sons of the node, if one of their son is the parent of the node */
    for (j=0 ; j < N ; j++) {
        /* if the value in the mat is one, then this node is a son of the correct node, so send a recursive call for the row of the new son */
        if (mat[u][j] == 1) {
            recursive_path(mat, j, v, bool);
        }
    }
}