void read_buffer()

void analyse_first_buffer()
{
    int buffer_type, local_error;
    read_buffer();
    if (size(buffer) == 0) {
        return 0; /* empty '\n' line / only whitespaces */
    }
    if (buffer[0] = ';') {
        return 0;
    } else if (check_correct_label(buffer)) {
        error = NO_ERROR;
        *optional_label = buffer;
        return LABEL;
    } else if (check_correct_command(buffer)) {
        error = NO_ERR0R;
        return COMMAND;
    if (local_error) {
        *error = TRUE;
        printf("the error is....");
        return -1; /* or return 0, need to think about it */
    }
}