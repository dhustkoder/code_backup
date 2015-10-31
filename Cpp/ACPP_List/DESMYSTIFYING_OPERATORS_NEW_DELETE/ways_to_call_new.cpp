#include <iostream>

class Test
{
public:
	Test() { std::cout << ": class Test constructed" << std::endl; }
};

#define LOG(x) std::cout << x << std::endl
int main(void)
{

	Test *test_ptr = nullptr, *test_ptr2 = nullptr, *test_ptr3 = nullptr;
	LOG(1);
	test_ptr = new Test();

	// 1. the common one: allocates memory by calling operator new (sizeof(Test)), 
	// and then call the object constructor and contruct the object in that newly allocated space.


	LOG(2);
	test_ptr2 = new(std::nothrow) Test(); 
	// same as above but calls operator new (sizeof(Test), std::nothrow) noexcept
	// does the same but do not throws an exception. if allocation fails returns a null pointer



	LOG(3);
	//test_ptr3 = (Test*) ::operator new (sizeof(Test));
	// allocates memory by calling: operator new (sizeof(Test))
	// but does not call Test's constructor



	LOG(4);

	new (test_ptr3) Test();
	// does not allocate memory -- calls: operator new (sizeof(Test), test_ptr3)
	// construct a object of type Test at test_ptr3



}