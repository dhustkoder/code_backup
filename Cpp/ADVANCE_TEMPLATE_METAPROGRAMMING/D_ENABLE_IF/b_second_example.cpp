#include <iostream>
#define LOG(x) std::cout << x << std::endl


// ENABLE_IF, A single-type variant on conditional


// IF true give back the givin type, if false give nothin


// first the helper

template<class T>
struct type_is { using type = T; };



// now the enable_if

// this first declaration assumes that condition is true
template<bool, class T>
struct enable_if : type_is<T> {};



// now the specialization for false

template<class T>
struct enable_if<false,T> {}; // no type at all



// how this helps ?

// consider the following structs, lets try some static polymorphism
struct Banana { void eat() { LOG("ate a Banana"); } };
struct Wine { void drink() { LOG("drank a glass of wine");}};
struct Weapon{ void attack(){LOG("attacked with weapon");}};


//helper
struct false_type { static constexpr bool value = false;};
struct true_type { static constexpr bool value = true;};


// type_traits for Banana, Wine, Weapon
template<class T>
struct is_eatable : false_type{};
template<>
struct is_eatable<Banana> : true_type {};

template<class T>
struct is_drinkable : false_type{};
template<>
struct is_drinkable<Wine> : true_type {};

template<class T>
struct is_weapon : false_type{};
template<>
struct is_weapon<Weapon> : true_type {};



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
	Wine wine;
	Weapon weapon;

	useItem(bana);
	useItem(wine);
	useItem(weapon);
}

// imagine we add other class that is-a relationship
struct Sword : Weapon
{
	void attack() { LOG("you attacked with a Sword"); }
};
// lets add the specialization for sword
template<>
struct is_weapon<Sword> : true_type{};

// and do again
int main()
{
	
	Banana bana;
	Wine wine;
	Weapon weapon;
	Sword weapon_sword;
	useItem(bana);
	useItem(wine);
	useItem(weapon);
	useItem(weapon_sword);

}










