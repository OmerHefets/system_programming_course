#include <stdio.h>

#define MAXSTRING 101
#define NO_MATCH -1

void get_pattern_and_text(char pattern[MAXSTRING], char text[MAXSTRING]);
int match(char pattern[MAXSTRING], char text[MAXSTRING]);
int check_num_differences_strings(char word1[MAXSTRING], char word2[MAXSTRING]);
void get_substring(int start, int end, char string[MAXSTRING], char substring[MAXSTRING]);