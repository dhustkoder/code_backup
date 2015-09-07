#include <iostream>
#include <vector>
#include <string>


class Person
{
public:
	Person(std::string name) :  name_ ( nullptr )
	{
		name_ = new std::string(std::move(name));	
	}
	
	
	Person(const Person&) = delete;
	Person(Person&& oldPerson)
	{
		delete this->name_;
		this->name_ = oldPerson.name_;
		oldPerson.name_ = nullptr;	
	}
	
	std::string getName() const
	{
		
		return (name_ != nullptr) ? *name_ : "nullptr";
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
	
	
	
	
	
	
	Person& operator=(Person &person)
	{
		if(name_ != nullptr)
		{
			delete this->name_;
			name_ = nullptr;
		}
		
		if(person.name_ != nullptr)
			this->name_ = new std::string(person.name_->c_str());

		return *this;
	
	}
	
	
	~Person()
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

	oldPerson = persons.back();

	persons.back() = youngPerson; 
}
