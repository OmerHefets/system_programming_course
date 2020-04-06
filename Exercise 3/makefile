mycomp: complex_io.o mycomp.o complex.o validate_input.o execute_input.o complex.h
	gcc -g -Wall -ansi -pedantic complex_io.o mycomp.o complex.o validate_input.o execute_input.o complex.h -o mycomp -lm

complex_io.o: complex_io.c complex.h
	gcc -c -Wall -ansi -pedantic complex_io.c

mycomp.o: mycomp.c complex.h
	gcc -c -Wall -ansi -pedantic mycomp.c

complex.o: complex.c complex.h
	gcc -c -Wall -ansi -pedantic complex.c

validate_input.o: validate_input.c complex.h
	gcc -c -Wall -ansi -pedantic validate_input.c

execute_input.o: execute_input.c complex.h
	gcc -c -Wall -ansi -pedantic execute_input.c

# cleanup
clean:
	rm *.o