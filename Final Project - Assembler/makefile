assembler: main.o data_structures_functions.o assembler.h
	gcc -g -Wall -ansi -pedantic main.o data_structures_functions.o assembler.h -o assembler
main.o: main.c assembler.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o
data_structures_functions.o: data_structures_functions.c assembler.h
	gcc -c -Wall -ansi -pedantic data_structures_functions.c -o data_structures_functions.o


# cleanup
clean:
	rm *.o