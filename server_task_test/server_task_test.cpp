#include <iostream>
#include "thread_pool.h"
#include "server_task.h"
#include <windows.h>

using namespace std;

static void listen_cb(int sock, struct sockaddr *address, int sock_len, void *arg) {
	cout << "listen_cb in main()" << endl;
}

int main() {

#ifdef _WIN32
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#else
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif
	int server_port = 12345;
	int thread_count = 10;

	// 初始化线程
	ThreadPool::Instance()->init(thread_count);

	// 创建server线程池
	ThreadPool server_pool;
	server_pool.init(1);

	// 创建连接任务
	auto task = new ServerTask;
	task->set_server_port(12345);
	task->listen_cb = listen_cb;


	server_pool.dispatch(task);

	while (1) {

	}

	return 0;
}