CC = gcc
FLAGS = -Wall -g 


all: libclassloops.a libclassrec.a libclassloops.so libclassrec.so mains maindrec maindloop

loops: libclassloops.a
libclassloops.a: advancedClassificationLoop.o basicsClassification.o
	 ar -rcs libclassloops.a advancedClassificationLoop.o basicsClassification.o

recursives: libclassrec.a
libclassrec.a: advancedClassificationRecursion.o basicsClassification.o
	 ar -rcs libclassrec.a advancedClassificationRecursion.o basicsClassification.o

recursived: libclassrec.so
libclassrec.so: advancedClassificationRecursion.o basicsClassification.o
	 $(CC) -shared -o  libclassrec.so advancedClassificationRecursion.o basicsClassification.o

loopd: libclassloops.so
libclassloops.so: advancedClassificationLoop.o basicsClassification.o
	 $(CC) -shared -o libclassloops.so advancedClassificationLoop.o basicsClassification.o

mains: main.o libclassrec.a 
	 $(CC) $(FLAGS) -o mains main.o libclassrec.a -lm

maindloop: main.o 
	 $(CC) $(FLAGS) -o maindloop main.o ./libclassloops.so -lm
	 
maindrec: main.o
	 $(CC) $(FLAGS) -o maindrec main.o ./libclassrec.so -lm
	
basicsClassification.o: basicsClassification.c NumClass.h
	 $(CC) $(FLAGS) -c basicsClassification.c -lm
advancedClassificationLoop.o: advancedClassificationLoop.c NumClass.h
	 $(CC) $(FLAGS) -c advancedClassificationLoop.c -lm 
advancedClassificationRecursion.o: advancedClassificationRecursion.c NumClass.h
	 $(CC) $(FLAGS) -c advancedClassificationRecursion.c -lm	 	
main.o: main.c NumClass.h
	$(CC) $(FLAGS) -c main.c 	
	
.PHONY: all clean	
	
clean:	
	 rm -f *.o *.a *.so maindloop maindrec mains

