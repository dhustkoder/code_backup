#include <iostream>
#include <algorithm>
#include <utility>

using DDDCity = std::pair<int, const char*>;

static DDDCity dddsAndCities[8] = 
{
	{61, "Brasilia"}, {71, "Salvador"},
	{11, "Sao Paulo"}, {21, "Rio de Janeiro"},
	{32, "Juiz de Fora"}, {19, "Campinas"},
	{27, "Vitoria"}, {31, "Belo Horizonte"}
};


int main()
{
	static int ddd;

	std::cin >> ddd;
	auto itr = std::find_if(dddsAndCities, dddsAndCities + 8, [](DDDCity &it) { return it.first == ddd; });

	if (itr != dddsAndCities + 8)
		std::cout << itr->second << std::endl;
	else
		std::cout << "DDD nao cadastrado" << std::endl;
}