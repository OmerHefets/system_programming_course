#include "find_match.h"

int main()
{
    char pattern[MAXSTRING];
    char text[MAXSTRING];
    int match_index;
    get_pattern_and_text(pattern, text);
    match_index = match(pattern, text);
    printf("The index with the best match is: %d\n", match_index);
    return 0;
}