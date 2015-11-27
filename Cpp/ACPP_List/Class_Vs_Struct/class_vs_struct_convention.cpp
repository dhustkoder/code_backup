#include <string>


/*         Class vs Struct
 *
 * 		Classes and Structs behave in the same way, the only difference is : 
 *
 * 		Struct: 	struct members are public by default.
 * 		
 * 		Class: 		class members are private by default.
 */

struct person_t
{
	
	
	std::string name; // public data
	int age;

	
private: // but nothing forbid you from creating private variables or functions...
	std::string secret;
};

class Person
{
	
	
	std::string name_; // private data
	int age_;

	
public: // but nothing forbid you from creating public variables or functions...
	int getAge() const { return age_; }
	void setAge(const int newAge ) {  age_ = newAge; }
	void setName(std::string newName) { name_ = newName; }
	std::string getName() const { return name_; }
};




/*   			Class vs Struct : INHERITANCE
 *
 *
 * 			Struct:	When inheritance is from struct  the default is public. 
 *
 * 			Class:	When inheritance is from class the default is private.
 */

struct fat_person_t : person_t // public inheritance
{
	
};


class FatPerson : Person // private inheritance
{

};


/*               The Convention 
 *
 * 		
 * 		Struct: Small passive objects that carry public data and have no, or few, member functions. ( data container )
 *
 * 		Class: Bigger active objects that carry private data, Interfaced through public member functions. ( complex data structure )
 *
 */



int main()
{
	// interface && convention
	
	person_t boy;
	boy.name = "Jack The Ripper"; // this is ok, cuz structs are for basic data container and may not need interfaces.
	boy.age = 10; 


	Person man;
	man.setName("Vic Boss"); // this is good, cuz Classes need to HIDE IMPLEMENTATION. so any changes in the behavior of class/program are easier to do.
	man.setAge(39);	
	
	
	
	// inheritance	
	
	fat_person_t fat_boy;

	fat_boy.age = 10; // ok cuz default inheritance is public.

	FatPerson fat_man;

	fat_man.getAge(); // not ok cuz default inheritance is private. public must be specified

}
















