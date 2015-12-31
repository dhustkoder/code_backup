#include <iostream>
#include <boost/type_index.hpp>
#define LOG(x) std::cout << x << std::endl

// using decltype do define a function template that the return type
// depends on the type of template parameter

// supose we'd like to write a function that takes a container that support indexing via square brackets ("[]")
// plus a index, then authenticates the user before returning the result of the indexing operation.

// the return type of the function should be the same as the type returned by the indexing operation ( [] )

// operator [] of a container typically returns T& . That is the case of std::deque, for example, and it's almost the case
// for std::vector. For std::vector<bool>, however , operator[] return a brand new object, is T operator[]

// but what is important here is that the type returned by a container's operator[] depends on the container

// decltype


int main()
{





}
