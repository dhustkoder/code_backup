#include <iostream>
#include <thread>
#include <chrono>
#include <set>
#include "TestList.h"

#define LOG(x) std::cout << x << std::endl



void pusherWorkerMT(List *&list, int init, int end)
{
	list = new List();

	for (int i = init; i < end; ++i)
		list->push(i);
}


void pusherWorker(List *list, int init, int end)
{
	for (int i = init; i < end; ++i)
		list->push(i);
}


void chrono_tests()
{
	std::set<std::chrono::microseconds> durations;
	std::chrono::steady_clock steadyClock;

	for (int i = 0; i < 100; ++i)
	{
		auto start = steadyClock.now();
		List *list = new List();

		pusherWorker(list, 0, 1000);
		pusherWorker(list, 1000, 5000);
		pusherWorker(list, 5000, 10000);

		list->saveToFile("Single List");
		delete list;

		auto end = steadyClock.now() - start;
		durations.insert(std::chrono::duration_cast<std::chrono::microseconds>(end));
	}

	auto singleThread = std::make_pair(*durations.begin(), *(--durations.end()));
	durations.clear();

	for (int i = 0; i < 100; ++i)
	{
		auto start = steadyClock.now();
		List *sharedList = new List();
		List *dummyList1, *dummyList2;

		std::thread t1(pusherWorkerMT, &dummyList1, 1000, 5000), 
			t2(pusherWorkerMT, &dummyList2, 5000, 10000);

		pusherWorker(sharedList, 0, 1000);

		t1.join();
		sharedList->mergeAndDel(dummyList1);
		t2.join();
		sharedList->mergeAndDel(dummyList2);

		sharedList->saveToFile("Shared List");
		delete sharedList;

		auto end = steadyClock.now() - start;
		durations.insert(std::chrono::duration_cast<std::chrono::microseconds>(end));
	}

	auto multiThread = std::make_pair(*durations.begin(), *(--durations.end()));
	
	LOG("Single Threaded Best Result: " << singleThread.first.count());
	LOG("Multi Threaded Best Result: " << multiThread.first.count());

	LOG("Single Threaded Worst Result: " << singleThread.second.count());
	LOG("Multi Threaded Worst Result: " << multiThread.second.count());
	std::cin.ignore();
}



int main()
{
	//chrono_tests();
}



