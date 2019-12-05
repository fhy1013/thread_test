#include <thread>
#include <chrono>
#include <iostream>

#include "thread_getid.h"

using namespace std;

void threadTask(int n){
	this_thread::sleep_for(chrono::seconds(n));
	cout<< "thread " << this_thread::get_id() << " paused " << n << " seconds" << endl;
}

void funcThreadGetId(){
	thread threads[5];
	cout<< "Spawing 5 threads..." << endl;
	for(auto i = 0; i < 5; ++i){
		threads[i] = thread(threadTask, i + 1);
	}

	cout<< "Done spawing threads! Now wait for them to join" <<endl;
	for(auto &e : threads)
		e.join();
	cout<< "All threads joined." << endl;
}
