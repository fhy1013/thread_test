#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void funcThread1(int n){
	for(auto i = 0; i < 5; ++i){
		cout<< "thread " << n << " executing" << endl;
		this_thread::sleep_for(chrono::milliseconds(300));
	}
}

void funcThread2(int &n){
	for(auto i = 0; i < 5; ++i){
		cout<< "thread 2 executing" <<endl;
		++n;
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}

void funcThreadConcurrent(){
	int n = 0;
	thread t1;
	thread t2(funcThread1, n+1);
	thread t3(funcThread2, ref(n));
	thread t4(move(t3));

	t2.join();
	t4.join();
	cout<< "final value of n is " << n <<endl;
}
