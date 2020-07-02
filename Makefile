all: main.o
	gcc -o pthread_test main.o -lpthread

main.o: main.c
	gcc -c main.c

run: all
	./pthread_test

clean:
	rm *.o