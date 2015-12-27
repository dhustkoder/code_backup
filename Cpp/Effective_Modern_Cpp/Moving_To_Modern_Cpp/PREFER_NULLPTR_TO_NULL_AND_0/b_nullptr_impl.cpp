#include <iostream>
#define LOG(x) std::cout << x << std::endl
	




// nullptr's advantage is that it doesn't have an integral type. To be honest
// it doesn't have an pointer type, either, but it behaves as a pointer of all types.
	
// nullptr actual type is std::nullptr_t and in a wonderfully circular definition,
// nullptr_t is defined to be the type of nullptr.
// nullptr_t implicity converts to all pointer types

	
// the implementation is something like this



class my_nullptr_t
{
public:
	
	my_nullptr_t() = default;	
	
	template<typename T>
	constexpr operator T*() const{        // convert to any pointer type
		return 0;
	}
	template<class C, typename T>
	constexpr operator T C::* () const{  // convert to any pointer to member type
		return 0;
	}

private:
	my_nullptr_t(const my_nullptr_t&) = delete;
	my_nullptr_t(my_nullptr_t&&) = delete;
			
	void operator +()                    = delete;
	void operator -()                    = delete;
	void operator =(const my_nullptr_t&) = delete;
	void operator *()                    = delete;
	void operator /(const my_nullptr_t&) = delete;
	void operator &()                    = delete;
	void operator ->()                   = delete;
	void *padding; // ensure the sizeof nullptr is the same as void*
};
#define my_nullptr (my_nullptr_t()) 
// make my_nullptr a rvalue


class SomeType
{
public:
	void foo() { LOG("member fun, int x: " << x);}
	int x;
};


int main()
{
	SomeType sometype;
	
	int *some_pointer = &sometype.x;                  // common pointer
	void(SomeType::*PtrToMemFunc)() = &SomeType::foo; // pointer to member

	*some_pointer =  300;           // uses common ptr
	(sometype.*PtrToMemFunc)();     // uses ptr to member func
	
	some_pointer = my_nullptr;      // assign nullptr; (uses convert to any pointer type: operator T*)
		
	PtrToMemFunc = my_nullptr;      // assign nullptr; (uses convert to any pointer to member type: operator T C::*)

	if(some_pointer == my_nullptr)  // again uses operator T*, and then compare the pointers
		LOG("ok its null"); 
	if(PtrToMemFunc == my_nullptr)  // again uses operator T C::*, and then compare the pointers
		LOG("ok its null too");	
	
}
