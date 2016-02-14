#include <iostream>
#include <vector>

template<class T, class ReturnType, class ...Args>
using MethodPtr = ReturnType (T::*)(Args...);


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
// Example:
class OtherClass
{
public:
	template<class T, class ...Ts>
	auto DoSomething(T x, Ts&& ...args)
	{
		return x(std::forward<Ts>(args)...);
	}
};


class Test
{
	int x = 10;

	int Sum(int a, int b)
	{
		return x += (a + b);
	}

	int Sub(int a, int b)
	{
		return x += (a - b);
	}

	int Mul(int a, int b)
	{
		return x += (a * b);
	}

	void InternalMethod()
	{
		std::cout << "Hi, I'm Test's private method" << std::endl;
	}

public:
	auto callDelegate()
	{
		OtherClass otherObject;
		auto *del = new Delegate<Test,int, int, int>(*this);
		*del = &Test::Sum;
		*del += &Test::Sub;
		*del += &Test::Mul;
		
		// other object calls Test's private method through Delegate
		std::cout << otherObject.DoSomething(*del, 10,10) << std::endl;


		// void return type method...
		auto *del2 = new Delegate<Test, void>(*this);
		*del2 = &Test::InternalMethod;
		
		otherObject.DoSomething(*del2);
	}

};




int main()
{
	Test().callDelegate();
}