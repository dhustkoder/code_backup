#include <stdio.h>
#include <stdlib.h>

// C++98 CODE


typedef unsigned int Uint;

Uint mystrlen(const char*);
void cpyback(void*, const void*, Uint);


struct Buffer 
{
	Buffer() 
		: data(NULL) 
	{
 
	}
	
	Buffer(Uint size) 
	{ 
		data = static_cast<char*>(malloc( sizeof(char) * size) );
	}
	
	~Buffer() { free(data); }
	operator char*() { return data; }
	bool operator==(void* p) const { return data == p; }

	char* data;
};





int main(int argc, char** argv)
{
	const Uint print_times = 10;
	
	if( argc < 2 ) {
		fprintf(stderr, "usage: %s <word>\n", argv[0]);
		return -1;
	}

	const Uint word_len = mystrlen(argv[1]);
	Buffer buffer ( word_len + 1 );

	if(buffer == NULL) {
		perror("Failed to allocate memory: ");
		return -1;
	}

	cpyback(buffer, argv[1], word_len);
	buffer[word_len] = '\0';

	for(Uint i = 0; i < print_times; ++i) {
		puts(buffer);
	}

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
