CC = gcc

CFLAGS = 

OBJS = main.o util.o
TARGET = 20131612

.SUFFIXES: .c .o

all: ${TARGET}

${TARGET}: ${OBJS}
	$(CC) -o $@ ${OBJS}

clean:
	rm -f ${OBJS} ${TARGET}
