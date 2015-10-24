#include <iostream>
#define LOG(X) std::cout << X << std::endl;


// Multiple Inheritance is an Controversal topic, some people belive it complicate the design and debuggers have a hard time with it,
// but lets see what are the pitfalls , and benefits that it can bring.



// the benefit is implementation reuse, we have already a class to read files, and other class to write to files


class InputFile___
{
public:
	void read() { LOG("using InputFile read"); }
};



class OutputFile___
{
public:
	void write() {LOG("using OutputFile Write"); }
};



// then we can create a class that does both read & write

class IOFile___ : virtual public InputFile___, virtual public OutputFile___
{



};

// so far so good

// but we need all classes to have a common function, a openFile function cuz obviously we need to open a file before writting to it

class InputFile__
{
public:
	void open() { LOG("using InputFile open");	} 
	void read() { LOG("using InputFile read"); 	}
};



class OutputFile__
{
public:
	void open() { LOG("using OutputFile open");	}
	void write() {	LOG("using OutputFile Write"); }
};



// now there is a problem, when we use:
// IOFile file; file.open();

// the compiler will not know which function to call, open from InputFile or OutputFile??
// there are many ways to overcome this problem.

// we can specify which one we want when making the call:
// file.InputFile::open(); this will call InputFile open;

// or we can add using to IOFile class:
class IOFile__ : virtual public InputFile__, virtual public OutputFile__
{
public:
	using InputFile__::open;
	// now file.open(); will compile and the compiler will call the InputFile::open;
	
	// but, still we will have 2 identical functions, for the same goal. this is ugly, and not the best solution...

};

// What we can do is a simple class File that keep the fileName and open a file.
// a Base class from which Input and OutputFile will share its common members.
class File_
{
public:
	File_ () { LOG("creating File_"); }
	void open(const std::string &name) { name_ = name; LOG("using File open"); }
	
protected:
	std::string name_;

};


class InputFile_ : public File_
{
public:
	InputFile_() { LOG("creating InputFile_ "); } 
	void read() { LOG("using InputFile read"); }
};



class OutputFile_ : public File_
{
public:
	OutputFile_ () { LOG("creating OutputFile_ "); }
	void write() {LOG("using OutputFile Write"); }
};



// all right , but there is still a problem, InputFile inherite from File, as do OutputFile...
// so InputFile has a open and a name, as do OutputFile, so the code still will not compile the call is still ambiguous
// no, is even worse, when we instanciate IOFile we will instanciate 2 instances of File. one instanciated for InputFile and other for OutputFile.
// this is terrible. 
//it is called Diamon Shape Hierarchy

/*
				File
				/  \
	          /      \
	OutputFile       InputFile
			 \       /
			   \   /
			   IOFile

*/

class IOFile_ : public InputFile_, public OutputFile_
{



};


// But there is a simple solution by placing virtual keyword before the public when inheriting from File


class File
{
public:
	File (std::string name) : name_(std::move(name)) { LOG("creating File " << name_); }
	void open() { LOG("using File open"); }
	
protected:
	std::string name_;
	File() { LOG("Creating File default contructed"); }

};


class InputFile : virtual public File
{
public:
	InputFile(std::string name) : File(std::move(name))  { LOG("creating InputFile " << name_); } 
	void read() { LOG("using InputFile read on " << name_); }
protected:
	InputFile() { LOG("InputFile default constructed"); }
};



class OutputFile : virtual public File
{
public:
	OutputFile (std::string name) : File(std::move(name)) { LOG("creating OutputFile" << name_); }
	void write() {LOG("using OutputFile Write on " << name_ ); }
protected:
	OutputFile() {LOG("OutputFile default contructed"); };
};

// Now it is ok, our code is perfect, no ambiguity nor multiple instances. 
// But note that I added a constructor that take a parameter on File class. now we have to initialize File from its derived classes.

// now this is a important rule in multiple inheritance: 
// 		The Initialization of the Base Class , is responsability of the most derived class.

class IOFile : public InputFile, public OutputFile
{
public:
	IOFile(std::string name) : File(std::move(name)),	InputFile(), OutputFile() {}


};


// Notice how I created Default Constructors for InputFile , OutPutFile and File, but these Default Constructors are PROTECTED , so only
// Derived classes can call it.

// In this Case , the parameter STD::STRING NAME, is only passed for InputFile and OutputFile to construct FILE class, as IOFile passes the NAME for FILE constructor,
// there is no need to pass it again for InputFile and OutputFile, so we call the PROTECTED Default Constructor.


int main()
{

	

	/*

		Other Considerations when using multiple inheritance in C++

		When you use a class that is based on virtual inheritance like Radio,
		you should avoid using C style casts and use the C++ specific dynamic_cast instead.

		It will perform a runtime check for validity before casting. so you can be sure that the type of the object
		you want to cast is related (by inheritance), with the object type you want to cast into.
		if they are not related, the result will be a NULL pointer or a bad_cast exception in case of references.



	*/










	
	IOFile file("LALA");
	file.open();
	file.read();
	file.write();
}
