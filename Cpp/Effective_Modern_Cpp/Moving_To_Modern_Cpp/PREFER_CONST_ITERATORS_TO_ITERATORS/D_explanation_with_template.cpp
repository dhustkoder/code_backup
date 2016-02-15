#include <iostream>




class Test
{
public:
	void useTest() {
		std::cout << "using non-const Test" << std::endl;
	}

	void useTest() const {
		std::cout << "using const Test" << std::endl;
	}

};


// version for non-const
template<class T>
void USE(T& t) {
	t.useTest();
}

// version for const
template<class T>
void USE(const T& ct) {
	ct.useTest();
}


int main()
{
	Test t;
	const Test& ct = t;

	USE(t);
	USE(ct);



}










