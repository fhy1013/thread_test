#include <iostream>
#include "thread_test.h"
#include "thread_concurrent.h"
#include "thread_getid.h"
#include "thread_condition_variable.h"
#include "thread_single_producer_single_consumer.h"
//#include "thread_signal_producer_multiple_consumer.h"
#include "thread_mult_producer_mult_consumer.h"

int main(){
	//funcThread();
	//funcThreadConcurrent();
	//funcThreadGetId();
	//funcConditionVariable();
	//funcSignalProduceSignalConsume();
	//funcSignalProduceMultipleConsume();
	funcMultipleProduceMultipleConsume();	
	std::cout<<"main thread"<<std::endl;
	return 0;
}
