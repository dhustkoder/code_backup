#include <iostream>
#include <string>
#include <typeinfo>
#define LOG(x) std::cout << x << std::endl



class File
{
friend class InputFile; 
friend class OutputFile;
public:
	File(const std::string &fileName) : name(fileName) {LOG("creating File class"); }
	File(std::string &&fileName) : name(std::move(fileName)) { LOG("creating File class"); }
	
	void open()
	{
		LOG("using File base class Open");
	}
	void setName(const std::string &newName)
	{
		LOG("using copy setName");	
		this->name = newName;	
	}
	void setName(std::string &&newName)
	{
		LOG("using move setName");
		this->name = std::move(newName);
	}
protected:
	std::string name;

};


class InputFile : virtual public File
{
public: 
	InputFile(const std::string &fileName) : File(fileName) { LOG("creating InputFile class"); }

	void read()
	{
		LOG("Reading from " << name );
	}

};



class OutputFile : virtual public File
{
public:
	OutputFile(const std::string &fileName) : File(fileName) { LOG("creating OutputFile class"); }

	void write()
	{
		LOG("Writing to " << name);
	}

};


class IOFile : public InputFile, public OutputFile
{
public:
	IOFile(const std::string &fileName) : InputFile(fileName), OutputFile(fileName), File(fileName) { LOG("creating IOFile class"); }


};


int main()
{
	IOFile file("hello");

	file.open();
	file.setName("hello");

	file.read();
	file.write();
}












