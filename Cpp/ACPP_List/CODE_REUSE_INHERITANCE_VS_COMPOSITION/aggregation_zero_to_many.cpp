class Professor{};




#define DEPARTAMENT_MAX_PROFESSORS 20
class Departament
{
public:
	Departament(Professor *initialProf)
	{
		std::fill_n(m_members,DEPARTAMENT_MAX_PROFESSORS, nullptr);
		m_numberOfMembers = 0;
		if(initialProf == nullptr)
			return
		
		m_members [ m_numberOfMembers++ ] = initialProf;

	}
	bool addProfessor(Professor *newProf)
	{
		if(newProf == nullptr || m_numberOfMembers >= DEPARTAMENT_MAX_PROFESSORS)
			return false;

		m_members [ m_numberOfMembers ++ ] = newProf;


	}

	~Departament() { std::fill_n(m_members,DEPARTAMENT_MAX_PROFESSORS, nullptr); }
private:
	Professor *m_members [ DEPARTAMENT_MAX_PROFESSORS ];
	int m_numberOfMembers;
};




// this is an example of how Flexible Composition & Aggregation can be.


// DEPARTAMENT Can HAVE MANY PROFESSOR, and MULTIPLE TYPES OF PROFESSORS cuz PROFESSOR can be just a BASE CLASS/interface.


/* Code Reuse: Where Composition Is Better Than Inheritance


	1. Less Code Coupling between the reused code, and the Reuser of the code
			
			a. Derived Classes automaticaly inherit all the Base public members.

			b. Derived classes can access the Base Protected members
				- breaks encapsulation.



	2. Dynamic Binding

		a. Inheritance is bind at compile time.


		b. Composition can be bind at compile-time or run-time



	3 Flexible Code Construct
*/