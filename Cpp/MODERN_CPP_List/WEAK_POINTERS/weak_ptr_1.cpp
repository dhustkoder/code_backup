#include <iostream>
#include <string>
#include <memory>



// a way to avoid Cyclic Reference with Shared Pointers , is using weak pointers


/* Weak Pointer: 

	std::weak_ptr is a smart pointer that holds a NON-OWNING("weak") reference to an object
	that may be managed by a std::shared_ptr, but weak_pointer does not have the responsability
	to delete the object whem he goes out of scope.


*/



struct Test_Wrong{

	std::shared_ptr<Test_Wrong> m_ptr;

	Test_Wrong() { std::cout << "created test wrong" << std::endl;}
	void foo() {std::cout << "using test wrong" << std::endl;}
	~Test_Wrong() { std::cout << "deleted test wrong" << std::endl;}
};


struct Test_Correct{
	std::weak_ptr<Test_Correct> m_ptr;
	
	Test_Correct() { std::cout << "created test correct" << std::endl;}
	void foo() {std::cout << "using test correct" << std::endl;}
	~Test_Correct() { std::cout << "deleted test correct" << std::endl;}	
};



void memory_leak(){
	std::shared_ptr<Test_Wrong> s_ptr(new Test_Wrong());
	
	s_ptr->m_ptr = s_ptr; // Cyclic reference, memoy will leak...
	
	s_ptr->foo();
}


void no_memory_leak(){
	std::shared_ptr<Test_Correct> s_ptr(new Test_Correct());
	
	s_ptr->m_ptr = s_ptr; // No Cyclic reference, cuz weak_ptr doesn't count as owner.

	s_ptr->foo();

}



int main(void)
{
	memory_leak();
	std::cout << "\n\n----------------------------------------\n" << std::endl;
	no_memory_leak();
}

