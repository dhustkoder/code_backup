#include <iostream>
#include <string>
#include <memory>
#define LOG(x) std::cout << x << std::endl



class Dog{

public:
	Dog(std::string name) : m_name(name){
		LOG("Dog " << name << ", is Created.");
	}

	~Dog(){
		LOG("Dog " << m_name << ", is Destroyed...");
	}

	
	void bark(){ 
		LOG("Dog " << m_name << ", is Barking!!");
	}

	void setFriend(std::shared_ptr<Dog> f){
		m_friend = f;
	}

	void showFriend(){
		if(m_friend.expired()) // test if m_friend is not valid
			return;

		LOG("I'm " << m_name << ", and this is my friend: " << m_friend.lock()->m_name << "!");
	}
	
private:
	std::weak_ptr<Dog> m_friend;
	std::string m_name;
};



void no_memory_leak()
{
	std::shared_ptr<Dog> dog1 = std::make_shared<Dog>("DogMeat");
	std::shared_ptr<Dog> dog2 = std::make_shared<Dog>("D-Dog");

	dog1->setFriend(dog2);
	dog2->setFriend(dog1);

	dog1->showFriend();
	dog2->showFriend();

}



int main()
{
	no_memory_leak();
	/* Output:
			Dog DogMeat, is Created.
			Dog D-Dog, is Created.
			I'm DogMeat, and this is my friend: D-Dog!
			I'm D-Dog, and this is my friend: DogMeat!
			Dog D-Dog, is Destroyed...
			Dog DogMeat, is Destroyed...
	*/
}