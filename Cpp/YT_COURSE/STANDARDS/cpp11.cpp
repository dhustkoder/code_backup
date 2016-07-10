#include <iostream>
#include <vector>
#include <algorithm>
// C++11 CODE

using Uint = unsigned int;

inline Uint mystrlen(const char*);

int main(int argc, char** argv) 
{
	using std::cout;
	using std::cerr;
	
	try {
		
		constexpr Uint print_times = 10;
		
		if( argc < 2 ) {
			cerr << "usage: " << argv[0] <<  " <word>\n";
			return -1;
		}

		const auto buffer = [argv] {
			std::vector<char> tmp(argv[1], argv[1] + mystrlen(argv[1]));
			std::reverse(tmp.begin(), tmp.end());
			return tmp;
		}();

		for(Uint i = 0; i < print_times; ++i) {
			cout << buffer.data() << '\n';
		}

	}
	catch(std::exception& e) {
		cerr << "Fatal error: " << e.what() << '\n';
		return -1;
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
