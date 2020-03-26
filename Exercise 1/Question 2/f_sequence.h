#include <stdio.h>
/* max string as defined */
#define MAXSTRING 100

/*
 * gets the kind of the sequence and prints it
 * param input - the string that represents the sequence
 * return - does not return any value
 */
void f_sequence(char line[]);

/*
 * gets the kind of the sequence
 * param input - the string that represents the sequence
 * return - int as the ENUM defined above - represents and sequence
 */
int check_sequence(char line[]);

/*
 * prints the kind of the sequence
 * param input - the string that represents the sequence
 * return - does not return any value
 */
void print_kind_sequence(int sequence, char line[]);