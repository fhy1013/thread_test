#ifndef __THREAD_PRODUCER_CONSUMER__
#define __THREAD_PRODUCER_CONSUMER__

#include <mutex>
#include <condition_variable>

const int kItemRepositorySize = 3;
const int kItemsToProduce = 17;

struct ItemRepository{
	int item_buffer[kItemRepositorySize];
	size_t read_position; //消费者读取产品位置
	size_t write_position; // 生产者写入产品位置
	size_t produced_item_counter; //
	size_t consumed_item_counter;
	std::mutex mtx; // 互斥量，保护产品缓冲区
	std::mutex procuded_item_counter_mtx;
	std::mutex consumed_item_counter_mtx;
	std::condition_variable repo_not_full; // 条件变量，指示产品缓冲区不为满
	std::condition_variable repo_not_empty; // 条件变量，指示产品缓冲区不为空
};

typedef struct ItemRepository ItemRepository;

extern ItemRepository gItemRepository;

void produceItem(ItemRepository &ir, int item);
int consumeItem(ItemRepository &ir);
void initItemRepository(ItemRepository &ir);

#endif // __THREAD_PRODUCER_CONSUMER__
