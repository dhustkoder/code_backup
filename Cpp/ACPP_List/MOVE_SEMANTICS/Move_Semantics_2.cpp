#include <iostream>

// A different implement , using swaps.
struct disc_t
{
	std::string label;
};

class CdCase
{
public:
	CdCase(int capacity) :
		discs_(nullptr), n_of_discs_(capacity)
	{
		
		discs_ = new disc_t[capacity];
		discs_[capacity - 1].label = "Last Disc";
	}


	CdCase(const CdCase &rhs) :
		CdCase(rhs.n_of_discs_)
	{
		std::copy_n(rhs.discs_,rhs.n_of_discs_, this->discs_);
	}



	CdCase(CdCase&& rhsMove) :
		discs_(nullptr), n_of_discs_(0)
	{
		std::swap(this->discs_, rhsMove.discs_);
		std::swap(this->n_of_discs_, rhsMove.n_of_discs_);
	}


	~CdCase()
	{
		delete[] discs_;
	}
private:
	disc_t *discs_;
	int n_of_discs_;
};

/*
int main()
{
	
	CdCase cdCase1(20000);

	CdCase copy(cdCase1);


	CdCase move(std::move(copy));

}

*/