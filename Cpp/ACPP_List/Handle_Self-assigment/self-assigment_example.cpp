#include <iostream>


enum class COLOR : uint8_t
{

	RED,
	GREEN,
	BLUE



};


std::ostream& operator<<(std::ostream& os, const COLOR &color)
{
	switch(color)
	{
		case COLOR::RED:
			os << "Red";
			break;
		case COLOR::GREEN:
			os << "Green";
			break;
		case COLOR::BLUE:
			os << "Blue";
			break;
	
	}

	return os;

}



class Dog
{
	COLOR* color_ptr;
public:
	Dog(const COLOR dog_color) : color_ptr { new COLOR(dog_color) }
	{
	
		std::cout << *color_ptr << "  dog is born!"  << std::endl;
	
	}
	void bark()
	{
		std::cout << "I'm a " << *color_ptr << " Dog!" << std::endl;
	}
	
	
	
	
	Dog& operator=(const Dog &assigment)
	{
		// the dog has  a pointer to his color. if we assigment the dog with another dog , we have to delete the pointer,
		// and then allocate a new color with it.
		// but, if we do self-assiment, the dog will delete his pointer and try to create a new color with the deleted pointer.
		// this is not good. the result may be undefined as the memory at that location will be freed.
		// but we can prevent it with a small test.
		
		if( this == &assigment ) // now if we do self-assigment, we return immediatly. good.
			return *this;

		// Other thing, enum class cant have constructors but just for example :
		// for example : what if the COLOR was a normal class , and its constructor could throw an exception ? 
		// then we have to take care to not delete the color_ptr until a new COLOR is constructed with everything ok.
		COLOR *aux;
		try
		{
			aux = new COLOR(*assigment.color_ptr);
		}
		catch(const int x)
		{
			std::cerr << " error constructing color: " << x << std::endl;
			delete aux;
			return *this;
		}
			delete color_ptr;
			color_ptr = aux;
			return *this;
	}

};



int main()
{
	Dog dog(COLOR::RED);
	
	dog = dog; // this looks silly;

	Dog	dogs[] = { dog };

	int i{0}, j{0};

	dogs[ i ] = dogs[ j ];  // but this can happen more often.

	dogs[0].bark(); // so, how can we , prevent self-assigment errors  ?
	
}



























