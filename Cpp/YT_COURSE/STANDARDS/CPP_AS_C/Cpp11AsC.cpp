#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C++11 CODE



using Uint = unsigned int;

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

inline void cpy_reverse(char*, const char*, Uint size);

int main(int argc, char** argv)
{
	constexpr const Uint PRINT_TIMES = 10;
	
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

	const auto buffer_cleanup = MakeScopeExit([buffer] { 
		free(buffer);
		printf("buffer freed\n");
	});

	cpy_reverse(buffer, argv[1], word_len);
	buffer[word_len] = '\0';

	for(Uint i = 0; i < PRINT_TIMES; ++i) 
	{
		if( puts(buffer) == EOF ) {
			perror("puts failed: ");
			break;
		}
	}

	FILE* const file = fopen("savefile.txt", "w");
	
	if(file == nullptr) {
		perror("failed to create savefile.txt: ");
		return -1;
	}

	const auto close_file = MakeScopeExit([file] {
		fclose(file);
		printf("file closed\n");
	});

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
