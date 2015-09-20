#include <iostream>






class NuclearWarhead
{
public:
	NuclearWarhead(float megatons)
	{
		megatons_ = megatons;
		exploded_ = false;

	}
	void explode()
	{
		if( not exploded_ )
		{
			// explode ......
			std::cout << "!!!!!!!!!!!!!!!!!! " << megatons_ <<  " MEGATONS EXPLOSIOOOOON !!!!!!!!!!!!!!" << std::endl;
		}
		else
			std::cout << "the nuke is already destroyed" << std::endl;


		exploded_ = true;
	}


private:	
	float megatons_;
	bool exploded_;


};




class MetalGear
{
public:
	MetalGear(NuclearWarhead *nuke)
	{
		nuclearWeapon_ = nuke;

	}
	void fireNuke()
	{
		if(nuclearWeapon_ != nullptr)
		{
			nuclearWeapon_->explode();
			nuclearWeapon_ = nullptr;
		}
		else
			std::cout << "Nuclear Weapon is empty" << std::endl;	
	}
	
	~MetalGear()
	{
		std::cout << "Re-Loading Metal Gear's nuclear weapon" << std::endl;
	}
private:
	NuclearWarhead *nuclearWeapon_;
	
};






int main()
{
	NuclearWarhead nuke(100);

	MetalGear rex(&nuke); // normal constructor call

	rex.fireNuke(); // explosion
	rex.fireNuke();	// nuclear weapon is empty

	rex = &nuke; // type conversion constructor, destroy reconstruct the same object  with the new constructor parameter
	
	rex.fireNuke(); // the nuke is already destroyed

	
	// if the explicit keyword is in MetalGear constructor, we cant do
	// rex = &nuke;
}





