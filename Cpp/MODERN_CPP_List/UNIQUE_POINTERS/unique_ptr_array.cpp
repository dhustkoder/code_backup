#include <iostream>
#include <string>
#include <memory>
#define LOG(x) std::cout << x << std::endl

class Dog
{
public:
	Dog(std::string name = "nameless") : m_name(name) {
		LOG("Creating Dog: " << name);
	}

	void bark() {
		LOG("Dog: " << m_name << ", is barking!!");
	}

	~Dog() {
		LOG("Destroying Dog: " << m_name);
	}
private:
	std::string m_name;
};


void example_1()
{
	// if we were to use arrays with shared pointers, we have to give an custom deleter.
	std::shared_ptr<Dog> s_pD(new Dog[4],[](Dog *dogArr)
	{
		LOG("\n\ncustom deleting dog for shared ptr\n\n");
		delete[] dogArr;
	});
	s_pD.get()[3].bark();


	// but for UNIQUE pointers, we can simply pass the template argument telling that we want array deleter
	std::unique_ptr<Dog[]> u_pD(new Dog[4]);
	u_pD[3].bark();
}



int main()
{
	example_1();

}

