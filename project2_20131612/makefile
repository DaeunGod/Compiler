CC = gcc
LEX = flex
BISON = bison

CFLAGS =

OBJS = lex.yy.o main.o util.o scan.o
TARGET = 20131612

.SUFFIXES: .c .o

all: ${TARGET}

${TARGET}: ${OBJS}
	$(CC) -o $@ ${OBJS}

lex.yy.c: tiny.l
	$(BISON) -d tiny.y
	$(LEX) tiny.l

lex.yy.o: lex.yy.c
	$(CC) -c tiny.tab.c lex.yy.c -ly -ll

clean:
	rm -f ${OBJS} ${TARGET}
	rm -f lex.yy.c
	rm -f tiny.tab.*
