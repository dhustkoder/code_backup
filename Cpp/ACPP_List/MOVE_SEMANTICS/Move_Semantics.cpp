#include <iostream>
#include <algorithm>
#include <string>


#define LOG(x) std::cout << x << std::endl;

	// Move Semantics... 
/*	So in C++11 we're introduce to new feature. the Rvalue reference.
 *
 *  But what is the purpose of Rvalue reference?.
 *
 * Rvalue reference is going to help us to increase the performance of our code more easily, I mean, with less code.
 *
 * and we do that, using Rvalues references to do  MOVE SEMANTICS.
 *
 * Lets take a simple example. 
 *
 *
 */

// We are already familiar with Lvalues and Rvalues. so take a look now in how Rvalue reference can be used

// this one of things we can do now, overload a function with Rvalue reference and Lvalue reference
void printInt(int &i) { std::cout << "Lvalue Reference i = " << i << std::endl; }

void printInt(int &&i) { std::cout << "Rvalue Reference i = " << i << std::endl; }

// But note that if we add other overload like this

//void printInt(int i) { /**/ } // the compiler will not know which function to call. so not use this version for overload when using references

void example_1()
{
	int a = 111; // as we know a is a Lvalue.

	printInt(a); // so here, the printInt(int&) will be called.

	printInt(a + 2); // but here, the Rvalue version ( printInt(int&&) ) will be called.

}


// But where is it really helpful ? how does it increase performance. well, int is a small type so it does not make a difference really
// passing by value of passing by rvalue reference

// But when we're using RAII objects / Resource Managment Objects, this is really useful













// Lets take a look. here we have a class Bird, 
// Bird in this example does not have nothing expansive, just a variable of type std::string which store the Birds name.
class Bird
{
public:
	// Birds ... API's
	std::string name;


};


// But here we have  a BirdFlock class, it will save a array of Birds, we could use a std::vector, or any other std container for this.
// but we have to see this to understand how Rvalue reference help in performance.
class BirdFlock
{
public:
	BirdFlock(int flockSize) : 
		birdsPtr_( nullptr ), flockSize_(flockSize)
	{
		birdsPtr_ = new Bird[flockSize_];
		birdsPtr_[flockSize_ - 1].name = "last bird";
	}


	// here we have a COPY CONSTRUCTOR, it is a normal Copy Constructor, it does what is in its name.
	// does a deep copy of the BirdFlock rhs into (this), the new BirdFlock that is being born.
	BirdFlock(const BirdFlock& rhs) :
		birdsPtr_(nullptr), flockSize_(rhs.flockSize_)
	{
		LOG("USING COPY CONSTRUCTOR");
		if (rhs.flockSize_ == 0)
			return;

		this->birdsPtr_ = new Bird[flockSize_];

		std::copy_n(this->birdsPtr_, this->flockSize_, rhs.birdsPtr_);
		
		
	}


	// And here is the NEW TRICK of C++11, the MOVE CONSTRUCTOR.
	// this constructor takes a BirdFlock&& parameter which is a Rvalue
	// so as we know, Rvalues are meant to be temporary values, just for some operation, and it will be destroyed after the operation
	// Say that we just got a Rvalue of type BirdFlock and passed it to construct a new BirdFlock.
	// why would we create a deep copy of a BirdFlock that will be destroyed in the next instruction ?
	// so now in C++11 we have our MOVE CONSTRUCTOR, that does not copy all members of a Rvalue into his own.
	// It steal the address of the resources to himself and leave the Rvalue empty.
	BirdFlock(BirdFlock&& rhsMove) : 
		birdsPtr_ ( nullptr ), flockSize_ (rhsMove.flockSize_)
	{
		LOG("USING MOVE CONSTRUCTOR");
		if (rhsMove.flockSize_ == 0)
			return;
		
		birdsPtr_ = rhsMove.birdsPtr_; // steal the rhsMove's pointer to the birds.
		rhsMove.birdsPtr_ = nullptr; // set rhsMove's pointer to nullptr cause it will be destroyed and try to delete the pointer
		rhsMove.flockSize_ = 0; // set rhsMove flockSize_ to 0, just for safety.
	}




