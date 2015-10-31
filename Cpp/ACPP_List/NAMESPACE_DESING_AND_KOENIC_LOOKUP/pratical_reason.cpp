#include <iostream>


// Koenic Lookup and Namespace Design

// Pratical Reason

int main(void)
{

	std::cout << "hi"; // this code only compiles because of Koenic Lookup

	// if there was no Koenic Lookup, we maybe had to do this as

	std::operator<<(std::cout, "hi"); // that is terrible.

	// so we have to begin to get used to see parameters as extensions of scope

}