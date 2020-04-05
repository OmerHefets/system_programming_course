mycomp: complex_io.o mycomp.o complex.h
	gcc -g -Wall -ansi -pedantic complex_io.o mycomp.o complex.h -o mycomp

complex_io.o: complex_io.c complex.h
	gcc -c -Wall -ansi -pedantic complex_io.c

mycomp.o: mycomp.c complex.h
	gcc -c -Wall -ansi -pedantic mycomp.c


# cleanup
clean:
	rm *.o