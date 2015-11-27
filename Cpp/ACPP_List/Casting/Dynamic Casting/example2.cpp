#include <iostream>

class Dog
{
public:
	virtual ~Dog()
	{};
};

class YellowDog : public Dog
{
protected:
	int age;
public:
	void bark()
	{
		std::cout << "woof." << std::endl; 

	}


};

class BlackDog : public YellowDog
{
public:
	void bark()
	{
		std::cout << "woof, I am " << age << std::endl;
	}
	

};


int main()
{

	Dog* pd = new Dog();

	YellowDog* py = dynamic_cast<YellowDog*>(pd);

	py->bark(); // well, this prints woof.
	// so it call the function correctly...
	
	// BUT
	std::cout << "pd = " << pd << std::endl; // this prints the objects address 
	
	std::cout << "py = " << py << std::endl; // and this prints 0

	// so the dynamic_cast didn't work, and py points to a null pointer. but the function was called...
	
	// What happens is that the compiler interprets the "bark" function as a static function cuz we called it from a null pointer and it doesnt access any
	// data member from Dog or YellowDog.


	// But BlackDog access the member age , lets try and see what happens
	
	BlackDog *pb = dynamic_cast<BlackDog*>(pd);

	pb->bark(); // what happens is undefined behavior for dereference a null pointer...
	




}
