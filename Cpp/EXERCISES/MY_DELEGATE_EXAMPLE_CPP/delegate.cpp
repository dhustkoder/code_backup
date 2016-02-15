#include <iostream>
#include <vector>
#include <string>

// just a literal helper for strings
std::string operator"" _s(const char* x, unsigned long) { return std::string(x); }


// template for any Method pointer
template<class T, class ReturnType, class ...Args>
using MethodPtr = ReturnType (T::*)(Args...);




//-------------------------------------
//-------------------------------------
// SimpleDelegate implementation ( one method only )

template<class T, class ReturnType, class ...Ts>
class SimpleDelegate
{
	using TMethod = MethodPtr<T, ReturnType, Ts...>;
public:
	inline SimpleDelegate(T& ref) :
		m_ref(ref)
	{

	}

	inline void operator=(TMethod method) {
		m_method = method;
	}

	inline ReturnType operator()(Ts&& ...args) {
		return ((m_ref).*(m_method))(std::forward<Ts>(args)...);
	} 

protected:
	T& m_ref;
	TMethod m_method;
};





//-------------------------------------
//-------------------------------------
// Vector Delegate implementation ( can hold multiple methods and call all them )

template<class T, class ReturnType, class ...Ts>
class DelegateBase
{
	using TMethod = MethodPtr<T, ReturnType, Ts...>;
public:
	DelegateBase(T& ref) :
		m_ref(ref)
	{

	}

	void operator+=(TMethod method)
	{
		m_methods.push_back(method);
	}

	void operator=(TMethod method)
	{
		m_methods.clear();
		m_methods.push_back(method);
	}

protected:
	T& m_ref;
	std::vector<TMethod> m_methods;
};


template<class T, class ReturnType, class ...Ts>
class Delegate : public std::enable_if_t<!std::is_void<ReturnType>::value, DelegateBase<T, ReturnType, Ts...>>
{
	using Base = DelegateBase<T, ReturnType, Ts...>;
public:
	Delegate(T& ref) : DelegateBase<T, ReturnType, Ts...>(ref) {}

	ReturnType operator()(Ts&&...args)
	{
		ReturnType result = ((Base::m_ref).*(Base::m_methods[0]))(std::forward<Ts>(args)...);

		for (auto itr = Base::m_methods.begin() + 1; itr != Base::m_methods.end(); ++itr)
		{
			result += ((Base::m_ref).*((*itr)))(std::forward<Ts>(args)...);
		}

		return result;
	}

	using Base::operator=;

};


// void specialization
template<class T, class ...Ts>
class Delegate<T, void, Ts...> : public DelegateBase<T, void, Ts...>
{
	using Base = DelegateBase<T, void, Ts...>;
public:
	Delegate(T& ref) : DelegateBase<T, void, Ts...>(ref) {}
	void operator()(Ts&&...args)
	{

		for (auto& method : Base::m_methods)
		{
			((Base::m_ref).*(method))(std::forward<Ts>(args)...);
		}
	}
	using Base::operator=;

};






// -----------------------------------------------------------
// -----------------------------------------------------------
// -----------------------------------------------------------
// -----------------------------------------------------------
// Use Example:


class MonsterA
{


public: // public statics api
	enum class Level { Easy, Hard };
	static std::string GetName() { return "MonsterA"; }
	


public: // public api
	MonsterA(Level x)
	{
		switch(x)
		{
			case Level::Easy: m_shootDmgDel = &MonsterA::TakeShootOnEasy; break;
			case Level::Hard: m_shootDmgDel = &MonsterA::TakeShootOnHard; break;
		}
	}

	void TakeShootDamage(const std::string& msg) {
		m_shootDmgDel(msg);
	}	
private: // private methods
	void TakeShootOnEasy(const std::string &msg) {
		std::cout << msg << std::endl 
			<< "The Monster Dies..." << std::endl;
	}

	void TakeShootOnHard(const std::string &msg) {
		std::cout << msg << std::endl
			<< "The Monster Lives and Counter-Attack..." << std::endl;
	}

private: // private members

	SimpleDelegate<MonsterA, void, const std::string&> m_shootDmgDel{*this};
};

void use_gun(MonsterA &monster)
{
	monster.TakeShootDamage("Player Shoots the "_s + monster.GetName());
}

int main()
{
	MonsterA monster1(MonsterA::Level::Easy); // piece of cake monster
	MonsterA monster2(MonsterA::Level::Hard); // die hard monster

	use_gun(monster1);
	use_gun(monster2);
}
