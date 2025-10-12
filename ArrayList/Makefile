CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = array_list
OBJECTS = main.o array_list.o test_array_list.o

all: ${BIN}

main.o: main.c array_list.h test_array_list.h
array_list.o: array_list.c array_list.h 
test.o: test_array_list.c test_array_list.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean