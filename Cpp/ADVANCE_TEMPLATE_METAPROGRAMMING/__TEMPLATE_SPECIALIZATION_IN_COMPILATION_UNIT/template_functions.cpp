#include "template_functions.h"


// specialization for float
template<>
void foo<float>()
{
	LOG("foo float");
}

// specialization for int
template<>
void foo<int>()
{
	LOG("foo int");
}

