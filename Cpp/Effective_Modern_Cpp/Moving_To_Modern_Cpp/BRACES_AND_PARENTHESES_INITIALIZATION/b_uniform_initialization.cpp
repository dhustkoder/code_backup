#include <iostream>
#include <vector>
#define LOG(x) std::cout << x << std::endl



int main()
{
	// Even with several initialization syntaxes, there were some situations where C++98 had no way
	// to express a desired initialization. For example:
	// It wasn't possible set of directly indicate that an STL container should be created holdng a particular
	// set of values

	// To addrss the confusion of ultiple initialization syntaxes as well as the fact
	// that they don't cover all initialization scenarios, C++11 introduces Uniform Initialization
	// It's based on Braces and for that reason Braced Initialization can be a better name for
	// pratical reasons

	// Braced initialization lets you express heformerly inexpressible. Using braces specifying
	// the initial contents of a container is easy:

	std::vector<int> vec {1, 3, 5};  //vec's initial contents : 1, 3, 5
	LOG("vec's ...");
	for(auto i : vec)
		LOG(i);

	
	// Braces can also be used to specify default initialization for non-static data members
	// this capability new to C++11 is shared with "=" initialization, but not with parentheses

	struct Widget
	{
		Widget(int w = 0) {LOG("default ctor!");}
		int x { 0 }; // fine
		int y = 0;   // fine
		//int z ( 0 ); // error
	};

	
	// On the other hand, uncopyable objects (e.g, std::atomic) or objects with
	// copy constructor defined, may be initialized
	// using braces or parentheses , but not using "=", even if it would call the same constructor...

	struct Uncopyable
	{
		Uncopyable(int) { LOG("Uncopyable default ctor"); } 
		Uncopyable(const Uncopyable&) = delete;
	}; 
	
	Uncopyable x { 0 }; // call default
	Uncopyable y (0);  // call default
	//Uncopyable z = 0; // error, but would have called default if the copy ctor wasn't deleted


	struct Copyable
	{
		Copyable(int)       { LOG("Copyable default ctor"); }
		Copyable(const Copyable&) {};
	
	};
	Copyable ca(0);
	Copyable cb{0};
	//Copyable cc = 0; // error, but would have called default ctor if copy ctor wasn't defined



	struct Normal
	{
		Normal(int) { LOG("Normal struct default ctor called!");}
		Normal(const Normal&) = default;


	};

	Normal na(0);
	Normal nb{0};
	Normal nc = 0; // call default ctor...



}
