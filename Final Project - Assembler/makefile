assembler: main.o data_structures_functions.o parsing_error_checking.o defined_data_structures.o \
 parsing.o assembler.h
	gcc -g -Wall -ansi -pedantic main.o data_structures_functions.o parsing_error_checking.o \
	 defined_data_structures.o parsing.o assembler.h -o assembler
main.o: main.c assembler.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o
data_structures_functions.o: data_structures_functions.c assembler.h
	gcc -c -Wall -ansi -pedantic data_structures_functions.c -o data_structures_functions.o
parsing_error_checking.o: parsing_error_checking.c assembler.h
	gcc -c -Wall -ansi -pedantic parsing_error_checking.c -o parsing_error_checking.o
defined_data_structures.o: defined_data_structures.c assembler.h
	gcc -c -Wall -ansi -pedantic defined_data_structures.c -o defined_data_structures.o
parsing.o: parsing.c assembler.h
	gcc -c -Wall -ansi -pedantic parsing.c -o parsing.o


# cleanup
clean:
	rm *.o