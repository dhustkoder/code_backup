#include <boost/type_index.hpp>
#include "template_functions.h"




int main() 
{
	LOG( (is_one_of<int,char, void, int, double, void>::value) );

	foo<int>();
	foo<float>();
}




