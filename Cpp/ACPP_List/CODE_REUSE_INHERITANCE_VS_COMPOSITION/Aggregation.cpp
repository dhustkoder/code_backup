

class Professor {};





class Departament
{
public:
	Departament(Professor *initialProf)
	{
		assert(initialProf != nullptr);

		m_professor = initialProf;
	}

	~Departament() {};

private:
	Professor * m_professor;
};


// Aggregation is a type of COMPOSITION where the contained object can still "LIVE", after the owning object is destroyed.

// Departament have professor, but when the Departament closes the Professors still lives.