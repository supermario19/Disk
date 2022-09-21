#ifndef SERVER_TASK_H
#define SERVER_TASK_H
#include "task.h"
#include "server_task_export.h"

typedef void(*listen_cb_ptr)(int sock, struct sockaddr *address, int sock_len, void *arg);

class SERVER_TASK_API ServerTask : public Task
{
public:
	// 初始化任务
	virtual bool init() override;

	// 设置端口号
	void set_server_port(int server_port) {
		this->server_port = server_port;
	}

	// 获取端口号
	int get_server_port() const {
		return server_port;
	}

public:
	// 回调函数
	listen_cb_ptr listen_cb;
private:
	// 端口号
	int server_port;
};

#endif

