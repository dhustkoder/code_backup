#include <iostream>
#include <vector>
#include <string>


class Person
{
public:
	
	
	// a normal constructor just allocate a new string to represent the Person name_
	Person(std::string name) :  name_ ( nullptr )
	{
		name_ = new std::string(std::move(name));	// we move the string "name" cuz we dont need it anymore
	}
	
	
	Person(const Person&) = delete; // a default function deleted, so copy constructor cant be used anymore
	
	Person(Person&& oldPerson) // a move constructor created
	{
		// delete the original name if still not deleted.
		if(this->name_ != nullptr)
		{
			delete this->name_;
			this->name_ = nullptr;
		}
		// steal the oldPerson's name
		this->name_ = oldPerson.name_;
		oldPerson.name_ = nullptr;	// is needed to point the old object's pointers stealed to null, or we have problems, mainly destructor problems.
	}
	
	std::string getName() const
	{
		
		return (name_ != nullptr) ? *name_ : "nullptr"; // if the Person was moved, then its name is null, so ensure to not dereference a null pointer
	}	
	
	
	void setName(std::string newName)
	{
		if(name_ != nullptr)
		{
			delete name_;
			name_ = nullptr;
		}
		
		name_ = new std::string(std::move(newName));	
	
	}
	
	
	
	Person& operator=(const Person &person) // a normal assigment operator, assing the given person to the "this"
	{
		if(name_ != nullptr)
		{
			delete this->name_;
			name_ = nullptr;
		}
		
		if(person.name_ != nullptr)
			this->name_ = new std::string(person.name_->c_str());

		return *this;
		// the return of operator= is the "*this" for the following. see this: person_a = person_b = person_c;
		// person_a will be assign to the return of ( person_b = person_c ). which is person_b after the assing. ( *this )
	
	}
	
	
	Person& operator=(Person &&oldPerson) // a non common move assign. but cool, can be very useful, is faster than normal assign.
	{
		if(this->name_ != nullptr)
		{
			delete name_;
			name_ = nullptr;
		}
		name_ = oldPerson.name_;
		oldPerson.name_ = nullptr;

		return *this;
	}
		
	~Person() // and our destructor , very simple
	{
		if(name_ != nullptr)
		{
			delete name_;
			name_ = nullptr;
		}
	}

private:
	std::string *name_;
	
	
};






int main()
{

	Person oldPerson("makazian"), youngPerson("blueer");
	
	std::vector<Person> persons;

	
	//	persons.push_back(oldPerson); error , cuz this uses the deleted function, the Copy Constructor. But we can use the MOVE constructor.
	
	
	
	
	persons.push_back(std::move(oldPerson));  // so we moved the oldPerson, that means his name now is null
	
	std::cout << oldPerson.getName() << std::endl; // nullptr

	std::cout << persons.back().getName() << std::endl; // makazian

	
	
	
	oldPerson = std::move( persons.back() ); // now person got his name back

	// all that std::move does is a cast , cast things to rvalue
		
	
	std::cout << persons.back().getName() << std::endl; // nullptr

	std::cout << oldPerson.getName() << std::endl; // makazian
	
	persons.back() = youngPerson; // now the Person in the back() of the container, is a copy of younPerson

	std::cout << persons.back().getName() << std::endl; // blueer

	std::cout << youngPerson.getName() << std::endl; // blueer

	// and ... we can allocate directly in the container 
	
	persons.emplace_back("emplaced back Person"); // the container allocates a Person with name "emplaced back Person", and put it in the back

	std::cout << persons.back().getName() << std::endl; // emplaced back Person


	//OUTPUT
	//nullptr
	//makazian
	//nullptr
	//makazian
	//blueer
	//blueer
	//emplaced back Person 
}
