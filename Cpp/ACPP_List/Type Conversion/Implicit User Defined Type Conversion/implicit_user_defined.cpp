#include <iostream>


class BigBoss
{
public:
	BigBoss(std::string name = "Jhon")
	{
		name_ = name;
		skills_ = "BigBoss Skills: A++, A++, A++, A++, A++";
	
	}
	// If you only want to define a contructor, and no implicit type conversion,
	// always put "explicit" before the constructor to avoid inadvertent type conversion.		
	const char* getProfile() { return std::string( name_ + "\n" + skills_ ).c_str(); }

	operator const char*() { return std::string( name_ + "\n" + skills_ ).c_str(); } // no need for getProfile anymore. 

private:
	std::string name_;
	std::string skills_;



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
	 *
	 *
	 *
	 *
	 *
	 *
	 *
	 */



	BigBoss boss(bossu); 


	std::cout << "\nusing function...\n" << std::endl;

	std::cout << boss.getProfile() << std::endl;

	std::cout << "\nusing implicit type conversion...\n" << std::endl;

	std::cout << boss << std::endl; // less code



}
