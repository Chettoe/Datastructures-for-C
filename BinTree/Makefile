CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = bintree
OBJECTS = main.o bin_tree.o test_bin_tree.o

all: ${BIN}

main.o: main.c test_bin_tree.h
bin_tree.o: bin_tree.c bin_tree.h
test.o: test_bin_tree.c test_bin_tree.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean