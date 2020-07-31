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

void second_maavar(..., *no_errors)
{
    while(getline != EOF) {
        nituah_line_second(..., *no_errors);
    }
}

void nituah_line_second()

void create_files()