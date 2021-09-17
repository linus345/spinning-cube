IDIR=./include
CC=gcc
CFLAGS=-std=c99 -Wall -I$(IDIR) $(pkg-config --cflags --libs x11) -lX11

EXEC=a.out

$(EXEC): main.o
	$(CC) *.o -o $(EXEC) $(CFLAGS)


main.o: main.c
	$(CC) -c main.c $(CFLAGS)


.PHONY: clean

clean:
	rm -f *.o $(EXEC)
