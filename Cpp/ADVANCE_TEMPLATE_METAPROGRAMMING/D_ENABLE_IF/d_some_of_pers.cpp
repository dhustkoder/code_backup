#include <iostream>
#define LOG(x) std::cout << x << std::endl


// ENABLE_IF, A single-type variant on conditional


// IF true give back the givin type, if false give nothin


// first the helper

template<class T>
struct type_is { using type = T; };

//helper
struct false_type { static constexpr bool value = false;};
struct true_type { static constexpr bool value = true;};

// IF 
template<bool, class T, class F>
struct IF : type_is<T> {};

template<class T, class F>
struct IF<false,T,F> : type_is<F> {};



// Just a variation of is_one_of, using IF and std::is_same
template<class T, class T2, class ...Ts>
struct is_one_of : IF<std::is_same<T,T2>::value, true_type, is_one_of<T,Ts...>>::type{};

template<class T, class T2>
struct is_one_of<T,T2> : IF<std::is_same<T,T2>::value, true_type, false_type>::type {};



// now the enable_if

// this first declaration assumes that condition is true
template<bool, class T>
struct enable_if : type_is<T> {};

// now the specialization for false

template<class T>
struct enable_if<false,T> {}; // no type at all






struct Banana { void eat() { LOG("ate a Banana"); }};
struct Meat   { void eat() { LOG("ate Meat");     }};
struct Wine   { void drink() { LOG("drank a glass of wine");}};
struct Potion { void drink() { LOG("drank a Potion"); }};
struct Sword  { void attack(){LOG("attacked with Sword");}};
struct Axe    { void attack(){LOG("attacked with Axe");}};

// NOW here our code gets better

template<class T>
struct is_eatable : is_one_of<T, Banana, Meat> {};


template<class T>
struct is_drinkable : is_one_of<T, Wine, Potion> {};

template<class T>
struct is_weapon : is_one_of<T, Sword, Axe> {};



template<class T>
typename enable_if<is_eatable<T>::value, void>::type
useItem(T& item){
	item.eat();
}

template<class T>
typename enable_if<is_drinkable<T>::value, void>::type
useItem(T& item){
	item.drink();
}

template<class T>
typename enable_if<is_weapon<T>::value, void>::type
useItem(T& item){
	item.attack();
}


// there we go , this works like Overload but can be better because we can use kinda like polymorphism
// but without the cost of vtable / dynamic_cast / virtual functions

void workWithItems()
{
	Banana bana;
	Meat meat;
	Wine wine;
	Potion potion;
	Sword sword;
	Axe axe;

	useItem(bana);
	useItem(meat);
	useItem(wine);
	useItem(potion);
	useItem(sword);
	useItem(axe);
}



int main()
{
	workWithItems();

}








