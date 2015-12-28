#include <iostream>


#define LOG(x) std::cout << x << std::endl




// When users of a complex system are ignorant of how it works, yet 
// happy with what it does, that says a lot about the design of the system.


// By measure , template type deduction in C++ is a tremendous success
// Millions of programmers have passed arguments to template functions with completely
// satisfactory results, even though many of those programmers would be hard pressed
// to give more than the haziest desciption of how the types used by those functions were deduced

// type deduction for templates is the basis for one of modern C++'s most compelling
// features: auto. 


// Too bad that when the template type deduction rules are applied in the context of auto,
// they sometimes seem less intuitive than when they're applied to templates.


// For that reason It's really important to truly understand the aspects of template type deduction that auto builds on.



// when we look at a simple template function we can look at it like this
template<typename T> 
void foo(ParamType param);

// a call can be looked like this

foo(expr);      // call  f with some expression


// During compilation, compilers use 'expr' (the given expression) to deduce 2 types -
// One type for T and other for ParamType

// These types are frequently different, because ParamType often is type T with some adornments. (const or reference among other qualifiers).

// For example, if the template is declared like this:

template<typename T>
void foo(const T& param); 	// ParamType is const T&

int main()
{
	int x = 0;
	foo(x);					// call f with an int

	// T is deduced to be INT, but ParamType is deduced to be const int&

	// It's natural to expect that the type deduced for T is the same as the type of the argument
	// passed to the function. T is the type of expr.

	// in this example T is the type of X which in INT. But it doesn't always work that way. The 
	// Type deduced for T is dependent not just on the type of expr, but also on the form of ParamType.
	
}
