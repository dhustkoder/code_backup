#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
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

		const auto reverse_word = [argv] {
			std::string tmp(argv[1]);
			std::reverse(tmp.begin(), tmp.end());
			return tmp;
		}();


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
		cerr << "Fatal Exception: " << e.what() << '\n';
		return -1;
	}

	return 0;
}
