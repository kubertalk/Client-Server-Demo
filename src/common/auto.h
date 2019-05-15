#ifndef __AUTO_H__
#define __AUTO_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket_control.h"
#include "file_operation.h"

#define AGENT_STATUS_READY 0x22
#define AGENT_STATUS_RUNNING 0x33

#define CMD_ACK	0xA0000
#define DATA_ACK	0xB0000
#define CMD_SRC_SERVER	0xC0000
#define CMD_SRC_USER	0xD0000
#define CMD_SRC_AGENT	0xF0000

/*from agent to server cmd*/
#define CMD_AGENT_REGISTER	(CMD_SRC_AGENT|0x1)
#define CMD_AGENT_DOWN		(CMD_SRC_AGENT|0x2)

/*from user to server cmd*/
#define CMD_TASK_START		(CMD_SRC_USER|0x1)
#define CMD_TASK_STATUS	(CMD_SRC_USER|0x2)
#define CMD_TASK_CANCEL	(CMD_SRC_USER|0x3)
#define CMD_TASK_PAUSE		(CMD_SRC_USER|0x4)

/*from server to agent cmd*/
#define CMD_AUTO_START		(CMD_SRC_SERVER|0x1)
#define CMD_AUTO_PAUSE	(CMD_SRC_SERVER|0x5)

/*from server to user cmds*/
#define CMD_USER_PAUSE		(CMD_SRC_SERVER|0x1)
#define CMD_USER_TASK_STS	(CMD_SRC_SERVER|0x2)
/*user can get agent info*/
#define CMD_USER_AGENT_INFO	(CMD_SRC_SERVER|0x8)
/*cmd ack*/


/*data ack*/

struct agent_info {
	int status;
	char pc_name[64];
	char board_name[64];
};
struct agent_cmd_script{
	int script_len;
	char file_name[32];
};
struct auto_cmd {
	int cmd;
	union{
		struct agent_info info;
		struct agent_cmd_script script;
	}cmd_content;
};

struct auto_ack {
	int cmd;
	int status;
};


int socket_cmd_create(int cmd,char* param,int len,char* cmd_buf);
int socket_check_cmd_ack(char* buf);
int socket_check_data_ack(char* buf);
int socket_send_ack(socket_entry* sock,int ack);
int socket_recv_ack(socket_entry* sock,char* buf);
#endif
