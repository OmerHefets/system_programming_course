#include <string.h>
#include "find_match.h"

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

int match(char pattern[MAXSTRING], char text[MAXSTRING])
{
    int i, pattern_len, min_difference=-1, current_difference, min_index;
    char compare_word[MAXSTRING];
    pattern_len = strlen(pattern);
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
    if (min_difference == pattern_len) {
        return NO_MATCH;
    }
    return min_index;
}

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