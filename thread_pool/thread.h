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
	// ����
	Thread() = default;

	// ����
	~Thread() = default;

	// �߳�����
	void start();

	// �߳�����
	bool set_up();

	// �߳�������
	void thread_main();

	// �ص�����
	void notify(evutil_socket_t sock);

	// �̼߳����
	void active();

	// �������
	void add_task(Task *task);

	// �����߳�id
	void set_thread_id(int thread_id) {
		this->thread_id = thread_id;
	}

	// ��ȡ�߳�id
	int get_thread_id() const {
		return thread_id;
	}

	// ����notify_fd
	void set_notify_fd(int notify_fd) {
		this->notify_fd = notify_fd;
	}

	// ��ȡnotify_fd
	int get_notify_fd() const {
		return notify_fd;
	}
private:
	// �̱߳��
	int thread_id;
	// �ܵ�д��
	int notify_fd;
	// ������
	struct event_base *base;
	// �����б�
	std::list<Task *> tasks;
	// �б���
	std::mutex tasks_mutex;
};

#endif

