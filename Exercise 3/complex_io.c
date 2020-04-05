#include <stdio.h>
#include <string.h>
#include "complex.h"

char* read_white_chars(char *s)
{
    int count = 0;
    while ((*s == '\t' || *s == ' ') && (*s != '\0' && count < MAX_COMMAND_LINE)) {
        count++;
        s++;
    }
    return s;
}

char* read_argument(char *s)
{
    int count = 0;
    while ((*s != '\t' && *s != ' ') && (*s != '\0' && count < MAX_COMMAND_LINE)) {
        count++;
        s++;
    }
    return s;
}

void read_function(char *s, char command_name[MAX_COMMAND_LINE])
{
    int i = 0;
    while ((*s != '\t' && *s != ' ') && (*s != '\0' && i < MAX_COMMAND_LINE)) {
        command_name[i] = *s;
        i++;
        s++;
    }
    if (i == MAX_COMMAND_LINE) {
        command_name[--i] = '\0';
    } 
    else {
            command_name[i] = '\0';
    }
}


int check_num_of_args(char *s)
{
    int count = 0;
    int i = 0;
    while (i < MAX_COMMAND_LINE && *s != '\0') {
        while ((*s == '\t' || *s == ' ') && (i < MAX_COMMAND_LINE && *s != '\0' && *s != '\n')) {
            i++;
            s++;
        }
        if (i < MAX_COMMAND_LINE && *s != '\0') {
            count++;
            while ((*s != '\t' && *s != ' ') && (i < MAX_COMMAND_LINE && *s != '\0')) {
                i++;
                s++;
            }
        }
    }
    return count;
}


int validate_command_and_execute(char *s, char command_name[MAX_COMMAND_LINE])
{
    if (strcmp(command_name, "read_comp") == 0) {
        /*
        validate_read_comp();
        execute_read_comp();
        */
    } else if (strcmp(command_name, "print_comp") == 0) {
        ;
    } else if (strcmp(command_name, "add_comp") == 0) {
        ;
    } else if (strcmp(command_name, "sub_comp") == 0) {
        ;
    } else if (strcmp(command_name, "mult_comp_real") == 0) {
        ;
    } else if (strcmp(command_name, "mult_comp_img") == 0) {
        ;
    } else if (strcmp(command_name, "mult_comp_comp") == 0) {
        ;
    } else if (strcmp(command_name, "abs_comp") == 0) {
        ;
    } else if (strcmp(command_name, "stop") == 0) {
        ;
    } else {
        printf("invalid function name.\n");
        return INVALID;
    }
    return 0;
}

int validate_number_of_args(int args_num, char *s)
{
    int num_of_args = check_num_of_args(s);
    if (num_of_args > args_num) {
        printf("Invalid number of arguments - too many arguments.\n");
        return INVALID;
    } else if (num_of_args < args_num) {
       printf("Invalid number of arguments - missing arguments.\n");
       return INVALID;
    }
}

int validate_read_comp(char *s)
{
    if (!validate_number_of_args(READ_COMP_NUM_ARGS, s)) {
        return INVALID;
    }
}