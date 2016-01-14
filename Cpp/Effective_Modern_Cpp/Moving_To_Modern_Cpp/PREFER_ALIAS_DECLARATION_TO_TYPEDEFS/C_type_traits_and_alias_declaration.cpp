#include <iostream>
#include <type_traits>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define TYPESTR(x) boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name()
// C++11 gives you the tools to perform these kinds of transformations
// in the form of type traits, an assortment of templates inside the header
// <type_traits>.

// There are dozens of type traits in that header, and not all of them perform
// type transformations, but the ones that do offer a predictable interface.
// Given a type T to which you'd like to apply a transformation, the resulting type is,
// std::transformation<T>::type. for example:

const int x = 100;
std::remove_const<decltype(x)>::type non_const_x; // yields int from const int
const int& reference_to_x = x;
std::remove_reference<decltype(reference_to_x)>::type non_reference_x = 200; // yields const int from const int& or const int&&
std::add_lvalue_reference<decltype(non_reference_x)>::type reference_to_non_reference_x = non_reference_x; // yields const int& from const int
void showTypes() {
	LOG("x: " << TYPESTR(x));
	LOG("non_const_x: " << TYPESTR(non_const_x));
	LOG("reference_to_x: " << TYPESTR(reference_to_x));
	LOG("non_reference_x: " << TYPESTR(non_reference_x));
	LOG("reference_to_non_reference_x2: " << TYPESTR(reference_to_non_reference_x));

}

// The comments merely summarize what these transformations fo, so don't take them too literally
// Before using them on a project, you'd look up the precise specifications.


// Our goal is not a tutorial on type_traits, anyway.
// Note the  ::type at the end of each type_trait template 
// If we apply them to a type parameter inside a template ,
// we'd have to proced every use with 'typename'
// The reason for both of these syntatic speed bumps is that the C++11 type traits
// are implemented as nested typedefs inside templatized structs.

// That's right, they're implemented using the type synonum technology I've been trying to convinve
// you is inferior to alias templates.

// There's a historical reason for that, but we'll skip over it.
// Because the Standardization Committee belatedly recognized that alias templates
// are the better way to go, and they included such templates in C++14 for all the C++11 type transformations
// The alias have a common form: or each C++11 transformation std::transformation<T>::type,
// there's a corresponding C++14 alias template named std::transformation_t 
// Examples:

const int x2 = 100;
std::remove_const_t<decltype(x2)> non_const_x2; // yields int from const int
const int& reference_to_x2 = x2;
std::remove_reference_t<decltype(reference_to_x2)> non_reference_x2 = 200; // yields const int from const int& or const int&&
std::add_lvalue_reference_t<decltype(non_reference_x2)> reference_to_non_reference_x2 = non_reference_x2; // yields const int& from const int

// no need for ::type 
template<typename T>
class Widget
{
private:
	typename std::add_const<T>::type _constT;
	std::add_const_t<T> __constT; // no need for typename and ::type
};

// The C++11 constructs remain valid in C++14, but I don't know why you'd want 
// to use them. Even if you don't have access to C++14, writting the alias templates
// yourself is child's play, only C++11 language features are required, and even children
// can mimic a pattern, right ?



int main()
{
	showTypes();


}