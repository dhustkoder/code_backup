#include <iostream>
#include <fstream>
#include "TestList.h"

#define LOG(x) std::cout << x << std::endl

struct List::Node
{
	Node() : next(nullptr), previus(nullptr) {}
	int m_number;
	Node *next;
	Node *previus;
};



List::List() 
	: head(nullptr), tail(nullptr) 
{

}


List::~List()
{
	Node *deleterParser = head;
	while (deleterParser != nullptr)
	{
		Node *to_be_deleted = deleterParser;
		deleterParser = deleterParser->next;
		delete to_be_deleted;
	}

}




bool List::push(int newNumber)
{

	if (head == nullptr) {
		tail = head = new Node();
		head->m_number = newNumber;

		return true;
	}

	Node *newNode = new Node();
	newNode->m_number = newNumber;
	tail->next = newNode;
	newNode->previus = tail;
	tail = newNode;
	return true;
}

void List::pop()
{
	Node *to_be_deleted = tail;
	tail = tail->previus;
	tail->next = nullptr;

	to_be_deleted->previus = nullptr;
	delete to_be_deleted;
}


void List::print()
{
	Node *parser = head;

	while (parser != nullptr) {
		LOG(parser->m_number);
		parser = parser->next;
	}
}


void List::saveToFile(std::string fileName)
{
	std::ofstream logFile(fileName, std::ios::app);
	logFile << "\n\n";
	Node *parser = head;

	while (parser != nullptr) {
		logFile << parser->m_number << std::endl;
		parser = parser->next;
	}
}



bool List::merge(List &rhs)
{
	if (rhs.head == nullptr)
		return false;

	this->tail->next = rhs.head;
	rhs.head->previus = this->tail;
	this->tail = rhs.tail;

	rhs.head = rhs.tail = nullptr;

	return true;

}
bool List::mergeAndDel(List *&rhs)
{
	

	if (rhs == nullptr)
		return false;
	else if (rhs->head == nullptr)
		return false;

	this->tail->next = rhs->head;
	rhs->head->previus = this->tail;
	this->tail = rhs->tail;

	rhs->head = rhs->tail = nullptr;
	delete rhs;

	rhs = nullptr;

	return true;

}




