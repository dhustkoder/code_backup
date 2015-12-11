#include <iostream>
#include <vector>

// virtual dispatch model...

struct Base
{
    virtual int f() const noexcept { return 1; }
};

struct Derived : Base
{
    virtual int f() const noexcept { return 2; }
};

// alternative: member variable encodes runtime type...

struct Type
{
    Type(int type) : type_(type) { }
    int type_;
};

struct A : Type
{
    A() : Type(1) { }
    inline int f() const noexcept { return 1; }
};

struct B : Type
{
    B() : Type(2) { }
    inline int f() const noexcept { return 2; }
};

struct Timer
{
	Timer() {  }
	void start() { clock_gettime(CLOCK_MONOTONIC, &from); }
	struct timespec from;
	double elapsed() const
	{
		struct timespec to;
		clock_gettime(CLOCK_MONOTONIC, &to);
		return to.tv_sec - from.tv_sec + 1E-9 * (to.tv_nsec - from.tv_nsec);
	}
};

constexpr int AddLoopLimit = 1000000;
constexpr int IterationsLoopLimit = AddLoopLimit;



int main()
{

	// the virtual methods test ..............
	std::vector<Base*> vec;
	vec.reserve(AddLoopLimit);
	
	for(int i=0; i < AddLoopLimit; ++i)
		vec.push_back((i % 2) ? new Base() : (Base*) new Derived());

	
	Timer timer;
	double total = 0;
	timer.start();
	for(auto itr = vec.begin(); itr != vec.end(); itr++)
		total += (*itr)->f();

	double virtual_time_elapsed = timer.elapsed();
	printf("virtual method ended. total: %.0f.\n",total);
	printf("time elapsed: %f.\n", virtual_time_elapsed); 


	for(auto toDel : vec)
	{
		delete toDel;
	}


	// the type id test ......

	std::vector<Type*> vec2;
	vec2.reserve(AddLoopLimit);

	for(int i=0; i < AddLoopLimit; ++i)
		vec2.push_back((i % 2) ? new A() : (A*) new B());

	
	total = 0;
	timer.start();



	for(auto itr = vec2.begin(); itr != vec2.end(); itr++)
	{
		if((*itr)->type_ == 1)
			total += static_cast<A*>(*itr)->f();
		else
			total += static_cast<B*>(*itr)->f();
	}

	
	double type_id_time_elapsed = timer.elapsed();

	printf("type id checking ended. total %.0f.\n", total);
	printf("time elapsed: %f.\n", type_id_time_elapsed); 


	for(auto toDel : vec2)
	{
		delete toDel;
	}


}