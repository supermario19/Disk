#include "thread.h"
#include "task.h"
#include <thread>
#include <iostream>

using namespace std;

static void notify_cb(evutil_socket_t sock, short what, void *arg) {
	// 取线程
	auto *th = (Thread *)arg;

	// 执行相应线程回调函数
	th->notify(sock);
}

void Thread::start() {
	// 线程设置
	set_up();

	// 启动线程
	thread th(&Thread::thread_main, this);

	// 分离线程
	th.detach();
}

bool Thread::set_up() {
	// 创建event_base
	event_config *evc = event_config_new();
	event_config_set_flag(evc, EVENT_BASE_FLAG_NOLOCK);
	base = event_base_new_with_config(evc);
	event_config_free(evc);
	if (!base) {
		cerr << "event_base_new() error" << endl;
		return false;
	}

	// 创建管道
	evutil_socket_t fds[2];
	if (evutil_socketpair(AF_INET, SOCK_STREAM, 0, fds) < 0) {
		cerr << "event_socketpair() error" << endl;
		return false;
	}
	evutil_make_socket_nonblocking(fds[0]);
	evutil_make_socket_nonblocking(fds[1]);

	// 读端口放入event_base, 写端口保存
	notify_fd = fds[1];
	struct event *ev = event_new(base, fds[0], EV_READ | EV_PERSIST, notify_cb, this);
	event_add(ev, nullptr);
}

void Thread::thread_main() {
	cout << "thread " << thread_id << " begin" << endl;

	// 事件分发
	event_base_dispatch(base);

	// 事件销毁
	event_base_free(base);

	cout << "thread " << thread_id << " end" << endl;
}

void Thread::notify(evutil_socket_t sock) {
	char buffer[2] = { 0 };
	int len = recv(sock, buffer, 1, 0);
	if (len < 0) {
		return;
	}
	cout << "thread " << thread_id << " active" << endl;

	// 获取任务
	tasks_mutex.lock();
	if (tasks.empty()) {
		tasks_mutex.unlock();
		return;
	}
	Task *task = tasks.front();
	tasks.pop_front();
	tasks_mutex.unlock();

	// 任务初始化
	task->init();
}

void Thread::active() {
	int re = send(notify_fd, "c", 1, 0);
	if (re < 0) {
		cerr << "active() error" << endl;
	}
}

void Thread::add_task(Task *task) {
	if (!task) {
		return;
	}
	task->set_base(base);
	tasks_mutex.lock();
	tasks.push_back(task);
	tasks_mutex.unlock();
}


