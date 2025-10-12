CC = gcc
CFLAGS = -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = string
OBJECTS = main.o string.o

all: ${BIN}

main.o: main.c string.c

string.o: string.c string.h

${BIN}: ${OBJECTS}
		${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${OBJECTS} 

.PHONY: all clean