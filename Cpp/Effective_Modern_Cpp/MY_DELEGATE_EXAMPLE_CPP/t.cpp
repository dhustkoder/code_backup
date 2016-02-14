#include <iostream>
#include <string>

std::string operator"" s(const char *x, unsigned long s) { std::cout << s << std::endl ; return std::string(x); }

int main()
{

	auto x = "lala "s + "baba";


	std::cout << x << std::endl;
}
