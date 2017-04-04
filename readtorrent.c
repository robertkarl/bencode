/* print torrent announce and file info */

/* Data structure definitions aren't needed; the data is on
disk in bencode format. we can browse it with bencode f(x)s. */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "bencode.h"

char *read_entire_file(char *fname, long *fsize_out)
{
	FILE *f = fopen(fname, "rb");
	fseek(f, 0, SEEK_END);
	*fsize_out = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	char *string = malloc(*fsize_out + 1);
	fread(string, *fsize_out, 1, f);
	fclose(f);

	string[*fsize_out] = 0;
	return string;
}

int main(int argc, char **argv) {
	bencode_t root, curr, prev;
	const char *key;
	int keylen;
	long fsize;
	char *filecontents = read_entire_file(argv[1], &fsize);
	char *announce_url = calloc(200, 1);

	bencode_init(&root, filecontents, fsize);
	bencode_clone(&root, &prev);

	assert(bencode_is_dict(&root));

	const char *url;
	int urllen;
	do {
		bencode_dict_get_next(&prev, &curr, &url, &urllen);
		bencode_clone(&curr, &prev);
	} while (strncmp(url, "announce", 8));
	
	bencode_string_value(&curr, &url, &urllen);
	for (int i = 0; i < urllen; i++)
		printf("%c", url[i]);
	printf("\n");

	exit(0);
}

