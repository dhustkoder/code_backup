#include <unistd.h>
#include <iostream>
#include <signal.h>


void signal_handler(int sig_num)
{
	std::cout << "Recived signal: " << sig_num << std::endl;

	exit(sig_num);
}


int main()
{
	signal(SIGINT,signal_handler);

	while(1)
	{
		std::cout << "Running" << std::endl;
		sleep(2);
	}

	return 0;
}