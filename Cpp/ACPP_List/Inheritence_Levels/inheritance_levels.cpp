#include <iostream>


// Public , Protected, Private Inheritance Examples:

class B{
public:
	void f_pub() { std::cout << "f_pub is called" << std::endl; }
protected:
	void f_prot() { std::cout << "f_prot is called" << std::endl; }
private:
	void f_priv() { std::cout << "f_priv is called" << std::endl; }
};

class D_pub : public B {
public:
	
	void f()
	{
		f_pub(); // ok. D_pub public function
		f_prot(); // ok. D_pub protected function
		f_priv(); // error B private function 
	}
};


class D_prot : protected B {
public:
	void f()
	{
		f_pub(); // ok. D_prot protected function
		f_prot(); // ok. D_prot protected function
		f_priv(); // error B private function 
	}
};
class D_priv : private B {
public:
	void f()
	{
		f_pub(); // ok. D_priv private function
		f_prot(); // ok. D_priv private function
		f_priv(); // error B private function 
	}
};

/*
	They specifies different access controll from the derived class to the base class.

	Access Control:
	1. None of the derived classes can access anythinh that is private in B

	2. D_pub inherits public members of B as public and protected members of B as protected
		( making D_pub a kind of B, expansion of B, ...)

	3. D_prot inherits the public and protected members of B as protected

	4. D_priv inherits the public and protected members of B as private


	Difference in Casting:

	1. Anyone can cast a D_pub* to B*. D_pub is a special kind of B.

	2. D_prot's members, friends, and children can cast a D_prot* to B*

	3. D_priv's members and friends can cast a D_priv* to B*


*/


int main()
{
	B *p_Dpub = new D_pub(); // ok, cuz D_pub is-a relationship , a kind of B

	B *p_Dprot = new D_prot(); // error, only D_prot member functions, friends, children can cast a D_prot* to B*
	 
	B *p_Dpriv = new D_priv(); // error, only D_priv member functions, friends can cast a D_priv* to B*

	// Public Inheritance : is-a relationship, D_pub is a kind of B
	// Private Inheritance : similar to has-a relation
}