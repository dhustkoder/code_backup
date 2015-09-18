#include <iostream>


class BigBoss
{
public:
	BigBoss(std::string id = "John") : id_(id){}
	virtual void speak() 		{ std::cout << "I don't like spy movies..." << std::endl; }
	virtual BigBoss* clone() 	{ return new BigBoss(*this); } 
	virtual ~BigBoss()
	{
		if(id_ == "John")
			std::cout << "It's not over yet..." << std::endl;
	}
private:
	std::string id_;	

};

class SolidSnake : public BigBoss
{
public:
	SolidSnake() : BigBoss("David"){}
	virtual void speak() 	{ std::cout << "I'm no hero... never was... never will be." << std::endl; }		
	SolidSnake* clone() 	{ return new SolidSnake(*this); }
	~SolidSnake() 			{ std::cout << "This is my last mission..." << std::endl; }
};


class LiquidSnake : public BigBoss
{
public:
	LiquidSnake() : BigBoss("Eli"){}
	virtual void speak() 	{ std::cout << "You enjoy all the killing... That's why!" << std::endl; }
	LiquidSnake* clone() 	{ return new LiquidSnake(*this); }
	~LiquidSnake() 			{ std::cout << "SNAAAAAAAAAAAAAAKE!!!!!!!!!" << std::endl; }
};






void conversation(BigBoss *snake)
{
//	BigBoss *tempCopy = new BigBoss(*snake); // nao funcionara, pois nao criara o objeto certo.
	BigBoss *tempCopy = snake->clone();
	tempCopy->speak();
	delete tempCopy;

}



int main()
{
	BigBoss* bestSoldiers[] = { new BigBoss, new SolidSnake, new LiquidSnake };
	
	conversation(bestSoldiers[0]);
	conversation(bestSoldiers[1]);
	conversation(bestSoldiers[2]);






	return 0;
}




