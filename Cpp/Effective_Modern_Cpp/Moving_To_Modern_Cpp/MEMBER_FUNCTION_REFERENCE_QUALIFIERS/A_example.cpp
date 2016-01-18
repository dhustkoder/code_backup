#include <iostream>
#include <memory>
#include <vector>
#define LOG(x) std::cout << x << std::endl
#define TYPESTR(x) boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name()

class Widget
{
	using DataType = std::vector<double>;
public:
	Widget(std::initializer_list<double> il) : m_internalVec(il)
	{

	}

	DataType& data() & // for lvalue Widgets, return lvalue ref
	{
		return m_internalVec;
	}

	DataType data() && // for rvalue Widgets, return rvalue
	{
		return std::move(m_internalVec);
	}

private:
	DataType m_internalVec;
};
// Notice the differing return types from the data overloads. The lvalue reference
// overload returns an lvalue reference ... ( i.e, an lvalue), and the rvalue reference
// overload returns a temporary object (i.e., an rvalue)


void doSomething(Widget& w) {
	for (auto it : w.data()) // normaly use lvalue references
		std::cout << it << std::endl;
}

void doSomething(Widget&& w) {
	for (auto it : std::move(w).data()) // use std::move, when using rvalue references if you want it to be treated...
		std::cout << it << std::endl;   // as rvalue, other wise it will call the lvalue reference data().

	for (auto it : Widget({ 1,3,4 }).data()) // this is an pure rvalue, (not a reference to an rvalue), even without
		std::cout << it << std::endl;        // using std::move it will call the rvalue reference version of data();
}


int main()
{
	Widget lvalueW{ 30,40,50,60 };
	doSomething(lvalueW);
	doSomething(Widget({10,20,30,40}));
}