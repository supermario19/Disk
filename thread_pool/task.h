#ifndef TASK_H
#define TASK_H
#include <event2/event.h>

class Task {
public:
	// ���캯��
	Task() = default;

	// ��������
	virtual ~Task() = default;

	// �����ʼ��
	virtual bool init() = 0;

	// ��ȡbase
	event_base *get_base() const {
		return base;
	}

	// ����base
	void set_base(event_base *base) {
		this->base = base;
	}

	// ��ȡsock
	int get_sock() const {
		return sock;
	}

	// ����sock
	void set_sock(int sock) {
		this->sock = sock;
	}

	// ��ȡthread_id
	int get_thread_id() const {
		return thread_id;
	}

	// ����thread_id
	void set_thread_id(int thread_id) {
		this->thread_id = thread_id;
	}
protected:
	// ��������������
	struct event_base *base;
	// ����sock
	int sock;
	// ���������߳�
	int thread_id;
};

#endif
