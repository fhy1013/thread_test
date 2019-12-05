#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "thread_condition_variable.h"

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void doPrintId(int id){
	std::unique_lock<std::mutex> lck(mtx);
	while(!ready){
		std::cout<< "thread "<< id<<" cv.wait()"<< std::endl;
		cv.wait(lck);
	}
	std::cout<<"thread " << id<<std::endl;
	//std::this_thread::sleep_for(std::chrono::seconds(1));
}

void go(){
	std::unique_lock<std::mutex> lck(mtx);
	ready = true;
	cv.notify_all();
}

void funcConditionVariable(){
	std::thread threads[7];
	for(int i = 0; i < 7; ++i){
		threads[i] = std::thread(doPrintId, i);
	}

	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout<< "7 threads ready to race..." << std::endl;
	go();

	for(auto &t : threads){
		t.join();
	}
}
