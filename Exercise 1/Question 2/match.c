/* 
 * The main file of a program that takes two strings - a pattern and a text, and return the index in text where 
 * the number of non fitting chars between the pattern and the sequence of chars from that index in the text - is the smallest.
 * 
 * In the main program there is a call to two functions get_pattern_and_text and match, which gets the input from the user
 * and gets the best index, then the main prints it to the screen.
 * 
 * text must be longer than the pattern
 */

#include "find_match.h"

int main()
{
    char pattern[MAXSTRING];
    char text[MAXSTRING];
    int match_index;
    get_pattern_and_text(pattern, text);
    match_index = match(pattern, text);
    /* printing the index to the screen */
    printf("\nThe index with the best match is: %d\n", match_index);
    return 0;
}