#include "template_functions.h"


template<>
void foo<float>()
{
	LOG("foo float");
}


template<>
void foo<int>()
{
	LOG("foo int");
}

