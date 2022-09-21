#include <iostream>
#include <windows.h>
#include "thread_pool.h"

using namespace std;

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

	while (1) {
		
	}

	return 0;
}