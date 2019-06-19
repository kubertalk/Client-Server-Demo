#ifndef __SOCKET_CONTROL_H__
#define __SOCKET_CONTROL_H__
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          
#if LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <WS2tcpip.h>
#endif


#define SERVER_PORT_AUTO 8087
#define SERVER_IP_FIX 10.25.131.67
#define SOCKET_CMD_DONE 0x505AEE05

#define BUFF_LEN 1024

typedef struct sock_entry{
	int (*socket_cmd_handler)(struct sock_entry* entry, void* cmd_buf);
	void* private;
	int sock_fd;
	struct sockaddr_in inet_addr;
}socket_entry;

int socket_client_init(socket_entry* client, int server_port_num);
int socket_send(socket_entry* entry, char* buf,int len);
int socket_recv(socket_entry* entry, char* buf,int len);
int socket_server_init(int port_number);
void socket_server_start(socket_entry* server);

void handle_tcp_msg(socket_entry* entry);
#endif
