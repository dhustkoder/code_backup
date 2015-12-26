#include <iostream>
#define LOG(x) std::cout << x << std::endl


// If you are a template author, the tension between parentheses and braces for object
// creation can be specially frustrating, because in general, its not possible to
// know which should be used. Lets take a look at this

template<class T, class ...Ts>
void doSomeWork(Ts&& ...args)
{
	T localObject(std::forward<Ts>(args)...);  // should we use parentheses ?
	//T localObject2{std::forward<Ts>(args)...}; // or braced initialization ?

	localObject.use();
	//localObject2.use();
	//.......
}


struct Widget
{
	Widget(int x, int y){
		LOG("Widget: int, int. constructor");
	}
	
	Widget(std::initializer_list<int> il){
		LOG("Widget: initializer_list ctor");
	}

	void use(){
		LOG("Using Widget");
	}
};


int main(){

	// using 'doSomeWork' like this is going to create a Widget using what constructor ?
	// depends on how doSomeWork is calling the Widgets constructor...
	// if is calling with () will call the first ctor, if is calling with {} will call the initializer_list ctor

	// and for that reason, I think that parentheses should be the default way to initialize an object.

	// lets say that 'doSomeWork' uses parentheses to call the constructor.
	doSomeWork<Widget>(10,20); // this way you call the first ctor
	

	std::initializer_list<int> il = { 10, 20 };	
	doSomeWork<Widget>(std::move(il)); // this way you call the initializer_list ctor.
	// so when the template function uses the parentheses the client have some controll over the construction.	

	// but yes, it is not a  cool thing to do frequently
	
	// this is a problem faced by the standard library functions , std::make_shared and std::make_unique,
	// they resolve the problem by using parentheses and documenting it as part of their interfaces

}

