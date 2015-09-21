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
	
	const Rational operator*(Rational &rhs)
	{
		return Rational( numerator_ * rhs.numerator_ , dennominator_ * rhs.dennominator_ );
	}
	
	const Rational operator*(int multiplier)
	{
		return Rational(numerator_ * multiplier, dennominator_ * 1);
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
	// cause the Rational constructor  allows implicit conversions objects of Rational class can be initialized as follows
	
	Rational rat = 20; // 20 is implicit converted into Rational, numerator is 20, and denominator is default 1
	
	std::cout << rat; // 20, 1

	
	Rational rat2 = rat * 2; // operator*(int) is called to convert integer into Rational;
				// or we better do ( rat * Rational(2) )
	
	
	std::cout << rat2; // 40, 2 
	
	
	Rational rat3 = rat * rat2; // operator*(const Rational&) is called

	
	std::cout << rat3; // 800, 2

	Rational rat4 = 2 * rat3; // operator int() is called to convert rat3 into integer and do the operation.

	std::cout << rat4; // 800, 1

}




