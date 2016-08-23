CC=gcc -m64


all: t1

t1: t1.o linkhash.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $<
