#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// C++98 / C++03 CODE


typedef unsigned int Uint;

namespace {

struct ScopeFree {
	ScopeFree(void* p) : m_p(p) { }
	~ScopeFree() { free(m_p); printf("buffer freed\n"); }
	void* m_p;
};

struct ScopeFClose {
	ScopeFClose(FILE* f) : m_f(f) {}
	~ScopeFClose() { fclose(m_f); printf("file closed\n"); }
	FILE* m_f;
};

}


inline void cpy_reverse(char* dest, const char* src, Uint size);

int main(int argc, char** argv)
{
	const Uint print_times = 10;
	
	if( argc < 2 ) {
		fprintf(stderr, "usage: %s <word>\n", argv[0]);
		return -1;
	}

	const char* const word = argv[1];
	const Uint word_len = strlen(word);
	char* const buffer = static_cast<char*>( malloc(sizeof(char) * ( word_len + 1 )) );

	if(buffer == NULL) {
		perror("Failed to allocate memory: ");
		return -1;
	}

	const ScopeFree free_buffer( buffer );

	cpy_reverse(buffer, word, word_len);
	buffer[word_len] = '\0';

	for(Uint i = 0; i < print_times; ++i)
	{
		if( puts(buffer) == EOF ) {
			perror("puts failed: ");
			break;
		}
	}

	FILE* const file = fopen("savefile.txt", "w");
	if(file == NULL) {
		perror("failed to create savefile.txt: ");
		return -1;
	}

	const ScopeFClose close_file(file);

	fwrite(buffer, sizeof(char), word_len, file);
	if(ferror(file)) {
		perror("fwrite failed: ");
		return -1;
	}

	return 0;
}

inline void cpy_reverse(char* dest, const char* src, Uint size) {
	src += size-1;
	for( Uint i = 0 ; i < size ; ++i ) {
		*dest = *src;
		++dest;
		--src;
	}
}