	BirdFlock& operator=(const BirdFlock& rhs)
	{
		LOG("USING COPY ASSIGN OPERATOR");
		if(this->flockSize_ != 0)
		{
			delete[] this->birdsPtr_;
			this->flockSize_ = 0;
		}
		if (rhs.flockSize_ == 0)
			return *this;
		
		this->flockSize_ = rhs.flockSize_;
		this->birdsPtr_ = new Bird[flockSize_];
		std::copy_n(this->birdsPtr_, this->flockSize_, rhs.birdsPtr_);

		return *this;
	}


	BirdFlock& operator=(BirdFlock&& rhsMove)
	{
		LOG("USING MOVE ASSIGN OPERATOR");
		
		if(this->flockSize_ != 0)
		{
			delete[] this->birdsPtr_;
			this->flockSize_ = 0;
		}
		if (rhsMove.flockSize_ == 0)
			return *this;
			
		birdsPtr_ = rhsMove.birdsPtr_; // steal the rhsMove's pointer to the birds.
		rhsMove.birdsPtr_ = nullptr; // set rhsMove's pointer to nullptr cause it will be destroyed and try to delete the pointer
		rhsMove.flockSize_ = 0; // set rhsMove flockSize_ to 0, just for safety.

		return *this;
	}



	~BirdFlock()
	{
		delete[] birdsPtr_;
	}

	Bird *birdsPtr_;
	int flockSize_;

};


// Now , lets take a look how it will work with functions arguments.

// Well, pay attention that this function does not get a commum type as parameter (int , char, double, ....)
//this function takes a Custom Type , a class, so our Custom Type have 3 Constructors

// 1 MAIN CONSTRUCTOR, which takes the number of the Birds in the BirdFlock

// 2 COPY CONSTRUCTOR, which takes a Lvalue Reference to another BirdFlock, and COPIES the resource for its own

// 3 MOVE CONSTRUCTOR, whick takes a Rvalue Reference to another BirdFlock, and STEALS the resource for its own

void foo(BirdFlock birdEveryWhere) // so, which CONSTRUCTOR will be called here? 
{								  // it depends on the type that you will pass when calling this function of course.
								// lets see 


}

void foo_by_ref(BirdFlock &birdEveryWhere)
{

}

void Bird_Example()
{
	foo(10); // If we pass a Integer, the MAIN CONSTRUCTOR of BirdFlock will be called in the foo function
	BirdFlock reusable(10);
	//....
	foo(reusable); // here, the COPY CONSTRUCTOR will be called, couse the argument we are giving is a Lvalue
	
	foo(std::move(reusable)); // we can do like this.
	// using the std::move function , std::move is a cast, will cast the Lvalue reusable to a Rvalue,

	// we can do like this too:
	//foo(static_cast<BirdFlock&&>(reusable));
	// But in this case, the fastest operation is in foo_by_ref
	// becouse it call NO CONSTRUCTOR, is just a lvalue reference

	// we end with 3 types of argument passing for BirdFlock:

	foo_by_ref(reusable); // call NO CONSTRUCTOR couse its passed by Lvalue Reference, fastest operation

	foo(reusable); // Call COPY CONSTRUCTOR, slowest operaion

	foo(std::move(reusable)); // Call MOVE CONSTRUCTOR, fast operation


	// So, now that we know how to use it well,
	// when is the best time to use the Rvalue reference ?
	
	// It is when we want TO SWAP OBJECTS.

	// Lets say we have 2 Objects of type BirdFlock

	BirdFlock A(100);
	BirdFlock B(200);

	// So we have 2 Objects A and B, A is a Flock of 100 birds, and B is a flock of 200, birds.
	// pretending the Bird type is expansive size, the operation of copy this can be slow;
	// this is how we would normaly swap the Objects contents.


	BirdFlock temp = A; // now we have 2 copies of A
	A = B; // now we have 2 copies of B
	B = temp; // now we have 2 copies of temp (aka A)

	// So Swaping like that we end up doing the EXPANSIVE COPY OPERATION 3 times.
	// if we are going to swap to use the same DATA, why not just really SWAP and not copy ?

	// Lets use the MOVE 
	std::cout << " _____________________________________________________________ " << std::endl;
	BirdFlock TEMP = std::move(A); // TEMP steals from A. and leave it empty
	A = std::move(B); // A steals from B, and leave it empty
	B = std::move(TEMP); // B steals from TEMP (aka A) and leave it empty.
	// so TEMP ends empty, and the data SWAPS faster.
	
	// now we really just swap the the data!




}












int main()
{
	example_1();


	Bird_Example();



	std::cin.ignore(1);

	return 0;
}
