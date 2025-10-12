CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = graph
OBJECTS = main.o adj_array_graph.o array_list.o test_adj_array_graph.o

all: ${BIN}

main.o: main.c test_adj_array_graph.h
graph.o: adj_array_graph.c adj_array_graph.h array_list.h
array_list.o: array_list.c array_list.h
test.o: test_adj_array_graph.c test_adj_array_graph.h adj_array_graph.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean