#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include "thread_pool_export.h"
#include <vector>

class Task;
class Thread;

class THREAD_POOL_API ThreadPool {
public:
	// ����ģʽ
	static ThreadPool *Instance() {
		static ThreadPool pool;
		return &pool;
	}

	// �̳߳�ʼ��
	void init(int thread_count);

	// ����ַ�
	void dispatch(Task *task);

	// ����
	ThreadPool() = default;

	// ����
	~ThreadPool() = default;
private:
	// �߳�����
	int thread_count;
	
	// �߳�����
	std::vector<Thread *> threads;

	// �ϴ������߳�index
	int last_thread_index;
};

#endif

