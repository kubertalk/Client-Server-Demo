#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "socket_control.h"
#include "auto.h"
#if LINUX
#else
#pragma comment(lib, "ws2_32.lib")          //add ws2_32.lib  
#endif
int socket_send(socket_entry* entry, char* buf,int len)
{
	printf("client:%s\n",buf);
	return send(entry->sock_fd, buf, len , 0);
}

int socket_recv(socket_entry* entry, char* buf,int len)
{
	int flag = recv(entry->sock_fd, buf, len, 0);
        if (flag == 0){
            printf("peer closed\n");
        } 
        else if (flag == -1) {
            printf("recv failed ! error message : %d\n", flag);
       }
	return flag;
}



void handle_tcp_msg(socket_entry* entry)
{
	int len;
	char buf[BUFF_LEN];
	printf("client fd :%d \n",entry->sock_fd);//while(1);
	while(1){
		len=socket_recv(entry, buf,sizeof(struct auto_cmd));
		if(len <=0){
			printf("error\n");
			break;
		}
		printf("packet come in, len is %d\n",len);
		if(entry->socket_cmd_handler)
			entry->socket_cmd_handler(entry,buf);
	}
}
void* server_routine(void* param)
{
	socket_entry* entry = (socket_entry*)param;
	printf("start new thread sock fd:%d\n",entry->sock_fd);
	handle_tcp_msg(entry);
	close(entry->sock_fd);
	free(entry);
	printf("client down\n");
}


int socket_server_init(int port_number)
{
	int server_fd=-1;
	int ret;
	struct sockaddr_in ser_addr; 

	server_fd = socket(AF_INET, SOCK_STREAM, 0); //
	if(server_fd < 0)
	{
	    printf("create socket fail!\n");
	    return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	//ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_ANY); // 
	ser_addr.sin_addr.s_addr = htonl(SERVER_IP_FIX);
	ser_addr.sin_port = htons(port_number);  //

	ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
	if(ret < 0)
	{
	    printf("socket bind fail!\n");
	    return -1;
	}

	printf("pid %d: [socket %d] server:port %d is on\n",getpid(),server_fd,port_number);
	return server_fd;
}
extern int server_cmds_handler(socket_entry* entry,void* cmd_buf);
void socket_server_start(socket_entry* server)
{
	char buf[BUFF_LEN];
	
	printf("server %d listen for connect\n",server->sock_fd); 
	if(listen(server->sock_fd, 5) == -1){
		printf("ERROR in listen Stream Socket\n");
		return;
	}
	while(1){
		pthread_t thread;
		int client_fd = 0;
		struct sockaddr_in caddr;
		memset(&caddr,0,sizeof(struct sockaddr));
		int inet_addr_len=sizeof(struct sockaddr);
		
		client_fd = accept(server->sock_fd, (struct sockaddr *)(&(caddr)), &inet_addr_len);//sizeof(struct sockaddr_in));
		if(client_fd > 0){
			socket_entry* client = (socket_entry*)malloc(sizeof(socket_entry));
			memset(client,0,sizeof(socket_entry));
			client->sock_fd = client_fd;
			client->inet_addr = caddr;
			printf("accepted %d \n",client->sock_fd);
			client->socket_cmd_handler = server_cmds_handler;
			//socket_recv(client,buf);
			pthread_create(&thread,NULL,server_routine,(void *)client);
		}
	}
}


int socket_client_init(socket_entry* client, int server_port_num)
{
	int client_fd;
	struct sockaddr_in ser_addr;

	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(client_fd < 0)
	{
		printf("create socket fail!\n");
		return -1;
	}
	
	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //htonl(INADDR_ANY); //
	//ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //
	ser_addr.sin_port = htons(server_port_num);  //

	client->sock_fd = client_fd;
	int ret = connect(client_fd, (struct sockaddr*)&ser_addr, sizeof(struct sockaddr_in));//????  
	if (ret <0)
	{
		printf("socket connect failed\n");
		
		close(client_fd);
		return -1;
	}
	printf("pid %d: [socket %d] client:port %d is on\n",getpid(),client_fd,server_port_num);
	return client_fd;

}

