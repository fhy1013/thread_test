#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <unistd.h>
#include <chrono>

#include "thread_mult_producer_mult_consumer.h"


// 生产者任务
static void producerTask(){
	//bool ready_to_exit = false;
	while(true){
		std::unique_lock<std::mutex> lck(gItemRepository.procuded_item_counter_mtx);
		//if(gItemRepository.produced_item_counter < kItemsToProduce){
			++gItemRepository.produced_item_counter;
			produceItem(gItemRepository, gItemRepository.produced_item_counter);
			std::cout<< "producer thread " << std::this_thread::get_id() 
			<<" is producing the " << gItemRepository.produced_item_counter 
			<< "^th item..." << std::endl;
		//}else{
		//	ready_to_exit = true;
		//}
		//lck.unlock();
		//if(ready_to_exit)
		//	break;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout<< "producer thread " << std::this_thread::get_id()
	<< " is exiting..." << std::endl;
}

// 消费者任务
static void consumerTask(){
	//bool ready_to_exit = false;
	while(true){
		std::unique_lock<std::mutex> lck(gItemRepository.consumed_item_counter_mtx);
		//if(gItemRepository.consumed_item_counter < kItemsToProduce){
			int item = consumeItem(gItemRepository); // 消费一个产品
			++gItemRepository.consumed_item_counter;
			std::cout<< "consumer thread " << std::this_thread::get_id() 
			<< " is consuming the " << item << "^th item" <<std::endl;
		//}else{
		//	ready_to_exit = true;
		//}
		//lck.unlock();
		//if(ready_to_exit)
		//	break;
		std::this_thread::sleep_for(std::chrono::milliseconds(333));
	}
	std::cout<< "consumer thread " << std::this_thread::get_id()
	<< " is exiting..." << std::endl;
}

void funcMultipleProduceMultipleConsume(){
	initItemRepository(gItemRepository);

	std::thread producer1(producerTask);
	std::thread producer2(producerTask);
	std::thread producer3(producerTask);
	std::thread consumer1(consumerTask);
	std::thread consumer2(consumerTask);
	std::thread consumer3(consumerTask);

	producer1.join();
	producer2.join();
	producer3.join();
	consumer1.join();
	consumer2.join();
	consumer3.join();
}

