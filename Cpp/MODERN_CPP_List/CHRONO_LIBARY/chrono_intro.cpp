#include <iostream>
#include <chrono>
#define LOG(x) std::cout << x << std::endl;

/*	Introduction to chrono library.
		-- A precision-neutral library for time and date


	chrono provides 3 Clocks:
		
		1. std::chrono::system_clock : current time according to the system.

		2. std::chrono::steady_clock : goes at a uniform rate. (cannot be changed like the system clock)

		3. std::high_resolution_clock : provides smallest possible TICK period(frequency).

		in C++ chrono, time frequency is represented with a RATIAL



*/

// lets take a look at the ratials

void chrono_ratial()
{
	std::ratio<1, 10> r1;
	LOG(r1.num << " / " << r1.den); // 1 / 10

	// so, lets take a look at the frequency of my system clock:

	LOG(std::chrono::system_clock::period::num << " / " << std::chrono::system_clock::period::den);
	// my system clock frequency is 1 / 10000000

}



/* Duration :

	chrono have a template class duration to represent time duration.
		std::chrono::duration<>

	for example:

	std::chrono::duration<int, std::ratio<1,1>>
		: this can represent number of seconds as a int

	std::chrono::duration<double, std::ratio<60/1>>
		: this can represent number of minutes stored in a double
		
	with this we can select our own desired precision.
	to help, chrono have some predefined typedefs for common time measures

	chrono::nanoseconds, chrono::microseconds, chrono::milliseconds, chrono::seconds, chrono::minutes, chrono::hours
*/



void chrono_duration()
{
	std::chrono::microseconds mic(3300); // mic == 3300 microseconds.
	std::chrono::nanoseconds nano = mic; // nano == 3300000

	// as we can see we have the assign operator overloaded to do the conversion
	// however, this cannot convert from a HIGHer resolution measure to a LOWER resolution.
	// for example:

	/* std::chrono::milliseconds milli = mic;  */ 
	// this won't compile, because "mic" is HIGHER resolution precision than "milli"
	// so, we need  a chrono duration_cast
	std::chrono::milliseconds milli;
	milli = std::chrono::duration_cast<std::chrono::milliseconds>(mic); // cast microseconds type to a lower resolution milliseconds type
	// now milli == 3 milliseconds,  ( we lose precision )
}


int main() 
{
	chrono_ratial();
	chrono_duration();

}