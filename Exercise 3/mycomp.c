#include <stdio.h>
#include "complex.h"
#define MAXLINE 100

int main()
{
    char line[MAXLINE];
    while(fgets(line, MAXLINE, stdin) != NULL) {
            fputs(line, stdout);
    }
    if (fgets(line, MAXLINE, stdin) == NULL) {
        printf("ll");
    }
    return 0;
}