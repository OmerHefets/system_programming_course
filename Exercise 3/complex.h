typedef struct complex_att {
    double real;
    double img;
} complex;

#define COMPLEX_NUMBER 6
#define MAX_COMMAND_LINE 100
#define VALID 1
#define INVALID 0
#define ERROR -1
#define TRUE 1
#define FALSE 0
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

char* pass_white_chars(char *s);
char* pass_white_chars_and_commas(char *s);
char* read_argument(char *s, char arg[MAX_COMMAND_LINE], int skip_commas);
void read_function(char *s, char command_name[MAX_COMMAND_LINE]);
int check_num_of_args_and_commas(char *s);
int validate_command_and_execute(char *s, char command_name[MAX_COMMAND_LINE]);
int validate_number_of_args_and_commas(int args_num, char *s);
int validate_double(char *s);
int validate_complex(char *s);
int validate_read_abs_comp(char *s);
int validate_print_comp(char *s);
int validate_add_sub_mult_comp(char *s);
int validate_mult_real_and_img(char *s);
int validate_stop(char *s);
void execute_read_comp(char *s, complex **pointers_array);
void reset_complexes(complex **pointers_array, int array_size);
void read_complex(complex *number, double real_value, double img_value);