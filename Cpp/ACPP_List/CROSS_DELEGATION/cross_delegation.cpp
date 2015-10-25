#include <iostream>
#define LOG(x) std::cout << x << std::endl;




class Storable
{
public:
	Storable(const char* msg) { LOG("Storable Created - " << msg); }
	virtual void read() = 0; // this becomes pure virtual making storable an abstract
	virtual void write() { LOG("Storable write called "); };// class
	virtual ~Storable() {LOG("Destroying Storable ...")}
protected:
	Storable(){};

private:
	//....


};




class Transmitter : public virtual Storable
{
public:
	//Transmitter(const char *msg) : Storable(msg) {LOG("Transmitter Constructor Called ..."); }
	void write()
	{
		LOG("Called Transmitter Write ...");
		read();
		// ....
	}

	void transmitter_check()
	{
		LOG("cheking transmitter signal ...");
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

/* NOTE:
	
		There is no need now, for Transmitter and Receiver have a CONSTRUCTOR which take const char* parameter to pass on Storable,

		Because Transmitter and Receiver are not instantiable classes. both of them have 1 pure virtual method which only gets
		concrete on Radio Class. 


*/




class Radio : public Transmitter, public Receiver
{
public:
	Radio(const char *msg) : Storable(msg) { LOG("Radio Created ...");}
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

	//receiver->write(); // calls Transmitter class Write()




	/*

		Other Considerations when using multiple inheritance in C++

		When you use a class that is based on virtual inheritance like Radio,
		you should avoid using C style casts and use the C++ specific dynamic_cast instead.

		It will perform a runtime check for validity before casting. so you can be sure that the type of the object
		you want to cast is related (by inheritance), with the object type you want to cast into.
		if they are not related, the result will be a NULL pointer or a bad_cast exception in case of references.

	*/

	// dynamic_cast fail example;

	// lets allocate just a Receiver, cuz we want just Receive msgs

	Receiver *receiver_ptr = new Receiver("msg receiver");

	// at some point we passed receiver_ptr to a Storable pointer

	Storable *storable_ptr = dynamic_cast<Storable*>(receiver_ptr); // ok as Storable is the base of it all
	// this error is not going to happen cuz Storable is the base for all Transmitter, Receiver, Radio.
	if( storable_ptr == nullptr )
	{
		LOG("receiver_ptr do not point to a Storable compatible object ...")
	}

	// Now at some other point , we dont know if storable_ptr points to a Transmitter, Receiver
	// or Radio. ok, lets try to Transmit something with it...

	// and at some other point we want to pass storable_ptr to a Transmitter * to transmit something

	Transmitter *transmitter_ptr = dynamic_cast<Transmitter *>(storable_ptr);

	// we can't... storable_ptr points to a Receiver only...
	// if we didn't use dynamic_cast, it would get bad
	if(transmitter_ptr == nullptr)
	{
		LOG("storable_ptr do not point to a Transmitter compatible object...");
		
	}
	
	// what happened when we call a pure cast without check ?
	transmitter_ptr = (Transmitter*)( receiver_ptr );
	
	// this will cast no matter what, will just copy binary
	// this can lead to undefined behavior because our object is not of type Transmitter 
	// when we call "write()" will call the write on Storable class, this is already
	// bad, because it is not what WE WANT, WE WANT a Transmitter Write.
	
	transmitter_ptr->write(); // may call wrong function, may get undefined behavior
	
	// and the even worse when call a function that is only defined in Transmitter class
	transmitter_ptr->transmitter_check();


}
