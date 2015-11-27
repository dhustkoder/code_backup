#include <iostream>


// here we have a simple node struct, with its right, left, and imagine we actualy have some data to work with
struct TreeNode { TreeNode *left = nullptr, *right = nullptr ; /* data ... */ };

// and a normal Dynamic Polymorphism Implementation
class Generic_Parser
{
public:
	void parsePreorder(TreeNode *node)
	{
		if( node != nullptr )
		{
			processNode( node );
			parsePreorder(node->left);
			parsePreorder(node->right);
		}

	}
private:
	virtual void processNode(TreeNode *node)
	{
		std::cout << "Generic_Parser processNode" << std::endl;
		
	}


};


class EmployeeChart_Parser : public Generic_Parser
{
private:
	void processNode(TreeNode *node)
	{
		std::cout << "doing EmployeeChart_Parser processNode" << std::endl;
	}
};


class MilitaryChart_Parser : public Generic_Parser
{
private:
	void processNode(TreeNode *node)
	{
		std::cout << "doing MilitaryChart_Parser processNode" << std::endl;
	}

};


int main()
{
	// and this is Polymorphism as we already know, we can use a pointer from base class to use its API , but will access the
	// needed derived class's functions if the called function is virtual

	// but Dynamic Polymorphism comes with a SMALL performance price, the virtual table , dynamic binding.
	// So we will take a look into Static Polymorphism
	Generic_Parser	*employeeParser = new EmployeeChart_Parser;
	Generic_Parser	*militaryParser = new MilitaryChart_Parser;
	TreeNode tree;

	employeeParser->parsePreorder(&tree); //"doing EmployeeChart_Parser processNode"
	militaryParser->parsePreorder(&tree); //"doing MilitaryChart_Parser processNode"

	delete employeeParser;
	delete militaryParser;

}





















