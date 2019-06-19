#include <stdio.h>
#include <stdlib.h>
#include "socket_control.h"
#include "auto.h"

#include "cmd_agent_register.h"
#include "cmd_agent_auto_start.h"

int agent_cmds_handler(socket_entry* entry,void* cmd_buf)
{
	struct auto_cmd* cmd = (struct auto_cmd*)cmd_buf;
	
	switch(cmd->cmd)
	{
	case CMD_AGENT_AUTO_START:
		cmd_agent_auto_start_handler(entry,cmd_buf);
		break;
	case CMD_AGENT_AUTO_PAUSE:
	default:	
		break;
	}
	return 0;
}
void agent_init(socket_entry* agent_sender)
{
	socket_client_init(agent_sender, SERVER_PORT_AUTO);
}


void main(void)
{
	socket_entry agent_socket;
	agent_init(&agent_socket);
	//while(1);
	cmd_agent_register(&agent_socket);
	agent_socket.socket_cmd_handler = agent_cmds_handler;
	agent_socket.private = NULL;
	
	/*wait for cmds*/
	printf("agent wait for cmds\n");
	handle_tcp_msg(&agent_socket);
	printf("server down\n");
}
