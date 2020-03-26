/* 
 * The main file of a program that takes a string and checks if its increasing, decreasing, or no order
 * (or strictly increasing/decreasing)
 * using the functions in the find_match.c file
*/


#include "f_sequence.h"

int main()
{
    char input[MAXSTRING];

    printf("Please insert a string [0-100 chars only], so that the machine will check for any sequence: ");
    scanf("%s", input);
    /* f_sequence will check and print the results as requested */
    f_sequence(input);
    return 0;
}