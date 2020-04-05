typedef struct complex_att {
    double real;
    double img;
} complex;

#define COMPLEX_NUMBER 6
#define MAX_COMMAND_LINE 100
#define VALID 1
#define INVALID 0
#define READ_COMP_NUM_ARGS 3
#define PRINT_COMP_NUM_ARGS 1
#define ADD_COMP_NUM_ARGS 2
#define SUB_COMP_NUM_ARGS 2
#define MULT_COMP_REAL_NUM_ARGS 2
#define MULT_COMP_IMG_NUM_ARGS 2
#define MULT_COMP_COMP_NUM_ARGS 2
#define ABS_COMP_NUM_ARGS 1
#define STOP_NUM_ARGS 0

char* read_white_chars(char *s);
char* read_argument(char *s);
void read_function(char *s, char command_name[MAX_COMMAND_LINE]);
int check_num_of_args(char *s);
int validate_command_and_execute(char *s, char command_name[MAX_COMMAND_LINE]);
int validate_read_comp();