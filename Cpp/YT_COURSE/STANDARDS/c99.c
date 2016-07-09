#include <stdio.h>
#include <stdlib.h>

// C99 CODE


typedef unsigned int Uint;

Uint mystrlen();
void cpyback();

int main(int argc, char** argv)
{
	const Uint print_times = 10;
	
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

	for(Uint i = 0; i < print_times; ++i) {
		puts(buffer);
	}


	free(buffer);
	return 0;
}





Uint mystrlen(const char* str) {
	Uint len = 0;
	
	while( *str != '\0' ) {
		++len;
		++str;
	}

	return len;
}


void cpyback(void* dest, const void* src, Uint size) {
	char* _dest = (char*) dest;
	const char* _src = (const char*) src;
	_src += size-1;

	for( Uint i = 0 ; i < size ; ++i ) {
		*_dest++ = *_src--;	
	}

}
