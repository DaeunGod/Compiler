CC = gcc
LEX = flex
BISON = bison

CFLAGS =

OBJS = lex.yy.o tiny.tab.o main.o util.o analyze.o symtab.o code.o cgen.o
TARGET = project4_14

all: ${TARGET}

${TARGET}: ${OBJS}
	$(CC) -o $@ ${OBJS} -ly -ll

main.o: main.c
	$(CC) -c main.c

util.o: util.c
	$(CC) -c util.c

lex.yy.c: tiny.l
	$(BISON) -d tiny.y
	$(LEX) tiny.l

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

tiny.tab.o: tiny.tab.c
	$(CC) -c tiny.tab.c 

clean:
	rm -f ${OBJS} ${TARGET}
	rm -f lex.yy.c
	rm -f tiny.tab.*
	rm -f *.tm
