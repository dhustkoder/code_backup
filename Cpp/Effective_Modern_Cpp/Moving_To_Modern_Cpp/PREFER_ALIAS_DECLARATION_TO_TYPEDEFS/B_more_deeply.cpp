#include <iostream>
#include <unordered_map>
#include <list>
#include <memory>

template<typename T>
using MyAlloc = std::allocator<T>; // for using MyAlloc as example



//using alias declaration:
template<typename T>
using MyAllocList1 = std::list<T, MyAlloc<T>>;


MyAllocList1<std::string> stringList1; // client code


// using typedef:
template<typename T>
struct MyAllocList2
{
	typedef std::list<T, MyAlloc<T>> type;
};

MyAllocList2<std::string>::type stringList; // client code


// as you can see, using alias declaration result in simplier code.

// but using typedefs with templates get worse.
// If you want to use the typedef inside a template for the purpose of ceating
// a linked list holding objects of a type specified by a template parameter, 
// you have to precede the typedef name with typename:

template<typename T>
class Widget
{
private:
	// using alias declared MyAllocList:
	MyAllocList1<T> listT1; // ok, no need for typename or ::type


	// using typedef declared MyAllocList
	//MyAllocList2<T>::type listT_error; // error

	typename MyAllocList2<T>::type listT2; // ok


	// here , MyAllocList2<T>::type refers to a type that's dependent on a template type
	// parameter (T). MyAllocList2<T>::type is thus a dependent type, and no one
	// of C++'s many endearing rules is that the names of dependent types must be
	// preceded by typename


	// MyAllocList1 is defined as an alias template, this need for typename vanishes 
	// (as does the cumbersome “::type” suffix):



	// To you, MyAllocList1<T> (using alias template) may look just as dependent
	// on the template parameter T, as MyAllocList2 (using nested typedef).
	// But you're not the compiler.

	// When the compiler process the Widget template and encounter the use of
	// MyAllocList1<T>(using alias template), they know that MyAllocList1<T> is the name
	// of a type, because MyAllocList1 is an alias template: It Must name a type,
	// so MyAllocList1<T> is thus a non-dependent type, and a typename specifier is neither required
	// nor permitted.



	// When the compiler see MyAllocList2<T>::type (the use of nested typedef)
	// in the widget template, on the other hand, they can't know for sure
	// that it names a type, because there might be a specialization of MyAllocList2 that they haven't yet seen,
	// where MyAllocList2<T>::type refers to something other than a type. That sounds creazy,
	// but don't blame the compilers for this possibility, It's humans who have been known
	// to produce such code.
};

// For example some misguided souls may have concocted something like this:
class Wine {};
template<>
struct MyAllocList2<Wine>
{
private:
	enum class WineType
	{ White, Red, Rose };
	WineType type; // here type is a data member
};


// as you can see, MyAllocList<Wine>::type doesn't refer toa type.

// If Widget were to be instantiated with Wine, MyAllocList<T>::type inside the Widget template
// would refer to a data member, not a type.
// Inside the Widget template, then, whether MyAllocList2<T>::type refers to a type is honestly dependent on
// what T is, and that's why compilers insist on your asserting that it is a type by preceding it with typename


// If you've done any template metaprogramming (TMP), you've almost certainly bumped up
// against the need to take template type parameters and create revised types from them
// For example, given some type T, you might want to turn const std::string& into std::string.
// or might want to add const to a type or turn it into an lvalue refernce , etc...

// If you haven't done any TMP thats too bad, because if you want to be a truly effective
// C++ programmer, you need to be familiar with at least the basics of this facet of C++.



int main()
{



}