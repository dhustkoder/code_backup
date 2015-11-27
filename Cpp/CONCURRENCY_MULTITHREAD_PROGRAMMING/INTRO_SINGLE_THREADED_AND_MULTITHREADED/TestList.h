#ifndef TEST_LIST_H
#define TEST_LIST_H
#include <string>

class List
{
public:
	List();
	void pop();
	bool push(int newNumber);
	void print();
	void saveToFile(std::string fileName);
	bool merge(List &rhs);
	bool mergeAndDel(List *&rhs);
	~List();
private:
	struct Node;
	Node *head;
	Node *tail;

};
#endif
