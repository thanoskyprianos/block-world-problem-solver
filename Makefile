CC = gcc
FLAGS = -Wall -Werror -pedantic -g3
SIZE = 10

run: main
	time ./main ./test_inputs/n_$(SIZE).txt

main: main.c blocks.o priority_queue.o stack.o
	$(CC) $(FLAGS) -o main main.c blocks.o priority_queue.o stack.o

blocks.o: blocks.c blocks.h
	$(CC) $(FLAGS) -c blocks.c

priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(FLAGS) -c priority_queue.c

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c stack.c

test: test.c blocks.o priority_queue.o stack.o
	$(CC) $(FLAGS) -o test test.c blocks.o priority_queue.o stack.o

.PHONY: clean
clean:
	rm -f main test *.o