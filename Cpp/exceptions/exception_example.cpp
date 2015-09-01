#include <iostream>
#include <typeinfo>




double division(double a, double b)
{

	if(b == 0)
		throw "Division By Zero";

	return (a/b);




}

int main()
{
	int x = 100 , y = 0;
	double result = 0;

	try
	{
		result = division(x, y);
		std::cout << result << std::endl;
	}
	catch(const char *msg)
	{
		std::cerr << msg << std::endl;
	
	}
	
	return 0;


}
