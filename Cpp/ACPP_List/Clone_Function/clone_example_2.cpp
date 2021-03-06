#include <iostream>
#include <algorithm>

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


template<class T>
struct My_unique_ptr
{
	T* type_;
	My_unique_ptr(T* type) : type_ ( type ) {}
	My_unique_ptr(T type) : type_ ( new T(type) ){}
	My_unique_ptr(std::initializer_list<T*> list)
	{
		type_ = new T[list.size()];
		for(int i{0}; i < list.size(); ++i)
			type_[i] = (list.begin() + i);
	
	}
	My_unique_ptr() : type_( new T() ) {}
	T* operator->() { return type_; }
	T* operator[](int offset) { return *type_[offset]; }
	
	~My_unique_ptr() { delete type_; }

};



void conversation(BigBoss *snake)
{
//	BigBoss *tempCopy = new BigBoss(*snake);  nao funcionara, pois nao criara o objeto certo.
	My_unique_ptr<BigBoss> tempCopy(snake->clone()); // RAII example...
	tempCopy->speak();
	// no need to delete tempCopy

}



int main()
{
	My_unique_ptr<BigBoss*> bestSoldiers = { new BigBoss, new SolidSnake, new LiquidSnake };
	
	conversation(bestSoldiers[0]);
	conversation(bestSoldiers[1]);
	conversation(bestSoldiers[2]);


	std::cout << " ---------------------------------------------------------------------- " << std::endl;
	



	return 0;
}




