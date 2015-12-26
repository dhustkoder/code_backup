#include <iostream>
#define LOG(x) std::cout << x << std::endl

void* findRecord()
{
	return nullptr;
}







void f(int)
{
	LOG("F int called");
}

void f(bool)
{
	LOG("F bool called");
}

void f(void*)
{
	LOG("F void* called");
}

void f(int*)
{
	LOG("F int*");
}

int main()
{
	// so, 0 is a int not a pointer that is why is not what you want
	// nullptr its a macro that can be 0, 0L, and I've seen in MSVC as ((void*)0) which I think its a better than 0

	
	f((void*)0); // calls f(void*)
	f(0);        // calls f(int)
	//f(nullptr);     // in clang and gcc its ambiguos between all f functions
 
	//f(nullptr); // calls its ambiguos between  f(void*) and f(int*) -
	// because nullptr is a pointer of all types will aways be ambiguos between overloads of pointer types

	f((int*)nullptr); // call f(int*)


	// using nullptr in most cases can avoid overload resolution surprises ,
	// but that is not the only advantage, it also improve code clarity,
	// specially when auto variables are involved. look this

	auto result = findRecord(/* arguments */);
	// if you don't happen to know or can't easily find the type of result...
	// then you see

	if(result != nullptr)
		return 0; // oh result cleary is a pointer

	if(result != 0)   // what is result pointer or integer ?
		return 0;

	if(result != nullptr) // must be a pointer... but can be an integer
		return 0;


	int number = nullptr; // error so nullptr only can be assigned to ptrs






	


}
