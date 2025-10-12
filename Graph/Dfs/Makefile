CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = dfs
OBJECTS = main.o adj_array_graph.o array_list.o dfs.o

all: ${BIN}

main.o: main.c dfs.h
graph.o: adj_array_graph.c adj_array_graph.h array_list.h
array_list.o: array_list.c array_list.h
dfs.o: dfs.c dfs.h adj_array_graph.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean