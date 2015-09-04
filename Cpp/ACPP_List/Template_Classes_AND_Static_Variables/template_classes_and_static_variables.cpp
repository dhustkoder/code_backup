#include <iostream>





template<typename T>
class Test
{
public:
	static int Static_Variable;
	Test()
	{
		Static_Variable++;
	}



};
template<typename T>
int Test<T>::Static_Variable = 0;




int main()
{
	Test<int> a;
	Test<int> a2;

	std::cout << a.Static_Variable << std::endl;  // the value of Static_Variable here is 2; cause we have 2 classes of type Test<int> instantiated

	Test<float> a3;

	std::cout << a3.Static_Variable << std::endl; // here we have another Static_Variable of value 1; cause we have 1 class of type Test<float> instantiated


	

}



