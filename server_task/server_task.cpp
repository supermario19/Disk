#include "server_task.h"
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <cstring>
#include <iostream>

using namespace std;

void listener_cb_internal(struct evconnlistener *evc, evutil_socket_t sock, struct sockaddr *address, int socklen, void *arg) {
	auto *task = (ServerTask *)arg;

	if (!task->listen_cb) {
		cerr << "listen callback is not set" << endl;
		return;
	}
	task->listen_cb(sock, address, socklen, arg);
}

bool ServerTask::init() {
	if (server_port < 0 || server_port > 65535) {
		cerr << "server_port is not set" << endl;
		return false;
	}
	// 监听端口
	sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(server_port);

	// 创建监听事件
	auto *evc = evconnlistener_new_bind(base, listener_cb_internal, this, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, 10,
		(sockaddr *)&address, sizeof(address));
	if (!evc) {
		cerr << "listen port " << server_port << " failed!" << endl;
		return false;
	}
	cout << "listen port " << server_port << " success!" << endl;

	return true;
}