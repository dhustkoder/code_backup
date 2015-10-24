#include <iostream>
#define LOG(x) std::cout << x << std::endl;




class Storable
{
public:
	Storable(const char* msg) { LOG("Storable Created - " << msg); }
	virtual void read() = 0; // this becomes pure virtual making storable an abstract
	virtual void write() =0;// class
	virtual ~Storable() {LOG("Destroying Storable ...")}
protected:
	Storable(){};

private:
	//....


};




class Transmitter : public virtual Storable
{
public:
	Transmitter(const char *msg) : Storable(msg) {LOG("Transmitter Constructor Called ..."); }
	void write()
	{
		LOG("Called Transmitter Write ...");
		read();
		// ....
	}
	~Transmitter() {LOG("Destroying Transmitter ...")}
protected:
	Transmitter() { LOG("Transmitter Default Constructor Called"); }

};



class Receiver : public virtual Storable
{
public:
	Receiver(const char *msg) : Storable(msg) { LOG("Receiver Constructor Called");}
	void read()
	{
		LOG("Called Receiver Read ...");
	}
	~Receiver() { LOG("Destroying Receiver ..."); }
protected:
	Receiver() { LOG("Receiver Default Constructor Called "); }
};






class Radio : public Transmitter, public Receiver
{
public:
	Radio(const char *msg) : Storable(msg), Transmitter(), Receiver() { LOG("Radio Created ...");}
	// ...
	~Radio() {LOG("Destroying Radio ..."); }
};


int main()
{
	Radio *radio = new Radio("MSG");
	
	Transmitter *transmitter = radio;
	Receiver *receiver = radio;



	/*
		Because of virtual inheritance, when the write() function from the Transmitter Class is Called,
		the method read() from the Receiver Class gets called (as you may have noticed, 
		the Transmitter Class doesn't have a read() function).

		In the above Hierarchy we can instantiate only the Receiver and Radio class.
		Because in the Transmitter class alone, the read() function is pure virtual yet.
		it only gets concrete function when we instanciate a Receiver, or Radio.
		cuz Receiver is where the implementation for Read function is.

		but when we Instanciate a Receiver object, Its write function, will be the one in Storable, not in the,
		Transmitter. So lets make the Write function in Storable pure virtual,
		and now we cant instanciate a Receiver alone.



	*/


	transmitter->read(); // calls Receiver class Read()

	receiver->write(); // calls Transmitter class Write()




	/*

		Other Considerations when using multiple inheritance in C++

		When you use a class that is based on virtual inheritance like Radio,
		you should avoid using C style casts and use the C++ specific dynamic_cast instead.

		It will perform a runtime check for validity before casting. so you can be sure that the type of the object
		you want to cast is related (by inheritance), with the object type you want to cast into.
		if they are not related, the result will be a NULL pointer or a bad_cast exception in case of references.



	*/



}