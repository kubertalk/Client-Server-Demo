#include <stdio.h>
#include <stdlib.h>

#include "auto.h"
#include "socket_control.h"

#include "cmd_agent_register.h"
#include "cmd_auto_start.h"
#include "cmd_task_start.h"

int server_cmds_handler(socket_entry* entry,void* cmd_buf)
{
	struct auto_cmd* cmd = (struct auto_cmd*)cmd_buf;
	
	switch(cmd->cmd)
	{
	case CMD_AGENT_REGISTER:
		cmd_agent_register_handler(entry,cmd_buf);
		break;
	case CMD_TASK_START:
		/*1. receive script file*/
		/*2. find agent*/
		/*3. run task on agent*/
		cmd_task_start_handler(entry,cmd_buf);
		break;
	case CMD_TASK_STATUS:
		break;
	case CMD_TASK_CANCEL:
		break;
	case CMD_TASK_PAUSE:
		break;
	default:	
		break;
	}
	return 0;
}



void main(void)
{
	socket_entry server;
	server.sock_fd=socket_server_init(SERVER_PORT_AUTO);
	
	/*wait for cmds*/
	printf("wait for cmds\n");
	socket_server_start(&server);
	
}
