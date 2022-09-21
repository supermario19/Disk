#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include "thread_pool_export.h"
#include <vector>

class Task;
class Thread;

class THREAD_POOL_API ThreadPool {
public:
	// 单例模式
	static ThreadPool *Instance() {
		static ThreadPool pool;
		return &pool;
	}

	// 线程初始化
	void init(int thread_count);

	// 任务分发
	void dispatch(Task *task);

	// 构造
	ThreadPool() = default;

	// 析构
	~ThreadPool() = default;
private:
	// 线程数量
	int thread_count;
	
	// 线程数组
	std::vector<Thread *> threads;

	// 上次任务线程index
	int last_thread_index;
};

#endif

