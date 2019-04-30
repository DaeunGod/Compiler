CC = gcc
LEX = flex

CFLAGS =

OBJS = lex.yy.o main.o util.o
TARGET = 20131612

.SUFFIXES: .c .o

all: ${TARGET}

${TARGET}: ${OBJS}
	$(CC) -o $@ ${OBJS}

lex.yy.c: tiny.l
	$(LEX) tiny.l

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

clean:
	rm -f ${OBJS} ${TARGET}
	rm -f lex.yy.c
