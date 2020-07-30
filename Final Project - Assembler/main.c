void compile_multiple_files(argc, argv)
{
    while (argc > 0) {
        (compile_file(argv + ".as"));
    }
}

void compile_file(FILE *file)
{
    /* declare empty data structures + IC + DC */
    int no_errors = TRUE; /* or use it as a pointer! */
    no_errors = first_maavar(...);

    if (no_errors = TRUE) {
        no_errors = second_maavar(...);
    }
    if (no_errors = TRUE) {
        create_files(data_structures_declared);
    }
    free_all_DS();
}

void first_maavar(..., *no_errors)
{
    while(getline != EOF) {
        nituah_line_first(..., *no_errors);
    }
    update_data_symbols(symbols_table);
}

void second_maavar(..., *no_errors)
{
    while(getline != EOF) {
        nituah_line_second(..., *no_errors);
    }
}

void nituah_line_first()
{
    int buffer_type = 0, label;    
    buffer_type = analyse_first_buffer();
    /* if's depending on the buffer type */
    if comment or empty or not_defined {
        return;
    }
    if label {
        label = TRUE;
        read_buffer();
        check_correct_command();
    }
    if buffer == ".string" or ".data" {
        compile_string_or_data_line(..., label);
    } else if buffer == ".extern" or ".entry" {
        compile_entry_or_extern_line(..., label);
    } else { /* this is an operation */
        compile_operation_line(...,label);
    }
}

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

void read_buffer()

void nituah_line_second()

void update_data_symbols()

void create_files()

void free_all_DS()

void check_correct_command()

void check_correct_label()

void compile_string_or_data_line()

void compile_entry_or_extern_line()

void compile_operation_line()