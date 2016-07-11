#include <iostream>
#include <string>
#include <algorithm>
// C++11 CODE

using Uint = unsigned int;

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

		const auto word = [argv] {
			std::string tmp(argv[1]);
			std::reverse(tmp.begin(), tmp.end());
			return tmp;
		}();

		for(Uint i = 0; i < print_times; ++i)
			cout << word << '\n';
	}
	catch(std::exception& e) {
		cerr << "Fatal error: " << e.what() << '\n';
		return -1;
	}

	return 0;
}
