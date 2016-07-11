#include <iostream>
#include <string>
#include <algorithm>
// C++98 / C++03 CODE

typedef unsigned int Uint;

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

		std::string word(argv[1]);
		std::reverse(word.begin(), word.end());

		for(Uint i = 0; i < print_times; ++i)
			cout << word << '\n';
	}
	catch(std::exception& e) {
		cerr << "fatal error: " << e.what() << '\n';
		return -1;
	}

	return 0;
}
