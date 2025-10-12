CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = hash_map
OBJECTS = main.o hash_map.o test_hash_map.o

all: ${BIN}

main.o: main.c hash_map.h test_hash_map.h
hash_map.o: hash_map.c hash_map.h
test.o: test_hash_map.c test_hash_map.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean