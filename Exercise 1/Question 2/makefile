match: find_match.o match.o find_match.h
	gcc -g -Wall -ansi -pedantic find_match.o match.o find_match.h -o match
find_match.o: find_match.c
	gcc -c -Wall -ansi -pedantic find_match.c -o find_match.o
match.o: match.c
	gcc -c -Wall -ansi -pedantic match.c -o match.o