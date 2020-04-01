adjacency: adj_io.o adj_path.o adjacency.o adjacency.h
	gcc -g -Wall -ansi -pedantic adj_io.o adj_path.o adjacency.o adjacency.h -o adjacency
adj_io.o: adj_io.c adjacency.h
	gcc -c -Wall -ansi -pedantic adj_io.c
adj_path.o: adj_path.c adjacency.h
	gcc -c -Wall -ansi -pedantic adj_path.c
adjacency.o: adjacency.c adjacency.h
	gcc -c -Wall -ansi -pedantic adjacency.c

# cleanup
clean:
	rm *.o