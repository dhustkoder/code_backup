#include <iostream>
#include <memory>




class Dog
{
public:
	Dog(std::string name) : m_name(std::move(name))
	{
		std::cout << m_name << " is born!" << std::endl ;
		bark(); // this will call the base class Dog version of bark always, cause the child classes are not constructor yet.

		// constructors must be used just to put the class in a usable state.
	
	}
	
	virtual void bark()
	{
		std::cout << "I'm a Dog!!" << std::endl;
	}
	
	void seeCat()
	{
		bark();
	}

	~Dog()
	{
		std::cout << m_name << " (Dog) is destroyed" << std::endl;

		bark(); // this will also call always the base class version of bark, cause normally the child classes are destroyed before the base class.
	}



protected:
	std::string m_name;		



};


class YellowDog : public Dog
{
friend class DogFactory;
	YellowDog(std::string name) : Dog(std::move(name))
	{
	}
public:
	virtual void bark()
	{
		std::cout << "I'm a Yellow Dog!!" << std::endl;
	}
	~YellowDog()
	{
		std::cout << m_name << " (YellowDog) is destroyed" << std::endl;
	}

};

class DogFactory 
{
public:
	static std::shared_ptr<Dog> CreateYellowDog(std::string name)
	{
		return std::shared_ptr<YellowDog> (new YellowDog(std::move(name)));
	}





};

int main()
{

	std::shared_ptr<Dog> yellow_dog = DogFactory::CreateYellowDog("Pitoco");
	/*
	 * OUTPUT: 
	 * 	Pitoco is born!
	 * 	I'm a Dog!!
	 * 	Pitoco (YellowDog) is Destroyed
	 *
	 *
	 * */

	// Why the bark on constructor did not call the YellowDog bark version ?? 
	// 	 	Cause the YellowDog was not constructed yet. the Base Class are constructed first. just after that the YellowDog is constructed and can be used.
	//
	// 	So, do not overuse the Constructor. It should be used just to put the class in a usable state, not more.
	//
	// Also will the bark() in the base class destructor call the base class version of bark(); cause the child classes normally is already destroyed when 
	// the base class's destructor is called.
}

