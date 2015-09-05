#include <iostream>
#include <thread>
#include <mutex>



/*  Resource Aquisition Is Initialization ( RAII )
 *
 * 	Use Objects to manage resources :
 * 		memory, hardware device, network connection , etc.
 *
 * 	Example number 1: controlling threads.
 *
 */
std::mutex thread_controll;





void print_message_NO_RAII()
{
	thread_controll.lock();



	std::cout << "I'm thread " << std::this_thread::get_id() << std::endl;
	throw 20;

	thread_controll.unlock();
}



void some_thread_shared_function_NO_RAII(const int n_times)
{


	std::cout << "In some_thread_shared_function NO RAII" << std::endl;	
	
	
	
	for(int i= 0; i < n_times; ++i)
	{
		// Let's say that , "print_message" may throw an exception
		try
		{		
			print_message_NO_RAII();
		}
		catch(const int error)
		{
			std::cout << "handling error in print_message. code: " << error << std::endl;
		}
			
		// if print_message does throw it, thread_controll will never be unlocked. unless we manualy unclock it in all the throws/catchs.
		// what do we do to make it easy? :
		// the RAII class to manage the resource!
		//
		// The RAII class will lock the mutex , but when the class is destroyed the mutex will always be unlocked.
	
	}	



}


class RAII_Mutex_Example
{
public:
	
	// the class is contructed with a reference to a mutex, and lock it.
	RAII_Mutex_Example(std::mutex &mu) : myMutex { mu }
	{
		myMutex.lock();
		std::cout << "Mutex has been locked" << std::endl;
	}

	// the class is destructed unlocking that mutex. leaving it automatic always unlocked at the end of a function.
	// unless you create the class in heap with new. in that case ,  you have to ensure  the object is deleted at the end of function.
	~RAII_Mutex_Example()
	{
		myMutex.unlock();
		std::cout << "Mutex has been released" << std::endl;
	}

private:
	std::mutex &myMutex;

};




void print_message_WITH_RAII()
{
	RAII_Mutex_Example safe_lock(thread_controll);
	std::cout << "I'm in thread " << std::this_thread::get_id() << std::endl;

	throw 20;

}


void some_thread_shared_function_WITH_RAII(const int n_times)
{
	std::cout << "In some_thread_shared_function WITH RAII" << std::endl;	
	
	
	
	for(int i{0}; i < n_times; ++i)
	{

		try
		{	// now , our thread_shared_function, call the print_message_WITH_RAII , that have its mutex unlocked even if throws an exception	
			print_message_WITH_RAII();
		}
		catch(const int error)
		{
			std::cout << "handling error in print_message. code: " << error << std::endl;
		}
	}	
	



	

}



int main()
{

	// as you see, the thread using the raii object to managed the mutex goes fine, 
	// as for the other one it stops, cause the mutex is forever locked.

	std::thread with_raii(some_thread_shared_function_WITH_RAII,2);
	
	with_raii.join();

	std::thread without_raii(some_thread_shared_function_NO_RAII,2);

	without_raii.join();



}








