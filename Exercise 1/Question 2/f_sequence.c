#include <string.h>
#include "f_sequence.h"

/* define an int for each kind of the sequence, to be used in a switch */
enum kind_of_sequence {STRICTLY_INCREASING, INCREASING, STRICTLY_DECREASING, DECREASING, NO_ORDER};
enum changed_values {FALSE, TRUE};


/*
 * gets the kind of the sequence and prints it
 * param input - the string that represents the sequence
 * return - does not return any value
 */
void f_sequence(char input[])
{
    int sequence;
    sequence = check_sequence(input);
    print_kind_sequence(sequence, input);
}

/*
 * gets the kind of the sequence
 * param input - the string that represents the sequence
 * return - int as the ENUM defined above - represents and sequence
 */
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
        /* using the diffrence between chars do unsderstand of the sequence is increasing or decreasing */
        difference_between_chars = input[i] - input[i+1];
        if (difference_between_chars < 0) {
            if (!changed_value) {
                sequence = STRICTLY_INCREASING;
                changed_value = TRUE;
            }
            /* if the sequence kind needs to increase but is already something else, there is no order */
            else if (sequence != STRICTLY_INCREASING) {
                sequence = NO_ORDER;
            }
        }
        else if (difference_between_chars > 0) {
            if (!changed_value) {
                sequence = STRICTLY_DECREASING;
                changed_value = TRUE;
            }
            /* if the sequence kind needs to decrease but is already something else, there is no order */
            else if (sequence != STRICTLY_DECREASING) {
                sequence = NO_ORDER;
            }
        }
        else if (difference_between_chars == 0) {
            two_equal_chars = TRUE;
        }
    }
    /* if two chars are equals, then strictly increasing string is increasing, and strictly decreasing is only decreasing */
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


/*
 * prints the kind of the sequence
 * param input - the string that represents the sequence
 * return - does not return any value
 */
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