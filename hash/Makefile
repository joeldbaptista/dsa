CC=gcc
CFLAGS=-O2 -Wall
INCLUDES=-I.

all: hashkey htdemo

# Example of usage
hashkey: hashkey.o hashfn.o
	$(CC) $(CFLAGS) $(INCLUDES) -o hashkey hashkey.o hashfn.o

# Hash-table demo: insert/search/delete driven by a commands file
htdemo: htdemo.o hashtab.o hashfn.o
	$(CC) $(CFLAGS) $(INCLUDES) -o htdemo htdemo.o hashtab.o hashfn.o

hashkey.o: hashkey.c hashfn.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o hashkey.o hashkey.c

hashfn.o: hashfn.c hashfn.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o hashfn.o hashfn.c

hashtab.o: hashtab.c hashtab.h hashfn.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o hashtab.o hashtab.c

htdemo.o: htdemo.c hashtab.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o htdemo.o htdemo.c

clean:
	rm -f hashkey htdemo *.o
