#include "numbers.h"

void convert_number_to_string(FILE *ifp, FILE *ofp)
{
    char digits[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char tens[10][10] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    char ten_to_twenty[10][10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    int number;
    while (fscanf(ifp, "%d", &number) != EOF) {
        if (number < 10) {
            fprintf(ofp,"%s\n", digits[number]);
        } else if (number >= 10 && number < 20) {
            fprintf(ofp, "%s\n", ten_to_twenty[number%10]);
        } else if (number%10 != 0) {
            fprintf(ofp, "%s %s\n", tens[number/10], digits[number%10]);
        } else {
            fprintf(ofp, "%s\n", tens[number/10]);
        }
    }
}