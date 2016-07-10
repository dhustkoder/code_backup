#include <stdio.h>
#include <stdlib.h>
// C++98 / C++03 CODE


typedef unsigned int Uint;

inline Uint mystrlen(const char*);
inline void cpyback(void*, const void*, Uint);

int main(int argc, char** argv)
{
	const Uint print_times = 10;
	
	if( argc < 2 ) {
		fprintf(stderr, "usage: %s <word>\n", argv[0]);
		return -1;
	}

	const Uint word_len = mystrlen(argv[1]);
	char* const buffer = static_cast<char*>( malloc(sizeof(char) * ( word_len + 1 )) );

	if(buffer == NULL) {
		perror("Failed to allocate memory: ");
		return -1;
	}	

	// Clean buffer on scope exit
	const struct BufferGuard {
		BufferGuard(char* buffer, Uint len) : m_buff(buffer), m_len(len) {}
		~BufferGuard() {
			puts("WRITING BUFFER TO STDOUT");
			fwrite(m_buff, sizeof(char), m_len, stdout);
			putchar('\n');
			free(m_buff); 
		}
		char* const m_buff; 
		Uint m_len;
	}buffer_guard(buffer, word_len);



	cpyback(buffer, argv[1], word_len);
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





inline Uint mystrlen(const char* str) {
	Uint len = 0;
	
	while( *str != '\0' ) {
		++len;
		++str;
	}

	return len;
}


inline void cpyback(void* dest, const void* src, Uint size) {
	char* _dest = static_cast<char*>(dest);
	const char* _src = static_cast<const char*>(src);
	_src += size-1;

	for( Uint i = 0 ; i < size ; ++i ) {
		*_dest++ = *_src--;	
	}

}
