CC = gcc
FLAGS = -Wall -g

make all: stringProg

stringProg: Ex3.c
	$(CC) $(FLAGS) Ex3.c -o stringProg 

make run:
	./stringProg	

.PHONY: all clean	

clean:
	rm -f *.o stringProg