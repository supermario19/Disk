#ifndef SERVER_TASK_H
#define SERVER_TASK_H
#include "task.h"
#include "server_task_export.h"

typedef void(*listen_cb_ptr)(int sock, struct sockaddr *address, int sock_len, void *arg);

class SERVER_TASK_API ServerTask : public Task
{
public:
	// ��ʼ������
	virtual bool init() override;

	// ���ö˿ں�
	void set_server_port(int server_port) {
		this->server_port = server_port;
	}

	// ��ȡ�˿ں�
	int get_server_port() const {
		return server_port;
	}

public:
	// �ص�����
	listen_cb_ptr listen_cb;
private:
	// �˿ں�
	int server_port;
};

#endif

