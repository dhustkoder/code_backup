#include <iostream>
#include <string>
#include <type_traits>
#define LOG(x) std::cout << x << std::endl


template<typename ...Ttypes> struct Tuple; // Declaration

template<> class Tuple<> { /* empty */};


template<typename Tvalue, typename ...Trest>
struct Tuple<Tvalue, Trest...> : Tuple<Trest...>
{
	Tvalue data;
};

template<size_t idx, typename Ttuple>
struct TupleElement; // Declaration



// The 0th element  (base case)
template<typename Tvalue, typename ...Trest>
struct TupleElement<0, Tuple<Tvalue, Trest...> >
{
	using type_t = Tvalue; // type of the DATA of this index
	using TupleType_t = Tuple<Tvalue, Trest...>; // the type of the Tuple
};



template<size_t idx, typename Tvalue, typename ...Trest>
struct TupleElement<idx, Tuple<Tvalue, Trest...>>
	: TupleElement<idx - 1, Tuple<Trest...>>
{
	/*empty*/
};

template<size_t idx, typename ...Ttypes>
typename TupleElement<idx,Tuple<Ttypes...>>::type_t& 
get(Tuple<Ttypes...> & t) {
	using TupleType_t 
		= typename TupleElement<idx, Tuple<Ttypes...>>::TupleType_t;

	return static_cast<TupleType_t&>(t).data;
}



int main() 
{
	Tuple<int, char, std::string> myTup;
	get<2>(myTup) = "hello";
	get<1>(myTup) = 'y';
	get<0>(myTup) = 200;
	LOG(get<0>(myTup));






	// this tup creates the following inheritance pattern


	/*
			Tuple<>
				|
			Tuple<std::string>
				|
			Tuple<char,std::string>
				|
			Tuple<int , char , std::string>
	
	*/

	
}