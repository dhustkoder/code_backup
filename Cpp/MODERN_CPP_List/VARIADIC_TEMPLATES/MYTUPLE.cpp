#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl


// First we declare some taggings

template<typename ...Trest>
struct Tuple; // Declaration


template<>
struct Tuple<>
{
	/* base case */
};


template< typename Tfirst, typename ...Trest>
struct Tuple<Tfirst, Trest...> : Tuple<Trest...>
{
	Tuple() : Tuple<Trest...>(){}
	Tuple(Tfirst&& arg, Trest&& ...args) : 
		Tuple<Trest...>(std::forward<Trest>(args)...), data(std::forward<Tfirst>(arg))
	{

	}
	Tfirst data;
};


template< size_t index, typename Ttype>
struct TupleElement;



// Base Case
template< typename Tfirst, typename ...Trest >
struct TupleElement<0, Tuple<Tfirst, Trest...>>
{
	using type_t = Tfirst;
	using TupleType_t = Tuple<Tfirst, Trest...>;
};

template<size_t idx, typename Tfirst, typename ...Trest>
struct TupleElement<idx, Tuple<Tfirst, Trest...>>
	: TupleElement<idx - 1, Tuple<Trest...>>
{
	/*empty*/
};


template<size_t index, typename ...Ttypes>
typename TupleElement<index,Tuple<Ttypes...>>::type_t&
get(Tuple<Ttypes...> &tup)
{
	using TupleType_t = TupleElement<index, Tuple<Ttypes...>>::TupleType_t;

	return static_cast<TupleType_t&>(tup).data;
}


int main() {

	Tuple<int, char, std::string> t(10, 'c',"No Pain No Gain");

	LOG(get<2>(t));

	TupleElement<0, Tuple<int, char, std::string>>::type_t int_variable;
	TupleElement<1, Tuple<int, char, std::string>>::type_t char_variable;
	TupleElement<2, Tuple<int, char, std::string>>::type_t string_variable;

	TupleElement<0, Tuple<int, char, std::string>>::TupleType_t int_char_string_tuple;
	TupleElement<1, Tuple<int, char, std::string>>::TupleType_t char_string_tuple;
	TupleElement<2, Tuple<int, char, std::string>>::TupleType_t string_tuple;
}
