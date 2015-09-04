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

	std::cout << a.Static_Variable << std::endl;  // o valor da Static_Variable sera 2; pois instanciamos 2 classes do tipo Test<int>

	Test<float> a3;

	std::cout << a3.Static_Variable << std::endl; // o valor da Static_Variable sera 1; pois instanciamos 1 classe do tipo Test<float>


	

}



