#include <iostream>
#include <vector>
#include <algorithm>
// C++98 / C++03 CODE

typedef unsigned int Uint;

inline Uint mystrlen(const char*);
inline std::vector<char> CreateReverseVector(const char* str);

int main(int argc, char** argv) 
{
	using std::cout;
	using std::cerr;

	const Uint print_times = 10;
	
	if( argc < 2 ) {
		cerr << "usage: " << argv[0] <<  " <word>\n";
		return -1;
	}

	const std::vector<char> buffer = CreateReverseVector(argv[1]);

	for(Uint i = 0; i < print_times; ++i) {
		cout << buffer.data() << '\n';
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


std::vector<char> CreateReverseVector(const char* str) {
	std::vector<char> tmp ( str, str + mystrlen(str) );
	std::reverse(tmp.begin(), tmp.end();
	return tmp;
}
