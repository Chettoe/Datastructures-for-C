CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = list
OBJECTS = main.o linked_list.o list_test.o

all: ${BIN}

main.o: main.c linked_list.h list_test.h
list.o: linked_list.c linked_list.h 
test.o: list_test.c list_test.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean