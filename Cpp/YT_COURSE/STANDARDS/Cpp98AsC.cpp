#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// C++98 / C++03 CODE


typedef unsigned int Uint;

struct ScopeFree {
	ScopeFree(void* p) : m_p(p) { }
	~ScopeFree() { free(m_p); }
	void* const m_p;
};

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

	const ScopeFree buffer_cleanup( buffer );

	cpy_reverse(buffer, word, word_len);
	buffer[word_len] = '\0';

	for(Uint i = 0; i < print_times; ++i)
	{
		if( puts(buffer) == EOF ) 
		{
			perror("puts failed: ");
			return -1;
		}
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
