#include <iostream>


class BigBoss
{
public:
	BigBoss()
	{
		skills_ = "BigBoss Skills: A++, A++, A++, A++, A++";
	
	}		
	const char* getSkills() { return skills_.c_str(); }
	operator const char*() { return skills_.c_str(); } // no need for getSkills anymore. 

private:
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



	BigBoss boss; 
	std::cout << boss.getSkills() << std::endl;
	std::cout << boss << std::endl; // less code



}
