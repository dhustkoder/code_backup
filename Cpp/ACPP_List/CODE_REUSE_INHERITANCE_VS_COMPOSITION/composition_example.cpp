


class Motor
{};





class Car
{
public:
	Car() : m_motor(new Motor){}

	~Car() { delete m_motor; }

private:
	Motor *m_motor; // composition.
};


// "Car" Has-A RelationShip with the Motor, that means: "Car" is not a type of "Motor", but "Car" have a "Motor" that make total sense.


// This leads us to the Rule: In COMPOSITION when the owning object ("Car") is destroyed, so is its contained objects ("Motor").
// So lets Talk about Aggregation

