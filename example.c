#define HTTPD_IMPLEMENTATION
#include "httpd.h"

int main(void)
{
	static struct server_t server;
	const int reuse = 1;

	memset(&server, 0, sizeof(server));
	server.sock = -1;

	server.sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server.sock < 0) {
		perror("socket");
		return -1;
	}

	memset(&server.addr, 0, sizeof(server.addr));
	server.addr.sin_family = AF_INET;
	server.addr.sin_port = htons(8080);
	server.addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(server.sock, (const struct sockaddr *)&server.addr, sizeof(server.addr)) < 0) {
		perror("bind");
		return -1;
	}

	if (setsockopt(server.sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		perror("setsockopt");
		return -1;
	}

	if (listen(server.sock, 2) < 0) {
		perror("listen");
		return -1;
	}

	server.func_bad_request = request_bad;
	server.func_request = request_response;

	return run_server(&server);
}

