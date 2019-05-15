#include "auto.h"
#include "socket_control.h"
int socket_cmd_create(int cmd,char* param,int len,char* cmd_buf)
{
	struct auto_cmd* tx_cmd=(struct auto_cmd*)cmd_buf;
	tx_cmd->cmd = cmd;
	memcpy(cmd_buf+sizeof(int),param,len);
	return len+sizeof(int);
}
int socket_check_cmd_ack(char* buf)
{
	struct auto_ack* ack = (struct auto_ack*)buf;
	if (ack->status == CMD_ACK)
		return 0;
	else
		return -1;
}
int socket_check_data_ack(char* buf)
{
	struct auto_ack* ack = (struct auto_ack*)buf;
	if (ack->status == DATA_ACK)
		return 0;
	else
		return -1;
}
int socket_send_ack(socket_entry* sock,int ack)
{
	struct auto_ack tx_ack;
	tx_ack.status = ack;
	return socket_send(sock,(char*)&tx_ack,sizeof(struct auto_ack));
}

int socket_recv_ack(socket_entry* sock,char* buf )
{
	int flag = recv(sock->sock_fd, buf, sizeof(struct auto_ack) , 0);
        if (flag == 0){
            printf("peer closed\n");
        } 
        else if (flag == -1) {
            printf("recv failed ! error message : %d\n", flag);

        }																			   
	return flag;
}

