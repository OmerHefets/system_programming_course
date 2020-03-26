#include <stdio.h>

/* maxstring is 100 + 1 because fgets adds '\n' at the end*/
#define MAXSTRING 101
/* if there is no match of the pattern to the text*/
#define NO_MATCH -1

/*
 * Gets two strings from the user and prints them.
 * param pattern - first string as the pattern
 * param text - second string as the text
 * return - does not return any value
 */
void get_pattern_and_text(char pattern[MAXSTRING], char text[MAXSTRING]);

/*
 * Checks for the smallest difference in the first word and the second string as text, returns the best index.
 * param pattern - first string as the pattern
 * param text - second string as the text
 * return - the index where the diffrence is the smallest
 */
int match(char pattern[MAXSTRING], char text[MAXSTRING]);

/*
 * checks the number of character differences between two words (two strings)
 * param word1 - the first word
 * param word2 - the second word
 * return - int as the number of differences
 */
int check_num_differences_strings(char word1[MAXSTRING], char word2[MAXSTRING]);

/*
 * returns a substring from a longer string.
 * param start - starting index of the substring
 * param end - ending index of the substring
 * string - the string to cut
 * substring - the string to put the substring into
 * return - void, only changes the substring
 */
void get_substring(int start, int end, char string[MAXSTRING], char substring[MAXSTRING]);