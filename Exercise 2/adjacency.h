/* define the size of the 2d-array */
#define N 11
/* define values for TRUE and FALSE for the path function to return */
#define TRUE 1
#define FALSE 0

/* define 2d matrix with the corresponding N * N size, not asking the user for input */
typedef int adjmat[N][N];


/**
 * Function that set the value of the adjacency matrix.
 * param mat - the matrix to set the values for
 * return - void
 */
void set_adj_matrix(adjmat mat);

/**
 * prints a matrix
 * param mat - the matrix to be printed
 * return - void
 */
void print_matrix(adjmat mat);

/**
 * ask the user for a path, prints if the path exist or doesn't exist
 * param mat - the matrix to check for the path
 * return - TRUE (1) if the path was valid, then the main will ask for another path, FALSE (0) if the user entered -1,-1 (needs to exit the program)
 */
int check_and_print_path(adjmat mat);

/**
 * a function that sets a boolean value for path and calls a recursive function for the check.
 * param mat - the matrix to check the path for
 * param u - the node that the path starts from
 * param v - the node that the path needs to get to
 * return - TRUE (1) if there is a path, and FALSE (0) otherwise
 */
int path(adjmat mat, int u, int v);

/**
 * this recursive function checks for a valid path in its own height, and if not, checks for a path in her sons
 * param mat - the matrix to check the path for
 * param u - the node that the path starts from
 * param v - the node that the path needs to get to
 * param *bool - pointer to the boolean value that was defined in the path function
 * return - void
 */
void recursive_path(adjmat mat, int u, int v, int *bool);
