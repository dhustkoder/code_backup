#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define TYPESTR(x) boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name()


// PREFER SCOPED ENUMS TO UNSCOPED ENUMS

// It may seem that scoped enums have a third advantage over unscoped enums,
// because scoped enums may be forward-declared (their names may be declared,
// without specifying thei enumerators)

enum Color; //error
enum class Color; // fine

// this is mislewading. In C++11 , unscoped enums may also be forward-declared,
// but only after a bit of additional work;
// the work grows out the fact that every enum in C++ has a integral type that is determined by compilers.
// for an unscoped enum like color
enum Color {black, white, red};

// compilers might choose char as the underlying type, because there are only three values to represent.
// however, some enums have a range of values that is much larger:

enum Status {
	good = 0,
	incomplete = 100,
	corrupt = 200,
	indeterminate = 0xFFFFFFF
};

// Here the values to represent range from 0 to 0xFFFFFFF.
// except on unusual machines (where a char consists of at list 32 bits),
// compilers will have to select integral type larger than char for the representation of Status values


// To make efficient use of memory, compilers often want to choose the smallest
// underlying type for an enum that's sufficient to represent its range of enumerators values.

// In some cases, compilers will optimize for speed instead of size, and in that case,
// they may not choose the smallest permissible underlying type, but they certainly want
// to be able to optimize for size. To make that possible, C++98. supports only
// enum definitions ( where all enumerators are listed); enum declarations are not allowed.
// That makes it possible for compilers to select an underlying type for wach enum prior to the enum being
// used.

// But the inability to forward-declare enums has drawbacks. The most notable is
// probably the increase in compilation dependencies. Consider again the Status enum:

// That is the kind of enum that's likely to be used throughout a system, hence included
// in a header file that every part of the system is dependent on.
// if a new Status value is then introduced:

enum Status 
{
	good = 0,
	incomplete = 100,
	corrupt = 200,
	audited = 500, // new value
	indeterminate = 0xFFFFFFF
};

// It's likely that the entire system will have to be recompiled, even if only a single subsystem
// possibly only a single function! uses the new enumerator. This is the kind of thing people hate.

// And it's the kind of thing the ability to forward-declare enums in C++11 eliminates.

// For example, here's a perfectly valid delcaration of  a scoped enum and a function that takes one as parameter

enum class Status;// forward declaration
void continueProcessing(Status s); // use of fwd-declared enum

// the header containing these declarations requires no recompilation.
// If status definition is revised. Furthermore, if Status is modified (like add audited enumerator),
// but continueProcessing's behavior is unaffected( because continueProcessing doesn't use audited),
// continueProcessing's implementation need not be recompiled either

// But if compilers need to know the size of an enum before it's used, how can C++11's
// enums get away with forward declarations when C++98 cant ?

// Because: the underlying type for a scoped enum is always known, and for unscoped
// you can specify it.

// by default, the underlying type for scoped enums is int:
enum class Status; // underlying type is int

// if the default doesnt suit you, you can override it:
enum class Status : std::uint32_t; // Status is std::uint32_t from <cstdint>

// Either way, compilers know the size of the enumerators in a scoped enum

// To specify the underlying type for an unscoped enum, you do the same thing as for
// scoped enum, and the result may be forward-declared:
enum Color : std::uint8_t; // fwd decl for unscoded enum
                           // underlying type is uint8_t

// underlying type specifications can also go on enum definition
enum class Status : std::uint32_t
{
	good = 0,
	incomplete = 100,
	corrupt = 200,
	audited = 500, // new value
	indeterminate = 0xFFFFFFF
};

// In view of the fact that scoped enums avoid namespace pollution and aren't
// susceptible to nonsensical implicit type conversions, it may surprise you
// to heat that there's at least one situation where unscoped enums may be useful
// That's when referring to fields within c++11 std::tuples. For example,

// Suppose we have a typle holding values for the name, email. and reputation value for a user at a social
// network website
#include <tuple>
                            // name       // email   // reputation
using UserInfo = std::tuple<std::string, std::string, std::size_t>;
UserInfo getUserInfo(/*some user id*/) {
	// ... get informations
	return UserInfo{ "Leon S. Kennedy", "leonkennedy@gmail.com", 10 };
}


// Though the comments indicate what each field of the tuple represents,
// thats probably not very helpful when you encounter code like this in a separated source file:
void example()
{
	auto uInfo = getUserInfo(/*some user id*/);
	auto val = std::get<1>(uInfo);

	// as a programmer, we have a lot of stuff to keep track of.
	// should we really be expected to remember that field 1 corresponds to the user's email address?
	// I thing not. Using unscoped enum to associate names with fields numers avoid the need to:
	enum UserInfoFields {uiName, uiEmail, uiReputation};

	auto uInfo2 = getUserInfo(/* some user id*/);
	auto val = std::get<uiEmail>(uInfo2);

	// What makes this work is the implicit conversion from UserInfoFields to std::size_t
	// which is the type that std::get requires

	// The corresponding code with scoped enums is substantially more verbose:

}
// The corresponding code with scoped enums is substantially more verbose:

void example2()
{
	enum class UserInfoFields {uiName, uiEmail, uiReputation};
	auto uInfo = getUserInfo(/*some user id*/); // as before

	auto val = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo);

	// this verbosity can be reduced by writting a function that takes an enumerator and
	// returns it corresponding std::size_t value, but its a bit tricky
	// std:;get is a template, and the value you provide is a template argument,
	// so the function that transforms an enumerator into std::size_t has to produce its result
	// during compilation.
	// it must be a constexpr function
}
// in fact it should really be a constexpr function template, because it should work
// with any kind of enum. And if we're going to make that generalization, we should
// generalize the return type, too. Rather than returning std::size_t, we'll return
// the enum's underlying type. Its available via the std::underlying_type type trait;

template<typename T>
constexpr std::underlying_type_t<T> toUType(T enumerator) noexcept
{
	return static_cast<std::underlying_type_t<T>>(enumerator);
}

void example3()
{
	enum class UserInfoFields { uiName, uiEmail, uiReputation };
	auto uInfo = getUserInfo(/*some user id*/); // as before

	auto val = std::get<toUType(UserInfoFields::uiEmail)>(uInfo);

	// It's still more to write than use of unscoped enum, but it also
	// avoids namespace pollution and inadvertent conversions involving enumerators.
	// Int many cases you may decide that typing a few extra characters is reasonable price
	// to pay for the ability to avoid the pitfalls of an old enum technology;
}



int main()
{



}