#include <iostream>



class Test
{

public:
	void useTest() {
		std::cout << "using a non-const Test" << std::endl;
	}

	void useTest() const {
		std::cout << "using a const Test" << std::endl;
	}
};


int main()
{

	Test t;
	const Test& ct = t;

	t.useTest();  // call non-const version of useTest
	ct.useTest(); // call const version of useTest

	const Test* ctptr = &t;
	ctptr->useTest(); // obvious also call const verson of useTest
}

