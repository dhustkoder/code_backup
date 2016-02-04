#include <iostream>
#include <utility>

using SalaryAndTax = std::pair<float, float>;
void calcTaxes(SalaryAndTax&);

int main()
{
	static SalaryAndTax salAndTax;
	std::cin >> salAndTax.first;
	calcTaxes(salAndTax);

	if (salAndTax.second == 0.00f)
		std::cout << "Isento" << std::endl;
	else {
		std::cout.precision(2); std::cout.setf(std::cout.fixed);
		std::cout << "R$ " << salAndTax.second << std::endl;
	}

}

void calcTaxes(SalaryAndTax &salNTax) 
{
	constexpr auto frstPercentage =  1000.00f * 0.08f;
	constexpr auto scndPercentage =  1500.00f * 0.18f;
	constexpr auto trdPercentage = frstPercentage + scndPercentage;

	if (salNTax.first <= 2000.00f)
		salNTax.second = 0.00f;
	else if (salNTax.first <= 3000.00f)
		salNTax.second = (salNTax.first - 2000.00f) * 0.08f;
	else if (salNTax.first <= 4500.00f)
		salNTax.second = frstPercentage + ((salNTax.first - 3000.00) * 0.18);
	else 
		salNTax.second = trdPercentage + ((salNTax.first - 4500.00f) * 0.28f);
}