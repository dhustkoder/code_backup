#include <iostream>
#include <string>
#include <vector>
#include <memory>
#define LOG(x) std::cout << x << std::endl
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

// I'll show an example using 2 classes Teacher and Departament

class Teacher
{
public:
	Teacher(const char* name) : m_name(name) { LOG("created teacher " << m_name); }
	const std::string& getName() { return m_name; }
	~Teacher() { LOG("destroying teacher " << m_name); }
	// .....
private:
	std::string m_name; // by the way, Teacher here is using Composition with std::string
	// ......
};

// Now lets dive in the Departament class that is using Aggregation

// |Departament| <>-----------> | Teacher |
class Departament
{
public:
	Departament() { LOG("Creating Departament"); }
	template<class ...Args>
	void addTeacher(Args&& ...args)
	{
		(void)std::initializer_list<int>
		{
			(m_teachers.push_back(std::forward<Args>(args)), 0)...
		};
	}
	
	void listTeachers()
	{
		for (auto &itr : m_teachers)
			LOG(itr.lock()->getName());
	}
	~Departament() { LOG("Destroying Departament"); }
private:
	std::vector<std::weak_ptr<Teacher>> m_teachers;
};

void aggregation_test()
{
	std::shared_ptr<Teacher> teacher_1(new Teacher("Dr. cooper")), teacher_2(new Teacher("Dr. Hofstader"));
	

	// the theachers have its own life-time

	// the departament_1 have its own life-time too
	std::unique_ptr<Departament> departament(new Departament());

	departament->addTeacher(teacher_1, teacher_2);
	LOG("\n\nPrinting Departament 1 list...");
	departament->listTeachers();
	LOG("\n\n");
	// .... do some work until delete the departament
	departament.reset(nullptr); // departament is destroyed , but teachers lives on


	departament.reset(new Departament()); // a new departament is created

	
	departament->addTeacher(teacher_2, teacher_1);
	LOG("\n\n Printing Departament 2 list...");
	departament->listTeachers();
	LOG("\n\n");
	// ...do some work until delete the departament
	departament.reset(nullptr); // other departament is destroyed, but teachers lives on


	
}


// Composition: The Class is owner of a sub-Object and is responsable for its initialization and destruction
struct Motor{};

// | Car |<#>---------> |Motor|
class Car
{
public:
	Car() : m_motor(new Motor()){}
	~Car() { delete m_motor; }
private:
	Motor *m_motor;
};

// Or
// |Truck| <#>------> |Motor|
class Truck
{
public:
	Truck(){}
	~Truck(){}
private:
	Motor m_motor;
};


int main()
{
	aggregation_test();

	
}