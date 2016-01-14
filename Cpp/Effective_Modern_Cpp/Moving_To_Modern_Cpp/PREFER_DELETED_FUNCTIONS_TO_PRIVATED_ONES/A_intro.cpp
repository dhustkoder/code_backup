#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define TYPESTR(x) boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name()

// If you're providing code to other developers, and you want to prevent
// them from calling a particular function, generally just don't declare the function.

// But sometimes C++ declares functions for you, and if you want
// to prevent clients from calling those functions
// isn't quite so easy any more.



// This situation arises only for the special member functions.
// functions that C++ automatically generates when they're needed.
// now We'll be looking into Copy Constructor and Copy Assignment Operator.

// The C++98 approach to preventing use of these function is to declare
// them private and to avoid defining them.

// Near the base of the iostreams hierarchy in the C++ Standard Library is the class template basic_ios.
// All istream and ostrem classes inherit (possibly indirectly) from this class.

// Copying istreams and ostreams is undesirable, because it's not really clear what such operations
// should do. An istream object, represents a stream of input values
// some of which may have aleady been read, and some of which will potentially be read later.

// If an istream were to be copied, would that entail copying all the values that had already been read,
// as well as the values that would be read in the future ?
// the easiest way to deal with such questions is to define them out of existence
// prohibiting the copying of streams.

// To render istream and ostream class uncopyable, basic_ios is specified in
// C++98 as follows (including comments)

template<class charT, class traits = std::char_traits<charT> >
class basic_ios : public std::ios_base
{
public:
	//...
private:
	basic_ios(const basic_ios&);           // not defined
	basic_ios& operator=(const basic_ios&); // not defined
};

// declaring these functions private prevents clients from calling them.
// Deliberately failing to define them means that if code that still has access to them
// (member functions or friends of the class ) uses them, linking will fail due to missing function definitions

// In C++11, there's a better way to achieve essentially the same end: use "= delete"
// to mark the copy constructor and the copy assigment operator as deleted functions
// Here's the same parto of basic_ios as it's specified in C++11:
template<class charT, class trais = std::char_traits<charT> >
class basic_ios_cpp_11 : std::ios_base
{
public:
	// ...
	basic_ios_cpp_11(const basic_ios_cpp_11&) = delete;
	basic_ios_cpp_11& operator=(const basic_ios_cpp_11&) = delete;
};

// The difference between deleting these functions and declaring them private
// may seem more a metter, of fashion than anything else, but there's greater
// substance here than you might think.

// Deleted functions may not be used in any way, so even code thats in member and
// friend functions will fail to compile if it tries to copy basic_ios objects,
// thats an improvement over the C++98 behavior, where such improper usage wouldn't be
// diagnosed until link-time

// By convention, deleted functions are declared public, not private.
// There's a reason for that. When client code tries to use that
// member function,C++ checks accessibility for that, before deleted status,
// When client code tries to use a deleted private function, some compilers
// complain only about the function being private,
// even though the function's accessibiliy doesn't really affect whether it can be used.
// It's worth bearing this in mind when revising legacy code to replace private -and - not -defined
// member function, with deleted ones. because making the new function public will result in better
// error messages.


// An important advantage of deleted functions, is that any function may be deleted
// while only member functions may be private.
// For example, suppose we have a non-member function that takes an integer, and returns whether it's
// lucky number

bool isLucky(int number) {

}

// C++'s C heritage means that pretty much any type that can be viewed as vaguely
// numerical will implicitly convert to int, but some calls that would compile
// might not make sense:
void example() 
{
	
	if (isLucky('a'))  // is 'a' a lucky number ?
	{
		//...
	}

	if (isLucky(true)) // is "true" ?
	{
		//...
	}

	if (isLucky(3.5)) // should we truncate to 3, before cheking for luckiness ?
	{
		//...
	}
}

// if lucky numbers must really be integers, we'd like to prevents call
// such as these from compiling
// one way to accomplish that is to create deleted overloads for the types
// we want to filter out
bool isLucky(char) = delete;
bool isLucky(double) = delete;
bool isLucky(bool) = delete;

void example()
{

	if (isLucky('a'))  // won't compile, is a deleted function
	{
		//...
	}

	if (isLucky(true)) // won't compile is a deleted function
	{
		//...
	}

	if (isLucky(3.5)) // won't compile is a deleted function, rejects doubles and floats
	{
		//...
	}

	if (isLucky(3)) // fine
	{
		//...
	}
}

// the comment on the double overload, that says that both double and floats will
// be rejected may surprise you, but your surprise will dissipate once
// you recall that, given a choice between converting a float to an int or to a double,
// C++ prefers the conversion to double. Calling isLucky with a float will therefore call
// the double overload

// Although deleted functions can't be used, they're part of the program.
// As such they are taken into account durin overload resolution.
// That's why , with the deleted function declaration above, the undesirable calls will be rejected



int main()
{

}