#include <iostream>
#include <string>
#include <random>
#include <sstream>
#define LOG(x) std::cout << x << std::endl


/* <random> Random engine: 
	
		Stateful generator that generates random values within predefined mix and max.



*/

// default_random_engine
void example1() 
{

	std::default_random_engine engine;

	LOG("MIN: " << engine.min());
	LOG("MAX: " << engine.max());

	std::stringstream engine_state;
	engine_state << engine; // save state;

	LOG("RANDOM VALUE: " << engine());
	LOG("RANDOM VALUE: " << engine());

	
	engine_state >> engine; // restore state;

	// same values are generated because the eng state was restored.
	LOG("RANDOM VALUE: " << engine());
	LOG("RANDOM VALUE: " << engine());
	
}


int main()
{
	example1();


}