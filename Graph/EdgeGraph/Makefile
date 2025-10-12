CC = gcc
DEBUG = -DRUN_TEST
NDEBUG = -DNDEBUG
CFLAGS = ${DEBUG} -Wall -g -O2 -fsanitize=address -fsanitize=undefined
BIN = graph
OBJECTS = main.o edge_graph.o array_list.o test_edge_graph.o

all: ${BIN}

main.o: main.c test_edge_graph.h
graph.o: edge_graph.c edge_graph.h array_list.h
array_list: array_list.c array_list.h
test.o: test_edge_graph.c test_edge_graph.h edge_graph.h

${BIN}: ${OBJECTS} 
	${CC} ${CFLAGS} -o ${BIN} ${OBJECTS}

clean:
	rm -f ${BIN} ${OBJECTS}

.PHONY: all clean