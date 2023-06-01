CC = gcc 

all: thread_pool

thread_pool: thread_pool.c Queue.c 
	$(CC) -o coder thread_pool.c Queue.c ./libCodec.so -pthread


.PHONY: all clean
clean:
	-rm coder
