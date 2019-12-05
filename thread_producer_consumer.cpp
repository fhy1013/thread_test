#include <iostream>

#include "thread_producer_consumer.h"

ItemRepository gItemRepository;

void produceItem(ItemRepository &ir, int item){
	std::unique_lock<std::mutex> lck(ir.mtx);
	while(((ir.write_position + 1) % kItemRepositorySize) == ir.read_position){
		std::cout<< "producer is waiting for an empty slot..." <<std::endl;
		ir.repo_not_full.wait(lck); // 等待“产品库缓冲区不为满”这一条件发生
	}
	ir.item_buffer[ir.write_position] = item; // 写入产品
	ir.write_position++; // 写入位置后移
	if(ir.write_position == kItemRepositorySize)
		ir.write_position = 0; // 写入位置若在队列最后则重新设置为初始位置
	ir.repo_not_empty.notify_all(); // 通知消费者产品库不为空
	lck.unlock(); // 解锁
}

int consumeItem(ItemRepository &ir){
	int data;
	std::unique_lock<std::mutex> lck(ir.mtx);
	while(ir.write_position == ir.read_position){
		std::cout<< "consumer is waiting for items..." << std::endl;
		ir.repo_not_empty.wait(lck); // 等待“产品库缓冲区不为空”这一条件发生
	}
	data = ir.item_buffer[ir.read_position]; // 读取产品
	ir.read_position++; // 读取位置后移;
	if(ir.read_position >= kItemRepositorySize)
		ir.read_position = 0; // 读取位置若在队列最后则重新设置为初始位置
	ir.repo_not_full.notify_all(); // 通知生产者产品库不为满
	lck.unlock(); // 解锁

	return data;
}

void initItemRepository(ItemRepository &ir){
	ir.write_position = 0;
	ir.read_position = 0;
	ir.produced_item_counter = 0;
	ir.consumed_item_counter = 0;
}
