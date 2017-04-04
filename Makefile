CC     = gcc
CFLAGS = -g -std=c99 -Wall -Werror -I. -fno-common -fPIC -pedantic

all: readtorrent

bencode.o: bencode.c
	$(CC) $(CFLAGS) -c -o bencode.o bencode.c

readtorrent: bencode.o readtorrent.c
	$(CC) -g readtorrent.c bencode.o -o $@

.PHONY: clean 

clean:
	rm -f bencode.o readtorrent

