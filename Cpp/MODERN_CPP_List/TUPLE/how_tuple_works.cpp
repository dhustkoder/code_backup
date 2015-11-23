#include <iostream>
#include <string>
#include <functional>


/*+++++++ How Tuple Works +++++++ */


// First, some metaprogramming boilerplate, to represent a sequence of integers:

template<int...> struct seq {};

template<int max, int... s> 
struct make_seq :make_seq< max - 1, max - 1, s... > {}; // recursive



template<int... s> struct make_seq<0, s...> 
{
	typedef seq<s...> type;
};

template<int max> 
using MakeSeq = typename make_seq<max>::type;


// Next, the tagged class that actually stores the data:
template<int x, typename Arg>
struct tuple_storage 
{
	Arg data;
};

// This tagging technique is a common pattern whenever we want to associate data with some tag at compile time
// (in this case, an integer). The tag (an int here) isn't used anywhere in the storage usually, it is just used to tag the storage


// tuple_helper unpacks a sequence and a set of arguments into a bunch of tuple_storage,
// and inherits from them in a linear fashion. This is a pretty common pattern -- if you are doing this a lot,
// you end up creating metaprogramming tools that do this for you:
template<typename Seq, typename... Args>
struct tuple_helper
{};


template<int s0, int... s, typename A0, typename ...Args>
struct tuple_helper<seq<s0,s...>, A0, Args...> : tuple_storage<s0,A0>, tuple_helper<seq<s...>, Args...>
{};

// Now the Tuple type, creates a package of a sequence of indexes and the args, and passes it to the helper above,
// the helper then creates a bunch of tagged data holding parent classes:
template<typename... Args>
struct Tuple : tuple_helper< MakeSeq<sizeof...(Args)>, Args... > {};

// in Get function, we take the storage type (not the tuple type), and the explicit template argument N disambiguates
// which of the tuple_storage<n, T> we are going to access. 
// Now that we have the storage type, we simply return the data field:
template< int N, typename T>
T& get(tuple_storage<N, T>& storage) {
	return storage.data;
}

template< int N, typename T>
T const& get(tuple_storage<N, T> const& storage) {
	return storage.data;
}

/* We are using the overloading mechanisms of the C++ language to do the heavy lifting.
	when you call a function with a class instance, that instance as each of the parent classes
	are gone over to see if any of them can be made to match. With the N fixed, the is only one parent class that
	is a valid argument, so parent class (and hence T) is deduced automatically
*/
int main() 
{
	Tuple<int, std::string, char> t;
	get<0>(t) = 30;
	get<1>(t) = "testing tuple";
	get<2>(t) = 'c';

	std::cout << get<0>(t) << std::endl
		<< get<1>(t) << std::endl
		<< get<2>(t) << std::endl;
}