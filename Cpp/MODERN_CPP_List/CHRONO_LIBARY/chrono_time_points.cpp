#include <iostream>
#include <chrono>
#define LOG(x) std::cout << x << std::endl

/* Epoch Time:
	
	also called Unix time and POSIX time, is a system for descibing instants in time, defined as the number
	of seconds that have elapsed since 00:00:00 Coordinated Universal Time (UTC), Thursday, 1 January 1970. [ not counting leap seconds ]

	It is used widely in Unix-like and many other operating systems and file formats. Because it does not handle leap seconds,
	it is neither a linear representation of time nor a true representation of UTC.

*/

/* <chrono> Time Point: -- used to represent a point of time

	chrono::system_clock::time_point -- chrono::time_point<chrono::system_clock, chrono::system_clock::duration>
	chrono::steady_clock::time_point -- chrono::time_point<chrono::steady_clock, chrono::steady_clock::duration>


*/

void using_time_point()
{
	// Lets measure the cout <<, function

	std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration>
		start = std::chrono::steady_clock::now();

	std::cout << "-+-+-+-+-+-+-+- testing -+-+-+-+-+-+-+-+-" << std::endl;


	std::chrono::nanoseconds end = (std::chrono::steady_clock::now() - start);
	// so , the operator- for time point returns a duration. we assign that duration to end
	
	LOG("nanoseconds elapsed: " << end.count());
	// what if we want to print as other time resolutions measures?
	// use duration cast

	LOG("microseconds elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(end).count());
	LOG("milliseconds elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end).count());
	LOG("seconds elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(end).count());
}


int main()
{
	using_time_point();
	std::cin.ignore(); //see the output.
}