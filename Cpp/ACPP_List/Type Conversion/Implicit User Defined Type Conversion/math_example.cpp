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
	Rational(int numerator, int dennominator) : 
		numerator_ ( numerator ), dennominator_ ( dennominator ){}
	
	const Rational operator*(Rational &rhs)
	{
		return Rational( numerator_ * rhs.numerator_ , dennominator_ * rhs.dennominator_ );
	}


private:
	int numerator_, dennominator_;



};


int main()
{
	Rational rat(5,10);

	rat = rat * rat;

	std::cout << rat;	
	std::cout << rat;


}




