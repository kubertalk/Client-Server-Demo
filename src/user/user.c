#include <stdio.h>
#include <stdlib.h>
#include "socket_control.h"
#include "auto.h"

#include "cmd_task_start.h"

int user_cmds_handler(socket_entry* entry,void* cmd_buf)
{
	struct auto_cmd* cmd = (struct auto_cmd*)cmd_buf;
	
	switch(cmd->cmd)
	{
	case CMD_USER_AGENT_INFO:
		break;
	case CMD_USER_TASK_STS:
	default:	
		break;
	}
	return 0;
}
void user_init(socket_entry* entry)
{
	socket_client_init(entry, SERVER_PORT_AUTO);
}


void main(void)
{
	socket_entry user_socket;
	struct agent_cmd_script script;
	user_init(&user_socket);
	strcpy(script.file_name,"config_xml.txt");
	script.script_len = 108;
	cmd_task_start(&user_socket,(char*)&script);
	user_socket.socket_cmd_handler = user_cmds_handler;
	user_socket.private = NULL;
	
	/*wait for cmds*/
	printf("user wait for cmds\n");
	handle_tcp_msg(&user_socket);
	printf("server down\n");
}
