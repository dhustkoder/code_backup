#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>



/*  Resource Aquisition Is Initialization ( RAII )
 *
 * 	Use Objects to manage resources :
 * 		memory, hardware device, network connection , etc.
 *
 *
 *
 */




void some_thread_shared_function()
{






}



int main()
{
	std::mutex mu;
	mu.lock();

	std::this_thread::sleep_for(std::chrono::seconds(5));


}








