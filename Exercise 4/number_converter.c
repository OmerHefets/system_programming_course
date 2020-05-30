/**
 * This module holds the required functions to convert numbers from integers to strings, to convert a number to
 * words in english
 */

#include "numbers.h"

/* converts a number between 0-99 to the equivalent word in english */
void convert_number_to_string(FILE *ifp, FILE *ofp)
{
    /* keeping all required words for the numbers in three arrays */
    char digits[][WORD_LENGTH] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char tens[][WORD_LENGTH] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    char ten_to_twenty[][WORD_LENGTH] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    int number;
    /* not using constants istead of numbers in this code because the code is more readable without it */
    while (fscanf(ifp, "%d", &number) != EOF) {
        /* if the number is smaller than 10, the digit in the digits array is the specific requested english word */
        if (number < 10) {
            fprintf(ofp,"%s\n", digits[number]);
        /* if the number is between 10-20, there are special english words for these numbers */
        } else if (number >= 10 && number < 20) {
            fprintf(ofp, "%s\n", ten_to_twenty[number%10]);
        /* if the number is bigger than 20, and not in the group of tens, then we need to print two parts: the tens and the digits */
        } else if (number%10 != 0) {
            fprintf(ofp, "%s %s\n", tens[number/10], digits[number%10]);
        /* if the number is in the group of tens then print only its tens digit */
        } else {
            fprintf(ofp, "%s\n", tens[number/10]);
        }
    }
}