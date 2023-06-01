CC = gcc
FLAGS = -Wall -g

all: libMat.a connections

connections: main.o 
	$(CC) $(FLAGS) -o connections main.o libMat.a -lm 

mat: libMat.a
libMat.a: my_mat.o
	ar -rcs  libMat.a my_mat.o

my_mat.o: my_mat.c my_mat.h
	$(CC) $(FLAGS) -c my_mat.c -lm

main.o: main.c my_mat.h
	$(CC) $(FLAGS) -c main.c -lm 	

.PHONY: all clean	

clean:
	rm -f *.o *.a *.so main connections