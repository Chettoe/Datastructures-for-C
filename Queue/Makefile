CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = queue
OBJECTS = main.o queue.o linked_list.o test_queue.o 

all: ${BIN}

main.o: main.c queue.h test_queue.h
queue.o: queue.c queue.h linked_list.h
linked_list.o: linked_list.c linked_list.h
test_queue.o: test_queue.c test_queue.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean