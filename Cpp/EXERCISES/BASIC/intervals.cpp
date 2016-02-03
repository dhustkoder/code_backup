#include <iostream>

int main()
{
	enum { _0To25, _25To50, _75To100 };
	static constexpr const char* const intervalsText[] {
		"[0,25]", "(25,50]", "(75,100]"
	};
	static auto getIntervalIndex = [](float x)->int 
	{
		if (x < 0.0)
			return -1;
		else if (x <= 25.0)
			return _0To25;
		else if (x <= 50.0)
			return _25To50;
		else if (x > 75.0 && x <= 100.0)
			return _75To100;
		else
			return -1;
	};

	static float x;

	std::cin >> x;
	int index = getIntervalIndex(x);
	if (index != -1)
		std::cout << "Intervalo " << intervalsText[index] << std::endl;
	else
		std::cout << "Fora de intervalo" << std::endl;




	return 0;
}