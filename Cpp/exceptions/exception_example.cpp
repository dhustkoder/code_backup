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

	std::cout << division(10,0) << std::endl;




}
