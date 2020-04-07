typedef struct complex_att {
    double real;
    double img;
} complex;

#define COMPLEX_NUMBER 6
#define MAX_COMMAND_LINE 100
/* explicit declarations in the code */
#define VALID 1
#define INVALID 0
#define ERROR -1
#define TRUE 1
#define FALSE 0
/* number of arguments of each command */
#define READ_COMP_NUM_ARGS 3
#define PRINT_COMP_NUM_ARGS 1
#define ADD_COMP_NUM_ARGS 2
#define SUB_COMP_NUM_ARGS 2
#define MULT_COMP_REAL_NUM_ARGS 2
#define MULT_COMP_IMG_NUM_ARGS 2
#define MULT_COMP_COMP_NUM_ARGS 2
#define ABS_COMP_NUM_ARGS 1
#define STOP_NUM_ARGS 0
#define A_ASCII_VALUE 65
#define COMPLEX_LENGTH 1
/* position of complex numbers in the pointer array */
#define A_POS 0
#define B_POS 1
#define C_POS 2
#define D_POS 3
#define E_POS 4
#define F_POS 5

/* gets a pointer to a string and returns a pointer to the first char in the string that isn't a white char (tab or space) */
char* pass_white_chars(char *s);
/* gets a pointer to a string and returns a pointer to the first char in the string that isn't a white char (tab or space) or comma */
char* pass_white_chars_and_commas(char *s);
/* reading an argument (that is not a white char or comma) into an arg string that is passed to the function.
will skip commas in search for the argument if skip_commas is 1. returns a pointer to the end of the argument. */
char* read_argument(char *s, char arg[MAX_COMMAND_LINE], int skip_commas);

/* a function that returns the number of arguments in a string, and ERROR if the comma positioning isn't correct */
int check_num_of_args_and_commas(char *s);
/* gets the arguments line (after command) and validates it - if the command and arguments are valid then execute the requested command.
if the command is invalid, printing an error (with the validation functions).
returns 1 (TRUE) if the command was valid or invalid - so the program will ask for another command. 
returns 0 (FALSE) only if the command was "stop" and a valid stop - then returns 0 to finish the program. */
int validate_command_and_execute(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE]);
/* check if the number of arguments requested in a string is the same as the value.
checks for error values if the string is not correct, and prints the error to the screen as well. */
int validate_number_of_args_and_commas(int args_num, char *s);
/* validate that a string is a valid double number (check for decimal seperator and minus sign as well 
return VALID if double and INVALID if not a double. */
int validate_double(char *s);
/* validate that a string is a complex number. return VALID if true, INVALID if not */
int validate_complex(char *s);
/* validating that the arguments in the read command are valid - complex and two numbers */
int validate_read_comp(char *s);
/* validating that the argument in the print/abs command is valid - complex */
int validate_print_abs_comp(char *s);
/* validating that the arguments in the add/sub/multiply command are valid - two complex numbers */
int validate_add_sub_mult_comp(char *s);
/* validating that the arguments in the multiply real/img command are valid - complex and a number */
int validate_mult_real_and_img(char *s);
/* validating the stop command */
int validate_stop(char *s);

/* execture read command */
void execute_read_comp(char *s, complex **pointers_array);
/* execute print/abs command */
void execute_print_abs_comp(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE]);
/* execute add/sub/multiply command */
void execute_add_sub_mult_comp(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE]);
/* execute muliply real/img command */
void execute_mult_real_and_img(char *s, complex **pointers_array, char command_name[MAX_COMMAND_LINE]);

/* resets all complex numbers inside an array of pointers to complex numbers */
void reset_complexes(complex **pointers_array, int array_size);
/* reading values to a complex number */
void read_complex(complex *number, double real_value, double img_value);
/* print a complex number in the format: real_part + (img_part)i */
void print_complex(complex *number);
/* prints all the explanations to the user */
void user_interface();

/* adding the values of two complex numbers and printing the result to the screen */
void add_complex_numbers(complex *z, complex *w);
/* subtracting the values of two complex numbers and printing the result to the screen */
void sub_complex_numbers(complex *z, complex *w);
/* multiplying a complex number with a real number and printing the result to the screen */
void multiply_complex_real(complex *z, double real_number);
/* multiplying a complex number with an imaginary number and printing the result to the screen */
void multiply_complex_img(complex *z, double img_number);
/* multiplying a complex number with another complex number and printing the result to the screen */
void multiply_complexes(complex *z, complex *w);
/* calculate the abs of a complex number and print the result to the screen (print a number) */
void abs_of_complex(complex *z);