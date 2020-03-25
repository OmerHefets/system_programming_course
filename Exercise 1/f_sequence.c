#include <stdio.h>
#include <string.h>
#include "f_sequence.h"

enum kind_of_sequence {STRICTLY_INCREASING, INCREASING, STRICTLY_DECREASING, DECREASING, NO_ORDER};

void f_sequence(char input[])
{
    int i;
    for (i=0 ; i < MAXSTRING && input[i] != '\0' ; i++) {
        printf("Ascii value of %c is %d\n", input[i], input[i]);
    }
    printf("\ndam\n");
}

int check_sequence(char input[])
{
    // It's been said in the forum that the default definition for empty / 1 char string is strictly increasing.
    int sequence = STRICTLY_INCREASING;
    int i;
    if (strlen(input) == 0 || strlen(input) == 1) {
        return sequence;
    }
    for (i=0 ; i < MAXSTRING || input[i+1] != '\0' ; i++) {
        if (input[i] < input[i+1] && sequence != STRICTLY_INCREASING) {
            
        }
    }