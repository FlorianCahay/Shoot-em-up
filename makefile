CFLAGS = -ansi -Wall -Wfatal-errors

project: main.o
	gcc -o project main.o

main.o: main.c
	gcc -c $(CFLAGS) main.c

clean:
	rm project *.o