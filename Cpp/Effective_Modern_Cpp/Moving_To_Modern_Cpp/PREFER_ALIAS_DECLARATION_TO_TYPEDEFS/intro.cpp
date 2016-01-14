#include <iostream>
#include <unordered_map>
#include <list>
#include <memory>

template<typename T>
struct MyAlloc {}; // custom allocator, for example

void foo(std::string, int) {
	std::cout << "foooo" << std::endl;
}

int main()
{
	
	// I'm confident we can agree that using STL containers is a good idea,
	// and std::unique_ptr is a good idea too.

	// but it is not cool to be writing long namespaces prefixes all the time
	// like "std::unique_ptr<std::unordered_map<std::string, std::string>>".

	// we can avoid writing this long scentence with Typedefs
	//typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;

	// but typedefs are soo C++98, they work in C++11, sure, but C++11 also offers alias declaration

	using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;

	// given that the typedef and the alias declaration do exactly the same thing, its reasonable to wonder
	// whether there is a solid technical reason for preferring one over the other

	// There is... but before We get to it, is good to mention that many people find the alias declaration
	// easier to swallow when dealing with types involving function pointers

	// function pointer with typedef:
	typedef void(*FuncPtr1)(std::string, int);
	FuncPtr1 fptr = &foo;
	fptr("la", 0);
	// function pointer with alias declaration:
	using FuncPtr2 = void(*)(std::string, int);

	FuncPtr2 fptr2 = [](std::string, int) { std::cout << "lambdaaa" << std::endl;  };
	fptr2("la", 0);

	// of course, neither form is particularly easy to choke down, and few people
	// spend much time dealing with synonyms for function pointer types, anyway,
	// so this is hardly compelling reason to choose alias declaration over typedefs

	// But a compelling reason does exist: TEMPLATES. In particular,
	// alias declarations may be templatized (in which case they're called alias tempaltes),
	// while typedefs cannot

	// This gives C++11 programmers a straightforward mechanism for expressing things
	// that in C++98 had to be hacked together with typedefs nested inside templatized structs


	// For example, consider defining a synonym for a linked list that uses a custom allocator, MyAlloc, With an alias template
	// it's a piece of cake:



	// with alias declaration: 
	template<typename T>
	using MyAllocList = std::list<T, MyAlloc<T>>; // done

	MyAllocList<std::string> stringList; // client code


	// with a typedef, you pretty much have to create the cake from scratch:


	template<typename T>
	struct MyAllocList
	{
		typedef std::list<T, MyAlloc<T>> type;
	};

	MyAllocList<std::string>::type ls; // client code


}