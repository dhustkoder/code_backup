#include <iostream>
#define LOG(x) std::cout << x << std::endl


class Base
{
public:
	virtual ~Base() = default;
	virtual void foo_1() = 0;
	virtual void foo_2() = 0;
};


class Derived_1 : public virtual Base
{
public:
	void foo_1() override
	{
		LOG("called foo_1 from Derived_1");
	}
};


class Derived_2 : public virtual Base
{
public:
	void foo_2() override
	{
		LOG("called foo_2 from Derived_2");
		foo_1(); // call Derived_1 foo_1 even if Derived_1 isn't directly related
		// cross delegation
	}
};


class CompleteClass : public Derived_1, public Derived_2
{

};



int main()
{

	CompleteClass complete;

	complete.foo_2();




}
