#include <stdio.h>
#include <stdlib.h>

// C99 CODE

typedef unsigned int Uint;

inline Uint mystrlen(const char*);
inline void cpyback(void*, const void*, Uint);

int main(int argc, char** argv)
{
	const Uint PRINT_TIMES = 10;
	int exit_code = 0;
	
	if( argc < 2 ) {
		fprintf(stderr, "usage: %s <word>\n", argv[0]);
		return -1;
	}

	const Uint word_len = mystrlen(argv[1]);

	char* const buffer = malloc(sizeof(char) * (word_len + 1));

	if(buffer == NULL) {
		perror("Failed to allocate memory: ");
		return -1;
	}

	cpyback(buffer, argv[1], word_len);
	buffer[word_len] = '\0';

	for(Uint i = 0; i < PRINT_TIMES; ++i) 
	{
		if(puts(buffer) == EOF)
		{
			perror("puts failed");
			exit_code = -1;
			goto buffer_cleanup;
		}
	}


buffer_cleanup:
	puts("WRITING BUFFER TO STDOUT");
	fwrite(buffer, sizeof(char), word_len, stdout);
	putchar('\n');
	free(buffer);


	return exit_code;
}





inline Uint mystrlen(const char* str) {
	Uint len = 0;
	
	while( *str != '\0' ) {
		++len;
		++str;
	}

	return len;
}


inline void cpyback(void* dest, const void* src, Uint size) {
	char* _dest = (char*) dest;
	const char* _src = (const char*) src;
	_src += size-1;

	for( Uint i = 0 ; i < size ; ++i ) {
		*_dest++ = *_src--;	
	}

}
