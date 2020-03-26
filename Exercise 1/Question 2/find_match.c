/*
 * The module with all the needed functions for main to check for the best index for the pattern and text.
*/

#include <string.h>
#include "find_match.h"


/*
 * Gets two strings from the user and prints them.
 * param pattern - first string as the pattern
 * param text - second string as the text
 * return - does not return any value
 */
void get_pattern_and_text(char pattern[MAXSTRING], char text[MAXSTRING])
{
    printf("This code checks for the smallest error between a string and a text [0-100 chars]\n");
    printf("Please insert the string for the pattern:\n");
    fgets(pattern, MAXSTRING, stdin);
    printf("Please insert the string for the text:\n");
    fgets(text, MAXSTRING, stdin);
    printf("The pattern is: ");
    fputs(pattern, stdout);
    printf("The text is: ");
    fputs(text, stdout);
}

/*
 * Checks for the smallest difference in the first word and the second string as text, returns the best index.
 * param pattern - first string as the pattern
 * param text - second string as the text
 * return - the index where the diffrence is the smallest
 */
int match(char pattern[MAXSTRING], char text[MAXSTRING])
{
    int i, pattern_len, min_difference=-1, current_difference, min_index;
    char compare_word[MAXSTRING];
    /* length of pattren is (strlen - 1) because the pattern holds the /n of the fgets as well */
    pattern_len = (strlen(pattern) - 1);
    if (pattern_len == 0) {
        return 0;
    }
    for (i=0 ; (i + pattern_len - 1) < MAXSTRING && text[i + pattern_len - 1] != '\0' ; i++) {
        get_substring(i, (i + pattern_len), text, compare_word);
        current_difference = check_num_differences_strings(pattern, compare_word);
        /* if it's the first difference check, put the difference in the minimun difference value */
        if (min_difference == -1) {
            min_difference = current_difference;
            min_index = i;
        }
        else if (current_difference < min_difference) {
            min_difference = current_difference;
            min_index = i;
        }
    }
    /* if the number of different chars is the same as the length of the pattern, there is no match between them and
    it's been said in the forum to return -1 in that case */
    if (min_difference == pattern_len) {
        return NO_MATCH;
    }
    return min_index;
}

/*
 * checks the number of character differences between two words (two strings)
 * param word1 - the first word
 * param word2 - the second word
 * return - int as the number of differences
 */
int check_num_differences_strings(char word1[MAXSTRING], char word2[MAXSTRING])
{
    int i, j, diff_counter=0;
    for (i=0, j=0 ; word1[i] != '\0' && word2[j] != '\0' && i < MAXSTRING ; i++, j++) {
        if (word1[i] != word2[j]) {
            diff_counter++;
        }
    }
    return diff_counter;
}

/*
 * returns a substring from a longer string.
 * param start - starting index of the substring
 * param end - ending index of the substring
 * string - the string to cut
 * substring - the string to put the substring into
 * return - void, only changes the substring
 */
void get_substring(int start, int end, char string[MAXSTRING], char substring[MAXSTRING])
{
    int i, j;
    for (i=0, j=0 ; i < end && i < MAXSTRING ; i++) {
        if (i >= start) {
            substring[j] = string[i];
            j++;
        }
    }
    substring[j] = '\0';
}