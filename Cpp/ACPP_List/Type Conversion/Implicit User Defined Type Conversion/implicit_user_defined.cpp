#include <iostream>


class BigBoss
{
public:
	explicit BigBoss(std::string name = "Jhon")
	{
		name_ = name;
		skills_ = "BigBoss Skills: A++, A++, A++, A++, A++";
	
	}
	// If you only want to define a contructor, and no implicit type conversion,
	// always put "explicit" before the constructor to avoid inadvertent type conversion.		
	
	
	
	const char* getProfile() { return std::string( name_ + "\n" + skills_ ).c_str(); } // get the data you need, using member function

	
	
	
	operator const char*() { return std::string( name_ + "\n" + skills_ ).c_str(); } 
	// no need for getProfile anymore. this get the data automaticaly
	// when BigBoss object is used in a context that ask for const char* type.
	
	
	
	~BigBoss() { std::cout << "This is good... isn't it ?" << std::endl; }
private:
	std::string name_;
	std::string skills_;



};

class Ocelot
{
public:
	Ocelot(std::string name = "Revolver Ocelot")
	{
		name_ = name;
	}
	void speak() {std::cout << "My name is " << name_ << ", and you're pretty good!" << std::endl ;}
	~Ocelot() { std::cout << "YOU FILTHY AMERICAN DOG!" << std::endl; }
private:
	std::string name_;


};


int main()
{

	/* User Defined Type Conversion.
	 * These are defined inside a class or struct
	 *
	 * just like that, imagine I want to get the main std::string, that represent BigBoss object
	 * 
	 * well , sometimes is better not to use it, some other times might be good to use, for math operations for example.
	 *
	 */


	// Method 1: Use contructor to convert other types into your class.
	std::cout << "Method 1. using constructor to convert other types into your class\n" << std::endl;
	
  	//BigBoss nakedSnake = std::string("Naked Snake");
	//std::cout << nakedSnake << std::endl;

	// I can't do this with BigBoss, cuz BigBoss's constructor have explicit keyword that wont let me do that.

	// But Ocelot class can do that.
	
	Ocelot shalashaska  = std::string("Adamska");
	shalashaska.speak(); // his name is Adamska

	shalashaska = std::string("Revolver");

	shalashaska.speak(); // now his name is Revolver

	// cool, It's like you can REconstruct your class, but becareful that destructor will be called when you "Reconstruct" the class
	


	//Method 2: Convert your class's object into another type, use a function to get a data of that type, or use a type conversion function to do that automaticaly	
	
	std::cout << "\nMethod 2: using a member function to get the data you need, OR using a type conversion function that do that automaticaly\n" << std::endl;

	BigBoss boss; 


	std::cout << "\nusing function...\n" << std::endl;

	std::cout << boss.getProfile() << std::endl;

	std::cout << "\nusing implicit type conversion...\n" << std::endl;

	std::cout << boss << std::endl; // less code

	
}
