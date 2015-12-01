#include <iostream>
#include <string>
#include <vector>
/*
    Association is a relationship where all objects have their own 
    lifecycle and there is no owner. Let’s take an example of Teacher and Student. 
    Multiple students can associate with single teacher and single student can associate with multiple teachers, 
    but there is no ownership between the objects and both have their own lifecycle. 
    Both can create and delete independently.

*/

// |AssociationExample| ----------> |std::string|

class AssociationExample
{
public:
    void foo(std::string &str) // association as a method argument
    {
        str.assign("using the resource...");
    
    }
    
    
    void foo()
    {
        std::string localStr; // association as a local variable
        
    }

    
};





// Aggregation: is a specialised form of | Association |.
// In Aggregation all objects have their own lifecycle,
// but there is ownership and child objects can not belong to another parent object.

// Like a Departament and Teacher. A single Teacher can not belong to multiple Departaments.
// but if we delete the Departament , the Teacher will not be deleted. this is a "Has-a" relationship



class Teacher
{
public:
    // .....
private:
    // ......
};


class Departament
{
public:
    template<typename ...Args>
    void addTeacher(Args ...args)
    {
        [](...){}( teachers.push(std::forward<Args>(args)...) );
        
    }
private:
    std::Vector<Teacher&> teachers;
    
    
};












int main()
{
    
   
   return 0;
}
