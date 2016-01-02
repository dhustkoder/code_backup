#include <iostream>
#include <vector>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl
#define DCLT(x) decltype(x)
// C++14 code ...

template<typename ...Ts>
constexpr void printTypes() noexcept
{
	return (void)std::initializer_list<int>
	{
		(LOG(boost::typeindex::type_id_with_cvr<Ts>().pretty_name()), 0)...
	};
}


std::vector<int> createKeyVec() {
	return{ 20,30,40 };
}



void authenticateUser() noexcept
{
	return;
}


template<typename Container, typename Index>
decltype(auto) authAndAccess(Container& c, Index i) 
{
	authenticateUser();
	return c[i];
}


// rvalue references specialization
template<typename Container, typename Index>
auto authAndAccess(Container&& c, Index i)
{
	authenticateUser();
	return c[i];
}

int main()
{
	decltype(auto) x = authAndAccess(createKeyVec(), 0);
	LOG(x); // doe to the specialization for rvalue references, this works ok

	auto keyVec = createKeyVec();

	// as this returns a reference to the key, normaly...
	authAndAccess(keyVec, 0) = 50;

	LOG(keyVec[0]);

}