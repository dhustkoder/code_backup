#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C99 CODE

typedef unsigned int Uint;
inline void cpy_reverse(char* dest, const char* src, Uint size);

int main(int argc, char** argv)
{
	const Uint print_times = 10;
	int exit_code = 0;
	
	if( argc < 2 ) {
		fprintf(stderr, "usage: %s <word>\n", argv[0]);
		return -1;
	}

	const char* const word = argv[1];
	const Uint word_len = strlen(word);

	char* const buffer = malloc(sizeof(char) * (word_len + 1));

	if(buffer == NULL) {
		perror("Failed to allocate memory: ");
		return -1;
	}

	cpy_reverse(buffer, word, word_len);
	buffer[word_len] = '\0';

	for(Uint i = 0; i < print_times; ++i) 
	{
		if(puts(buffer) == EOF)
		{
			perror("puts failed");
			exit_code = -1;
			goto buffer_cleanup;
		}
	}

	// ........

buffer_cleanup:
	free(buffer);
	return exit_code;
}




inline void cpy_reverse(char* dest, const char* src, Uint size) {
	src += size - 1;
	for( Uint i = 0; i < size ; ++i ) {
		*dest = *src;
		++dest;
		--src;
	}

}
