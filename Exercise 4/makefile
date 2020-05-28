numbers: numbers.o number_converter.o numbers.h
	gcc -g -Wall -ansi -pedantic numbers.o number_converter.o numbers.h -o numbers
numbers.o: numbers.c numbers.h
	gcc -c -Wall -ansi -pedantic numbers.c -o numbers.o
number_converter.o: number_converter.c numbers.h
	gcc -c -Wall -ansi -pedantic number_converter.c -o number_converter.o


# cleanup
clean:
	rm *.o