#include <thread>
#include <iostream>

using namespace std;

void threadTask(){
	cout<< "hello thread" <<endl;
}

void funcThread(){
	thread t(threadTask);
	t.join();
}

