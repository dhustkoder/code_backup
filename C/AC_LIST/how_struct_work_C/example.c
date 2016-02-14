#include <stdio.h>
#include <stdlib.h>
#include <assert.h>





// considering this struct

struct Item_t
{
	const char* _name;
	int weight;
};


int main(){

	assert(sizeof(char*) == 8);
	assert(sizeof(int) == 4);
	
	//considering that char* is 8 bytes and int 4 bytes:
	
	// the Item_t should look like this in memory  { | --- 8 bytes --- | - 4 bytes - | } 
	
	// we will manualy interact with it in memory in C for demonstration.
	
	
	void *ptr = malloc(12);
	
	// Yay we have now a pointer to a location in memory with 12 bytes for our use
	
	
	// lets treat this memory space as we would do with a pointer of type Item_t
	
	// the pointer is already to the first element of struct (const char*)
	
	*((const char**)ptr) = "Hello Memory Space";
	
	printf("%s !!\n",*((const char**)ptr));
	
	// our message was printed.
	// how this syntax works :
	
	// void* ptr , points to the first bytes of our memory space 
	
	//  |--------------------------------------------------------------|-------------------------------------
	//=>[1ºbyte] [2ºbyte] [3ºbyte] [4ºbyte] [5ºbyte] [6ºbyte] [7ºbyte] | [8ºbyte] [9ºbyte] [10ºbyte] [11ºbyte]
	
	
	// Well, our intention is to use these 8 first bytes in the MEMORY to store a address to a string constant ( "Hello Memory Space" )
	
	// we are using a ( void* ) pointer, the compiler doesn't know how to interpret the memory that his pointer points to
	
	// We need to tell the compiler: "Treat this memory space as (some type)".
	
	// then the compiler will know how to handle the operation and how many bytes to assign to.
	
	
	// OK: we have our void* ptr, pointing to a location with 12 bytes of space.
	
	// we want to use the first 8 as a const char* type.
	
	// so we use a cast
	
	// This is a trick part. Because we want take the location that void *ptr points and treat
	// this location as const char*
	
	// we can't dereference void*, and do ((const char*)*ptr)
	
	// SO, we have to tell the compiler: "hey listen, actualy my void* ptr, is a pointer to a const char*"
	
	((const char**)ptr); // this does the work, now the compiler knows how to treat the memory when we dereference 'ptr'
	
	
	// the rest is simple, just ask the compiler: "ok, now that you know that 'ptr' points to a const char*, gimme access to it"
	// do this by dereferencing
	
	*((const char**)ptr) = "Yay memory space accessed and stored with the address to this string";
	
	
	//to print it, we need to do the cast again since printf uses char* arguments to print %s
	
	printf("| [ 8 bytes ] const char* | -> %s\n",*((const char**)ptr));
	
	// Ok done.
	
	// now lets access the other 4 bytes... ow.. how ?
	
	
	// just advance our void *ptr, in 8 bytes ahead and we will point to the first byte of the [ 4 bytes ]
	
	// we cant do ' ptr += 8 '
	
	// because compiler advance a pointer based on the size of its type, the size of a void* is unknown to compiler
	
	
	// so just specify to the compiler that the pointer type is a const char*
	
	// to do this in a single line is complicated:
	//(*((const char**) &ptr)) += 1;  ( += 1, because the compiler knows now that he must advance 8 bytes, based on type char*.)
	
	// the fact is that we can't do ((const char*)ptr) += 1, because the result of the cast is not a lvalue
	
	// so we need to do a thing that do this:
	const char** _charPtr = (const char**)&ptr; // take the address of a pointer to our const char *
	(*_charPtr)+=1; // access our pointer to our const char*, and say: "hey advance in the size of bytes of your type)
	// since the type is known to the compiler as char *, will advance 8 bytes
	
	
	// OK, now we're pointing to our 4 bytes space, and want to treat it like a int
	// this should be a lot easier
	
	
	// just say to the compiler: "ok, now my 'ptr' is pointing to a 4 bytes space(int), treat it like a int and assign this value"
	
	
	*((int*)ptr) = 555;
	
	
	
	// now lets print
	
	
	printf("| [ 4 bytes ] - %d - |\n", *((int*)ptr));
	
	
	// to roll back to our const char*, go back 4 bytes
	
	int** _intPtr = (int**)&ptr;
	
	(*_intPtr) -= 1;
	
	// ou (*((int**)&ptr)) -= 1
	
	
	
	

}