#ifndef THREAD_H
#define THREAD_H
#include <event2/event.h>
#include <evutil.h>
#include <list>
#include <mutex>
#include "thread_pool_export.h"

class Task;

class Thread
{
public:
	// 构造
	Thread() = default;

	// 析构
	~Thread() = default;

	// 线程启动
	void start();

	// 线程设置
	bool set_up();

	// 线程主函数
	void thread_main();

	// 回调函数
	void notify(evutil_socket_t sock);

	// 线程激活函数
	void active();

	// 添加任务
	void add_task(Task *task);

	// 设置线程id
	void set_thread_id(int thread_id) {
		this->thread_id = thread_id;
	}

	// 获取线程id
	int get_thread_id() const {
		return thread_id;
	}

	// 设置notify_fd
	void set_notify_fd(int notify_fd) {
		this->notify_fd = notify_fd;
	}

	// 获取notify_fd
	int get_notify_fd() const {
		return notify_fd;
	}
private:
	// 线程编号
	int thread_id;
	// 管道写端
	int notify_fd;
	// 上下文
	struct event_base *base;
	// 任务列表
	std::list<Task *> tasks;
	// 列表锁
	std::mutex tasks_mutex;
};

#endif

