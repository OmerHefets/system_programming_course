#include <stdio.h>
#include <string.h>
#include "f_sequence.h"

enum kind_of_sequence {STRICTLY_INCREASING, INCREASING, STRICTLY_DECREASING, DECREASING, NO_ORDER};
enum changed_values {FALSE, TRUE};

void f_sequence(char input[])
{
    int sequence;
    sequence = check_sequence(input);
    print_kind_sequence(sequence, input);
}

int check_sequence(char input[])
{
    /* It's been said in the forum that the default definition for empty / 1 char string is strictly increasing. */
    int sequence = STRICTLY_INCREASING;
    int i, difference_between_chars;
    int changed_value = FALSE;
    int two_equal_chars = FALSE;
    if (strlen(input) == 0 || strlen(input) == 1) {
        return sequence;
    }
    for (i=0 ; i < MAXSTRING && input[i+1] != '\0' ; i++) {
        difference_between_chars = input[i] - input[i+1];
        if (difference_between_chars < 0) {
            if (!changed_value) {
                sequence = STRICTLY_INCREASING;
                changed_value = TRUE;
            }
            else if (sequence != STRICTLY_INCREASING) {
                sequence = NO_ORDER;
            }
        }
        else if (difference_between_chars > 0) {
            if (!changed_value) {
                sequence = STRICTLY_DECREASING;
                changed_value = TRUE;
            }
            else if (sequence != STRICTLY_DECREASING) {
                sequence = NO_ORDER;
            }
        }
        else if (difference_between_chars == 0) {
            two_equal_chars = TRUE;
        }
    }
    if (two_equal_chars) {
        if (sequence == STRICTLY_INCREASING) {
            sequence = INCREASING;
        }
        else if (sequence == STRICTLY_DECREASING) {
            sequence = DECREASING;
        }
    }
    return sequence;
}

void print_kind_sequence(int sequence, char input[])
{
    printf("The sequence ");
    printf("%s ", input);
    switch (sequence)
    {
    case STRICTLY_INCREASING:
        printf("is strictly increasing\n");
        break;
    case STRICTLY_DECREASING:
        printf("is strictly decreasing\n");
        break;
    case INCREASING:
        printf("is increasing\n");
        break;
    case DECREASING:
        printf("is decreasing\n");
        break;
    case NO_ORDER:
        printf("doesn't have any order\n");
        break;
    default:
        break;
    }
}