CC     = gcc
CFLAGS = -g -std=c99 -Wall -Werror -I. -pedantic

all: readtorrent parse_response

bencode.o: bencode.c
	$(CC) $(CFLAGS) -c -o bencode.o bencode.c

readtorrent: bencode.o readtorrent.c
	$(CC) -Wall -g readtorrent.c bencode.o -o $@

parse_response: parse_response.c bencode.o
	$(CC) $(CFLAGS) parse_response.c bencode.o -o parse_response


.PHONY: clean 

clean:
	rm -f bencode.o readtorrent parse_response

