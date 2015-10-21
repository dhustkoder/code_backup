#include <iostream>

// here we have a simple node struct, with its right, left, and imagine we actualy have some data to work with
struct TreeNode { TreeNode *left = nullptr, *right = nullptr ; /* data ... */ };



// and we create a Generic_Parser class that will act as base class for other specific Parsers...
// Generic_Parser will have the default functions , but ProcessNode must be defined in derived classes 
template<typename T>
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
	void processNode(TreeNode *node)
	{
		// some default stuf maybe.....
		// and then call the right processNode from a derived class
		static_cast<T*>(this)->processNode(node);
	
	}


};


class EmployeeChart_Parser : public Generic_Parser<EmployeeChart_Parser>
{
friend class Generic_Parser;

private:
	void processNode(TreeNode *node)
	{
		std::cout << "doing EmployeeChart_Parser processNode" << std::endl;
	}
};


class MilitaryChart_Parser : public Generic_Parser<MilitaryChart_Parser>
{
friend class Generic_Parser;
private:
	void processNode(TreeNode *node)
	{
		std::cout << "doing MilitaryChart_Parser processNode" << std::endl;
	}

};


int main()
{
	// this technique is called Curiusly Recurring Template Pattern ( Static Polymorphism, or Simulated Polymorphism)
	// We can use the Generic_Parser as it is a true Polymorphic Base Class, except for having to define templates.

	// But Static Polymorphism comes with a price too, our code may use too much templates, it will be Less Flexible
	// Cuz I cant Derive from MilitaryChart_Parser or EmployeeChart_Parser properly, the code will get confusing.
	// but for small things, the boost in performance can be worth it.

	Generic_Parser<EmployeeChart_Parser> *employeeParser = new EmployeeChart_Parser;
	Generic_Parser<MilitaryChart_Parser> *militaryParser = new MilitaryChart_Parser;
	TreeNode tree;

	employeeParser->parsePreorder(&tree); //"doing EmployeeChart_Parser processNode"
	militaryParser->parsePreorder(&tree); //"doing MilitaryChart_Parser processNode"

	delete employeeParser;
	delete militaryParser;

}





















