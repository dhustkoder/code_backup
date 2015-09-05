#include <iostream>
#include <cstdio>
#include <chrono>
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


void print_message()
{

	std::cout << "I'm thread " << std::this_thread::get_id() << std::endl;
}



void some_thread_shared_function(const int n_times)
{

	thread_controll.lock();
				
	
	
	
	for(int i= 0; i < n_times; ++i) // Let's say that , "print_message" may throw an exception
		print_message();
		
	
	
	
	
	thread_controll.unlock();	



}



int main()
{
	std::thread thread_1(some_thread_shared_function,4);
	std::thread thread_2(some_thread_shared_function,2);

	thread_2.join();
	thread_1.join();



//	std::this_thread::sleep_for(std::chrono::seconds(5));


}








