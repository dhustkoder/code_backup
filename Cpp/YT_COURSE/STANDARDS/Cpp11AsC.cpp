#include <stdio.h>
#include <stdlib.h>
// C++11 CODE


typedef unsigned int Uint;

inline Uint mystrlen(const char*);
inline void cpyback(void*, const void*, Uint);

template<class F>
struct ScopeExit {
	ScopeExit(ScopeExit&&) = default;
	ScopeExit(F&& f) : m_f(static_cast<F&&>(f)) { }
	~ScopeExit() { m_f(); }
	F m_f;
};

template<class F>
inline ScopeExit<F> MakeScopeExit(F&& f) {
	return ScopeExit<F>(static_cast<F&&>(f));
}


int main(int argc, char** argv)
{
	constexpr const Uint PRINT_TIMES = 10;
	
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

	const auto buffer_cleanup = MakeScopeExit([=] {
		puts("WRITING BUFFER TO STDOUT");
		fwrite(buffer, sizeof(char), word_len, stdout);
		putchar('\n');
		free(buffer); 
	});


	cpyback(buffer, argv[1], word_len);
	buffer[word_len] = '\0';

	for(Uint i = 0; i < PRINT_TIMES; ++i) 
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
