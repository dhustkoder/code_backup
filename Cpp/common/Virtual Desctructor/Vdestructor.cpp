#include <cstring>0
#include <iostream>
class Base 
{
private:
    char *name;
public:
    Base(const char *const _n)
    {
        name = new char[std::strlen(_n)];
        std::strcpy(name,_n);
    
        std::cout << "Base Constructor Called!!!!\n";
    }

   // ~Base(){}  this does not call Derived destructor if = Base* p = new Derived; delete p;
    virtual ~Base()
    {
        std::cout << "Base Destructor Called!!!!\n";
        delete name;
    }

};

class Derived : public Base
{
public:
    Derived() : Base("Called By Derived")
    {
        std::cout << "Derived Constructor Called!!!!!\n";
    }

    ~Derived()
    {

        std::cout << "Derived Destructor Called!!!!!\n";
    }
};

int main()
{
    Base *p = new Derived();                                        // STACK
//                                                                  [ DERIVED ] Pushed Last
    // Base Constructor Called                                      [   BASE  ] Pushed First
    // Derived Constructor Calledi                                       
    delete p;
    // Derived Destructor Called                                    [ DERIVED ] Destructed First
    // Base Destructor Called                                       [   BASE  ] Destructed Last
}
