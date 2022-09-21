#ifndef TASK_H
#define TASK_H
#include <event2/event.h>

class Task {
public:
	// 构造函数
	Task() = default;

	// 析构函数
	virtual ~Task() = default;

	// 任务初始化
	virtual bool init() = 0;

	// 获取base
	event_base *get_base() const {
		return base;
	}

	// 设置base
	void set_base(event_base *base) {
		this->base = base;
	}

	// 获取sock
	int get_sock() const {
		return sock;
	}

	// 设置sock
	void set_sock(int sock) {
		this->sock = sock;
	}

	// 获取thread_id
	int get_thread_id() const {
		return thread_id;
	}

	// 设置thread_id
	void set_thread_id(int thread_id) {
		this->thread_id = thread_id;
	}
protected:
	// 任务所属上下文
	struct event_base *base;
	// 任务sock
	int sock;
	// 任务所属线程
	int thread_id;
};

#endif
