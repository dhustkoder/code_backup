#include <iostream>
#define LOG(x) std::cout << x << std::endl

class Node
{
	friend class List;
private:
	Node* next;
	Node* previus;
	int value;
public:
	Node(int x) : next(nullptr), previus(nullptr), value(x)
	{

	}

};

class List
{
private:
	Node *head;
	Node *tail;
public:
	List() : head(nullptr), tail(nullptr){}

	template<typename N>
	void push(N &&x)
	{
		if (head == nullptr)
		{
			head = tail = new(std::nothrow) Node(std::forward<N>(x));
			return;
		}

		auto newNode = new(std::nothrow) Node(std::forward<N>(x));

		newNode->next = head;
		head->previus = newNode;
		head = newNode;
	}


	void pop()
	{
		auto toDelete = head;
		head = head->next;
		head->previus = nullptr;
		delete toDelete;
	}

	void listNumbers()
	{
		for (auto itr = head; itr != nullptr; itr = itr->next)
		{
			printf("%i \n", itr->value);
		}

	}

	~List()
	{
		for (auto itr = head; itr != nullptr; )
		{
			auto toDel = itr;
			itr = itr->next;
			delete toDel;
		}
	}



};

void doWork()
{
	List list;

    for (int i = 0; i < 1000000; i++)
    {
	if( i % 2 == 0 )
		list.push(i);
    }

	list.listNumbers();
}


int main()
{
	doWork();
	std::cin.ignore();


	return 0;
}

