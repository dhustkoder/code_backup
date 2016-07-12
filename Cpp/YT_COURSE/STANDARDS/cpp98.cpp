#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
// C++98 / C++03 CODE

typedef unsigned int Uint;

namespace {
inline std::string CreateReverseString(const char* const str);
}

int main(int argc, char** argv) 
{
	using std::cout;
	using std::cerr;

	try {

		const Uint print_times = 10;
		
		if( argc < 2 ) {
			cerr << "usage: " << argv[0] <<  " <word>\n";
			return -1;
		}

		std::string reverse_word = CreateReverseString(argv[1]);

		try {
			for(Uint i = 0; i < print_times; ++i)
				cout << reverse_word << '\n';
		}
		catch(std::exception& e) {
			cerr << "cout failed: " << e.what() << '\n';
		}

		std::ofstream file("savefile.txt");
		if(file.good() == false)
			throw std::runtime_error("failed to create savefile.txt");

		file << reverse_word;
	}
	catch(std::exception& e) {
		cerr << "fatal error: " << e.what() << '\n';
		return -1;
	}

	return 0;
}


namespace {

inline std::string CreateReverseString(const char* const str) {
	std::string tmp(str);
	std::reverse(tmp.begin(), tmp.end());
	return tmp;
}



}