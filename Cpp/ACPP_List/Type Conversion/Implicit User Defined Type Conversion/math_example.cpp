#include <iostream>


	// One example of how type conversion function inside a class, can be of help








class Rational
{
	friend std::ostream& operator<<(std::ostream &ostream, Rational &rational)
	{
		ostream << "numerator: " << rational.numerator_ << ", dennominator: " << rational.dennominator_ << std::endl;
		return ostream;

	}


public:
	Rational(int numerator = 0, int dennominator = 1) : 
		numerator_ ( numerator ), dennominator_ ( dennominator ){}
	
	const Rational operator*(Rational rhs)
	{
		return Rational( numerator_ * rhs.numerator_ , dennominator_ * rhs.dennominator_ );
	}
	const Rational operator*(int multiplier)
	{
		return Rational(numerator_ * multiplier, dennominator_ * multiplier);
	}	
	operator int()
	{
		return ( numerator_ / dennominator_ );
	}
private:
	int numerator_, dennominator_;



};


int main()
{
	Rational rat  = 20; // 20 is implicit converted into Rational
	
	std::cout << rat; // 20, 1

	
	Rational rat2 = rat * 2; // operator*(int) is called
	
	
	std::cout << rat2; // 40, 2 
	
	
	Rational rat3 = rat * rat2; // operator*(const Rational&) is called

	
	std::cout << rat3; // 800, 2

	Rational rat4 = 2 * rat3; // operator int() is called

	std::cout << rat4; // 800, 1

}




