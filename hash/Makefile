CC=gcc
CFLAGS=-O2 -Wall
INCLUDES=-I.

# Example of usage
hashkey: hashkey.o hashfn.o
	$(CC) $(CFLAGS) $(INCLUDES) -o hashkey hashkey.o hashfn.o

hashkey.o: hashkey.c hashfn.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o hashkey.o hashkey.c

hashfn.o: hashfn.c hashfn.h
	$(CC) $(CFLAGS) $(INCLUDES) -c -o hashfn.o hashfn.c

clean:
	rm -f hashkey *.o
