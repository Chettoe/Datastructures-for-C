CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = stack
OBJECTS = main.o stack.o linked_list.o test_stack.o 

all: ${BIN}

main.o: main.c stack.h test_stack.h
stack.o: stack.c stack.h linked_list.h
linked_list.o: linked_list.c linked_list.h
test_stack.o: test_stack.c test_stack.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean