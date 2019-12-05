#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <unistd.h>
#include <chrono>

#include "thread_single_producer_single_consumer.h"

// 生产者任务
static void producerTask(){
	for(int i = 1; i <= kItemsToProduce; ++i){
		std::cout<<"produce the " << i << "^th item..." << std::endl;
		produceItem(gItemRepository, i); // 循环生产
	}
}

// 消费者任务
static void consumerTask(){
	static int cnt = 0;
	while(true){
		//sleep(1);
		int item = consumeItem(gItemRepository); // 消费一个产品
		std::cout<< "consume the " << item << "^th item" <<std::endl;
		if(++cnt == kItemsToProduce){
			std::cout<< "cnt " << cnt<< std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void funcSignalProduceSignalConsume(){
	initItemRepository(gItemRepository);
	std::thread producer(producerTask);
	std::thread consumer(consumerTask);
	producer.join();
	consumer.join();
}
