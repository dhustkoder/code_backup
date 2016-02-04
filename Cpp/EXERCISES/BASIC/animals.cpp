#include <iostream>
#include <string>
constexpr const char* const vert = "vertebrado";
constexpr const char* const ave = "ave";
constexpr const char* const mami = "mamifero";
constexpr const char* const carn = "carnivoro";
constexpr const char* const oni = "onivoro";
constexpr const char* const herb = "herbivoro";
constexpr const char* const inver = "invertebrado";
constexpr const char* const inset = "inseto";
constexpr const char* const anel = "anelideo";
constexpr const char* const hema = "hematofago";

struct Animal
{
	Animal(const char* c1, const char*c2,
		const char*c3, const char*name)
	{
		classifications[0] = c1;
		classifications[1] = c2;
		classifications[2] = c3;
		this->name = name;
	}
	
	std::string classifications[3];
	const char* name;
};


static Animal animals[8] = 
{
	{vert, ave, carn, "aguia"},
	{vert, ave, oni, "pomba"},
	{vert, mami, oni, "homem"},
	{vert, mami, herb, "vaca"},
	{inver, inset, hema, "pulga"},
	{inver, inset, herb, "lagarta"},
	{inver, anel, hema, "sanguessuga"},
	{inver, anel, oni, "minhoca"}

};
static std::string input[3];


int main()
{
	
	std::cin >> input[0] >> input[1] >> input[2];
	int inputIndex = 0;

	Animal *rightAnimal = nullptr;
	for (auto& animal : animals)
	{
		bool isIt = true;
		for (auto& str : animal.classifications) 
		{
			if (str != input[inputIndex++]) {
				isIt = false;
				inputIndex = 0;
			}
		}

		if (isIt) {
			rightAnimal = &animal;
			break;
		}
	}
	
	if(rightAnimal != nullptr)
		std::cout << rightAnimal->name << std::endl;

}