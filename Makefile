CC     = gcc
CFLAGS = -g -O2 -Wall -Werror -W -I. -fno-common -fPIC -pedantic

bencode.o: bencode.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f bencode.o
