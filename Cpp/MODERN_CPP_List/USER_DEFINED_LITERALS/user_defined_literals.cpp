#include <iostream>


// User Defined Literals



/*
	Literals are constants

	C++ has 4 kinds of literals:

		integer			--- 45
		floating point  --- 4.5
		character		--- 'z'
		string			--- "Dog"



*/

// Literals can have suffix to specify the exact type of the literal
void demo()
{
	auto a = 45u; // 45u and a are unsigned int

	auto b = 45l; // 45l and b  long

	auto c = 45ul; // 45ul and c are unsigned long

	auto d = 45ull; // 45ull and d are unsigned long long

	auto e = 45; // 45 and e are integers

	

}



// So user defined literals allow us to specify our own literals
long double operator"" _m(long double x) { return x * 1000; }
long double operator"" _cm(long double x) { return x * 10; }
long double operator"" _mm(long double x) { return x; }



constexpr unsigned long long operator"" _b(unsigned long long x) { return x; }
constexpr unsigned long long operator"" _kb(unsigned long long x) { return x * 1000; }
constexpr unsigned long long operator"" _mb(unsigned long long x) { return x * 1000000; }

// why do that?
int main()
{

	

	// user defined literals can make the code easier for a reader

	// C++98
	long double height = 40.7; // Meters ?, centimeters?, Inches? 


	// with user literals it can be easier
	auto a = 10.0_cm; // a is a long double and will recieve the return of operator"" _cm (10.0 * 10)

	// so all the conversions and representation is easier to read.

	std::cout << 1.0_m + 10.0_cm << std::endl;

	// but there conversions have RUN-TIME COST, what can we do ?
	
	// we can do constexpr operator""

	// these conversions are done by the compiler in compile time as our literal operator are constexpr
	
	auto b = 10_kb; // b is already == 10000

	auto small_pendrive_limit = 1024_mb; // small_pendrive_limit is already == 1024000000 GB

	std::cout << small_pendrive_limit << std::endl;


}