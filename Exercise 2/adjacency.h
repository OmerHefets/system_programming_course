#define N 11
#define TRUE 1
#define FALSE 0

typedef int adjmat[N][N];

void set_adj_matrix(adjmat mat);
void print_matrix(adjmat mat);
int check_and_print_path(adjmat mat);
int path(adjmat mat, int u, int v);
void recursive_path(adjmat mat, int u, int v, int *bool);
