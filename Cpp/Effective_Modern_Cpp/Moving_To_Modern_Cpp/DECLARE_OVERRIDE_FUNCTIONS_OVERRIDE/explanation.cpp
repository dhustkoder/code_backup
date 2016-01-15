#include <iostream>
#include <boost/type_index.hpp>
#include <memory>
#define LOG(x) std::cout << x << std::endl
#define TYPESTR(x) boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name()


// Declare overriding functions override

// The world of object-oriented programming in C++ revolves
// around classes, inheritance, and virtual functions.
// Among the most fundamental ideas in this world is that
// virtual function implementations in derived classes override
// the implementations of their base class counterparts.

// It's disheartening, then, to realize just how easily
// virtual function overriding can go wrong.

// Because "overriding" sounds like "overloading", yet is completely unrelated,
// let us clear that make it clear that virtual function overriding is what makes it possible to 
// invoke a derived class function through a base class interface:

class Base {
public:
	virtual void doWork() { std::cout << "Base work" << std::endl; }
};
class Derived : public Base {
public:
	// overrides Base::doWork, virtual is optional here
	virtual void doWork() { std::cout << "Derived work" << std::endl; }
	//...
};

void virtualOverridingExample() {
	std::unique_ptr<Base> Uptr = std::make_unique<Derived>();

	Uptr->doWork();
	// call doWork through Base clas ptr; 
	// invokes Derived function doWork
}

// for this kind of overriding occur , some requirements must be met:

// - The base class function must be virtual
// - Base and Derived function names must be identical (except in case of virtual Destructors)
// - The parameter types of the base and derived functions must be identical
// - The constness of the base and derived function must be identical
// - The return types and exception specifications of the base and derived function must be compatible

// To these constraints, which were also parto of C++98 . C++11 add one more
// - The function's reference qualifiers must be identical.

// The function reference qualifier are one of C++11 less-publicized features.
// don't be surprised if you never heard of it.

// They make possible to limit use of a membe function
// to lvalues only or to rvalues only.
// member function need not be virtual to use them

class Widget 
{
public:
	void doWork() & // version called when *this is a lvalue
	{
		LOG("doWork: called by lvalue object");
	}

	void doWork() && // version called when *this is rvalue
	{
		LOG("doWork: called by rvalue object");
	}
};

Widget makeWidget()  // factory function, returns rvalue
{
	return Widget();
}

void functionReferenceQualifierExample()
{
	Widget w; // lvalue 
	w.doWork(); // call lvalue version
	makeWidget().doWork(); // call rvalue version
}

// We'll see more about member function with reference qualifiers later,
// but now, simply note that if a virtual function in a base classe has
// a reference qualifier, derived class overrides of that function must have exactly the same
// reference qualifier, if they don't, the declared function will still exist
// in the derived class, but they won't override anything in the base class.


// All these requirements for overriding mean that small mistakes
// can make a big difference. Code containing overriding erros is typically valid
// but its meaning isn't what we intended.
// You therefore can't rely on compilers to notifying you if you do something wrong
// . For example, h following code is completelyy legal and, at first sight
// looks reasonable, but it constaines no virtual function overrides-- not a single
// derived class function that is tied to a base class function
// Why each derived class function doesn't override the base class function
// of the same name ?

class _Base
{
public:
	virtual void mf1() const
	{
		LOG("mf1: Base");
	}

	virtual void mf2(int x) 
	{
		LOG("mf2: Base");
	}

	virtual void mf3() & 
	{ 
		LOG("mf3: Base"); 
	}
	void mf4() const 
	{
		LOG("mf4: Base");
	}
};


class _Derived : public _Base
{
public:
	virtual void mf1() // doesn't overrides Base::mf1 because is not the same const qualifier
	{
		LOG("mf1: Derived");
	}
	virtual void mf2(unsigned int x) // doesn't overrides Base::mf2: not the same parameter type
	{
		LOG("mf2: Derived");
	}
	virtual void mf3() && // not the same reference qualifier...
	{
		LOG("mf3: Derived");
	}
	void mf4() const // isn't virtual in base class
	{
		LOG("mf4: Derived");
	}
};

// compilers can generate warnings about that , but will compile

// but in C++11 we have a way to make explicit that a derived
// class function must override a base class function

// declaring them override...
class _Derived2 : public _Base
{
public:
	virtual void mf1() override
	{
		LOG("mf1: Derived");
	}
	virtual void mf2(unsigned int x) override
	{
		LOG("mf2: Derived");
	}
	virtual void mf3() && override
	{
		LOG("mf3: Derived");
	}
	void mf4() const override
	{
		LOG("mf4: Derived");
	}
};

// now this code doesn't compile, because the function aren't overriding anything...
// and will generate errors telling us that.


int main()
{
	//virtualOverridingExample();
	functionReferenceQualifierExample();
}