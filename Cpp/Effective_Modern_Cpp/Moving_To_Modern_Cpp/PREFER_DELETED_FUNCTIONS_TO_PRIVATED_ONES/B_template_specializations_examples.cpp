#include <type_traits>
// B prefer deleted functions over private ones

// Another trick that deleted functions can perform
// (and that private member functions can't) is to prevent
// use of template instantiations that should be disabled.

// For example, suppose you need a template that works with built-in pointers
template<typename T>
void processPointer(T* ptr) {
	// ...
}


// There are 2 special cases in the world of pointers.
// One is void* pointers, because there is no way
// to dereference them, to increment, or decrement them

// the other is char* pointers, because they typically represent pointers to C-style strings,
// not pointers to individual characters,

// we can do deleted specializations


template<>
void processPointer<char>(char*) = delete;

template<>
void processPointer<void>(void*) = delete;

// Now, if calling processPointer with void* or a char* is invalid,
// we don't want calls with const void* or const char* too, so,
// those instantiations will typically need to be deleted too


template<>
void processPointer<const char>(const char*) = delete;

template<>
void processPointer<const void>(const void*) = delete;

 //And if we really want to be thorough, we need also deleted
 //the const volatile void* and const volatile char*
 //and work won the overloads for pointers to the other standard character types:
 //std::wchar_t, std::char16_t, and std::char32_t

template<>
void processPointer<volatile char>(volatile char*) = delete;

template<>
void processPointer<volatile void>(volatile void*) = delete;

// const versions
template<>
void processPointer<const volatile char>(const volatile char*) = delete;

template<>
void processPointer<const volatile void>(const volatile void*) = delete;

//and so on...



// let's try a variadic template trick to avoid deleting these specializations
// one by one.
template<class T, class T2, class ...Ts>
struct is_one_of : std::conditional_t<std::is_same<T, T2>::value, std::true_type, is_one_of<T, Ts...>>
{
};

template<class T>
struct is_one_of<T,T> : std::true_type
{

};

template<class T, class T2>
struct is_one_of<T, T2> : std::false_type
{

};



// lets create another template processPointer to avoid conflicts with previous example
// so the code can compile
template<typename T>
void processPointer_2(T *ptr) // same thing as the frist
{

} 

// using is_one_of to help in processPointer_2:
// TA-DA, we deleted all desired specializations which we don't want to be usable
// in one single = delete, with the help of is_one_of
template<typename T>
std::enable_if_t<
	is_one_of<T, 
	char, const char, volatile char, const volatile char,
	void, const void, volatile void, const volatile void,
	wchar_t, const wchar_t, volatile wchar_t, const volatile wchar_t,
	char16_t, const char16_t, volatile char16_t, const volatile char16_t,
	char32_t, const char32_t, volatile char32_t, const volatile char32_t>::value >
	
	processPointer_2(T*) = delete; // one single '= delete' with all desired overloads to delete



int main()
{


}