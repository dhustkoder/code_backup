#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* C89 / C90 / ANSI C CODE */

typedef unsigned int Uint;

void cpy_reverse();

main(int argc, char** argv)
{
	const Uint print_times = 10;
	Uint i, word_len;
	const char* word;
	char* buffer;
	
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
		if( puts(buffer) == EOF )
		{
			perror("puts failed: ");
			free(buffer);
			return -1;
		}
	}


	free(buffer);
	return 0;
}





void cpy_reverse(char* dest, const char* src, Uint size) {
	Uint i;
	src += size-1;

	for( i = 0 ; i < size ; ++i ) {
		*dest = *src;
		++dest;
		--src;
	}

}
