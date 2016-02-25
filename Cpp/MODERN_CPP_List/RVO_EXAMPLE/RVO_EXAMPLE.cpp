#include <iostream>
#include "BigObject.h"
#define LOG(x) std::cout << x << std::endl



void test_1()
{
	LOG(" -- RVO -- ");
	auto x = create_rvo('1');
	LOG(" -- NRVO -- ");
	auto x2 = create_rvo('2');
	LOG(" -- MOVE -- ");
	auto x3 = create_move('3');
	LOG(" -- END -- ");
}


void test_2()
{
	BigObject x, x2, x3;

	LOG(" -- RVO -- ");
	x = create_rvo('1');
	LOG(" -- NRVO -- ");
	x2 = create_rvo('2');
	LOG(" -- MOVE -- ");
	x3 = create_move('3');
	LOG(" -- END -- ");
}

int main()
{
	LOG("\n\t -- TEST 1: Initializing the variable on the caller -- ");
	test_1();
	LOG("\n\n\t -- TEST 2: Assign the variable on the caller -- ");
	test_2();

}