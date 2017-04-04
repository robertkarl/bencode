/* print peers from a tracker response */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
	bencode_t root, curr;
	long fsize;
	char *filecontents = read_entire_file(argv[1], &fsize);

	bencode_init(&root, filecontents, fsize);

	const char *peers;
	int urllen;
	do {
		bencode_dict_get_next(&root, &curr, &peers, &urllen);
	} while (strncmp(peers, "peers", 5));

	bencode_string_value(&curr, &peers, &urllen);

	int i = 0;
	while (i < urllen) {
		for (int j = 0; j < 4; j++) {
			printf("%u", (uint8_t)peers[i]);
			if (j != 3)
				printf(".");
			i += 1;
		}
		printf(":");
		uint8_t port[2];
		port[0] = (uint8_t)peers[i++];
		port[1] = (uint8_t)peers[i++];
		printf("%d\n", port[0] << 8 | port[1]);
	}

	exit(0);
}

