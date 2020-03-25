#include "f_sequence.h"

int main()
{
    char input[MAXSTRING];

    printf("Please insert a string [0-100 chars only], so that the machine will check for any sequence: ");
    scanf("%s", input);
    f_sequence(input);
    return 0;
}