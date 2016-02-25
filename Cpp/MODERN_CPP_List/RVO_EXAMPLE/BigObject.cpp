#include <iostream>
#include "BigObject.h"
#define LOG(x) std::cout << x << std::endl

BigObject::BigObject()
	: m_data(nullptr)
{
	LOG("DEFAULT CONSTRUCTOR");
}

BigObject::BigObject(char y)
	: m_data(new char(y))
{
	LOG("CONSTRUCTOR");
}

BigObject::BigObject(const BigObject& other)
	: m_data(new char(*other.m_data))
{
	LOG("COPY CONSTRUCTOR");
}

BigObject::BigObject(BigObject&& other)
	: m_data(other.m_data)
{
	other.m_data = nullptr;
	LOG("MOVE CONSTRUCTOR");
}

BigObject::~BigObject()
{
	delete m_data;
	LOG("DESTRUCTOR");
}

const BigObject& BigObject::operator=(const BigObject& other)
{
	LOG("COPY ASSIGN OPERATOR");
	*m_data = *other.m_data;
	return *this;
}

const BigObject& BigObject::operator=(BigObject&& other)
{
	LOG("MOVE ASSIGN OPERATOR");
	m_data = other.m_data;
	other.m_data = nullptr;
	return *this;
}

void BigObject::setData(char y)
{
	if (m_data == nullptr)
		m_data = new char(y);
	else	
		*m_data = y;
	
}













BigObject create_rvo(char y)
{
	return BigObject(y);
}


BigObject create_nrvo(char y)
{
	BigObject x;
	x.setData(y);
	return x;
}

BigObject create_move(char y)
{
	BigObject x;
	x.setData(y);
	return std::move(x);
}
