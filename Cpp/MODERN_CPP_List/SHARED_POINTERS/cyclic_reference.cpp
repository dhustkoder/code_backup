#include <iostream>
#include <string>
#include <memory>

/* Cyclic Reference :
	
	There is a bad thing that can happen when using shared pointers whiout care: Cyclic Reference

	that happens when a object within a shared_ptr has a shared_ptr to himself or to another object that has a shared_ptr pointing back to the first one

	in other words forming a cycle of shared_ptr reference.

	but there is a cool solution: weak pointers... that I'll show in other folder.

*/

class Dog
{
	std::shared_ptr<Dog> m_friend;
	std::string m_name;
public:
	Dog(std::string name) : m_name(name) { std::cout << "Dog Constructed: " << m_name << std::endl; }
	void showFriend() { std::cout << "I'm " << m_name << ", and my friend is " << m_friend->m_name << std::endl; }
	void setFriend(std::shared_ptr<Dog> f) { m_friend = f; }
	~Dog() { std::cout << "Dog Destroyed: " << m_name << std::endl;  }
};

void foo()
{
	std::shared_ptr<Dog> dog1(new Dog("Mike"));
	std::shared_ptr<Dog> dog2(new Dog("Bambine"));

	dog1->setFriend(dog2); // now dog1 keeps dog2 alive, but when dog1 is destroyed, dog2 can be destroyed.

	dog2->setFriend(dog1); // oops, now dog2 keeps dog1 alive too, no one will be destroyed when out of scope, and memory will leak.

	// ----- 
	// we can do a simplier example like this:
	std::shared_ptr<Dog> dog(new Dog("loko dog"));
	dog->setFriend(dog); // this already forms a cycle.
	
}

int main()
{
	foo();


}