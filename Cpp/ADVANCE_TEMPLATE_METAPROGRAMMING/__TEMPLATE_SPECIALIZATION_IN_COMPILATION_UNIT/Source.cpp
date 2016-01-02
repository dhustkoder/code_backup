#include <boost/type_index.hpp>
#include "template_functions.h"




int main() 
{
	LOG( (is_one_of<int,char, void, double, void, int>::value) );
	foo<int>();
	foo<float>();
}




