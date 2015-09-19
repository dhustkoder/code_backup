#include <iostream>


class BigBoss
{
public:
	BigBoss()
	{
		skills_ = "BigBoss Skills: A++, A++, A++, A++, A++";
	
	}		
	operator const char*() { return skills_.c_str(); } 

private:
	std::string skills_;



};






int main()
{

	// User Defined Type Conversion.









	BigBoss boss; 
	std::cout << boss << std::endl;





}
