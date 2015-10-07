#include <iostream>
#include <string>

#define LOG(x) std::cout << x << std::endl;

class MyVec
{
public:
	MyVec(size_t vecSize)
	{
		heapPtr_ = new double[vecSize];
		vecSize_ = vecSize;
	}

	MyVec(const MyVec &rhs) : // copy constructor
		MyVec(rhs.vecSize_)
	{
		LOG("Called Copy Constructor");
		std::copy_n(rhs.heapPtr_, rhs.vecSize_, this->heapPtr_);
	}

	MyVec(MyVec &&rhs) : // Move Constructor
		heapPtr_(nullptr), vecSize_(0)
	{
		LOG("Called Move Constructor");
		std::swap(this->heapPtr_, rhs.heapPtr_);
		std::swap(this->vecSize_, rhs.vecSize_);
	}

	~MyVec()
	{
		delete[] heapPtr_;
	}



private:
	double *heapPtr_;
	size_t vecSize_;
};





MyVec& Process(MyVec &oldVec) // This copies from &oldVec and return the newVec
{
	LOG("Lvalue PROCESS");
	MyVec newVec(oldVec);
	//............ process
	return newVec;
}

MyVec&& Process(MyVec &&oldVec) // This moves oldVec to a newVec and returns the newVec
{
	LOG("Rvalue PROCESS");
	MyVec newVec(std::move(oldVec));
	//.............process
	return std::move(newVec);
}




// So Lets see Perfect Forwarding, in this example we want to pass a object of type MyVec to LogAndProcess Function
// But in the LogAndProcess the function Process is called, and it takes the same argument we passed to LogAndProcess.
// So, the point of Perfect Forwarding is, if we passed our object by an Lvalue reference then we want it to be passed to the Process(MyVec&).

// And if we passed by Rvalue, we want it to be passed to the version : Process(MyVec&&)


// we can do that like this.
template<class T>
T&& LogAndProcess(T&& arg)
{
	//......
	return Process(std::forward<T>(arg));
	// std::forward is a conditional cast, if arg was passed as Rvalue, it will pass a Rvalue to Process, if is  a Lvalue it will pass a Lvalue to Process
}


// Perfect Forwarding is just achived when: 
// 1. T is a template type.
// 2. Type deduction (reference collapsing happens to T)
// - T is a function template, not a class template.


class Test
{
	
	
public:
	Test() : Test(this)
	{
		A = new MyVec(10);
		throw std::exception("Testing");
		B = new MyVec(20);
	}
	~Test()
	{
		delete B;
		delete A;
	}


private:
	Test(Test*) : A(nullptr), B(nullptr) {}
	MyVec *A, *B;
};



int main()
{
	MyVec temp(1000);
	MyVec reusable(2000);
	LogAndProcess(reusable); // this result in 1 copy operation
	LogAndProcess(std::move(temp)); // this result in 1 move operation
	
	

	// reusable 
	//is unchanged
	// temp is empty
}







