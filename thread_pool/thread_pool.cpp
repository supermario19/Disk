#include "thread_pool.h"
#include "thread.h"
#include "task.h"
#include <thread>

using namespace std;

void ThreadPool::init(int thread_count) {
	// 上次分发线程下标
	last_thread_index = -1;

	// 线程数量
	this->thread_count = thread_count;

	for (int i = 0; i < thread_count; i++) {
		// 创建线程并加入线程队列
		Thread *thread = new Thread();
		thread->set_thread_id(i);
		thread->start();
		threads.push_back(thread);
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

void ThreadPool::dispatch(Task *task) {
	if (!task) {
		return;
	}
	int tid = (last_thread_index + 1) % thread_count;

	task->set_thread_id(tid);

	Thread *th = threads[tid];
	last_thread_index = tid + 1;

	// 线程派发任务
	th->add_task(task);

	// 激活线程
	th->active();
}