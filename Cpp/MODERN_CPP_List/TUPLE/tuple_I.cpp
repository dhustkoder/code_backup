#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#define LOG(x) std::cout << x << std::endl

/* Tuple:
		different of std::pair a tuple is an template class capable to hold a collection of elements. Each element can be of a different type.
*/


int main() 
{
	std::tuple<int, std::string, char> myTuple(233, "D-Dog", 'Z');
	// the std::get returns a reference to that element in the tuple
	LOG(std::get<0>(myTuple));
	LOG(std::get<1>(myTuple));
	LOG(std::get<2>(myTuple));

	// so we can change it. 
	std::get<1>(myTuple) = "DogMeat";

	LOG(std::get<1>(myTuple));

	// but the index of get<INDEX> must be a compile time constant


	std::tuple<int, std::string, char> myTuple2; // default constructor for inner types.

	myTuple2 = std::make_tuple(100,"tuple2",'c');

	if (myTuple > myTuple2) // lexicographical comparasion
		LOG("tuple1 greater");

	myTuple = myTuple2; // member by member copy


	int x;
	std::string str;
	char y;

	std::make_tuple(std::ref(x), std::ref(str), std::ref(y)) = myTuple;
	// this will tie each element of myTuple to local variables x, str, y

	// we can also do like this, using tie;
	std::tie(x, str, y) = myTuple;

	// we can also...
	std::tie(x, std::ignore, y);


	// now tuple cat
	std::tuple<std::string> myTuple3;

	auto cat_tup = std::tuple_cat(myTuple, myTuple3);
	// cat_tup is a tuple<int, std::string, char, std::string>


	//type traits
	LOG(std::tuple_size<decltype(myTuple)>::value); // print tuple size
	std::tuple_element<1, decltype(myTuple)>::type type;
	// type is std::string



}