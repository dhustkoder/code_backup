#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* C89 / C90 / ANSI C CODE */

typedef unsigned int Uint;

void cpy_reverse();

main(int argc, char** argv)
{
	const Uint print_times = 10;
	int ret_val = 0;
	Uint i, word_len;
	const char* word;
	char* buffer;
	FILE* file;	

	if( argc < 2 ) {
		fprintf(stderr, "usage: %s <word>\n", argv[0]);
		return -1;
	}

	word = argv[1];
	word_len = strlen(word);

	buffer = malloc(sizeof(char) * (word_len + 1));

	if(buffer == NULL) {
		perror("Failed to allocate memory: ");
		return -1;
	}

	cpy_reverse(buffer, word, word_len);
	buffer[word_len] = '\0';

	for(i = 0; i < print_times; ++i) 
	{
		if( puts(buffer) == EOF ) {
			perror("puts failed: ");
			break;
		}
	}

	file = fopen("savefile.txt", "w");
	if( file == NULL ) {
		perror("failed to create savefile.txt: ");
		ret_val = -1;
		goto free_buffer;
	}
	
	fwrite(buffer, sizeof(char), word_len, file);
	if( ferror(file) ) {
		perror("fwrite failed: ");
		ret_val = -1;
		goto close_file;
	}

close_file:
	fclose(file);
	printf("file closed\n");
free_buffer:
	free(buffer);
	printf("buffer freed\n");

	return ret_val;
}





void cpy_reverse(char* dest, const char* src, Uint size) {
	Uint i;

	if(size == 0 )
		return;

	src += size-1;

	for( i = 0 ; i < size ; ++i ) {
		*dest = *src;
		++dest;
		--src;
	}
}
