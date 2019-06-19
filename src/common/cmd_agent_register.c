#include <stdio.h>
#include <stdlib.h>

#include "auto.h"
#include "socket_control.h"
int agent_register_cmd_create(int cmd, void* param, char* cmd_buf)
{
	struct agent_info* info = (struct agent_info*)param;
	struct auto_cmd* tx_cmd = (struct auto_cmd*)cmd_buf;
	tx_cmd->cmd = cmd;
	memcpy((void*)&(tx_cmd->cmd_content.info), (void*)info, sizeof(struct agent_info));
	return 0;
}
int agent_register_check_ack(int cmd, void* param, char* cmd_buf)
{
	struct auto_ack* ack = (struct auto_ack*)cmd_buf;
	if (ack->status == CMD_ACK){
		printf("cmd ack here\n");
		return 0;
	}
	else
		return -1;
}
/*side A: send cmd agent register*/
void cmd_agent_register(socket_entry* agent)
{
	char buf[BUFF_LEN];
	struct agent_info info;
	int len;
	memset((char*)&info,0,sizeof(struct agent_info));
	info.status = AGENT_STATUS_READY;
	memcpy((void*)info.pc_name, "CDLAB-05", 8);
	memcpy((void*)info.board_name, "A3900", 5);
	
	len=agent_register_cmd_create(CMD_AGENT_REGISTER, (void*)(&info),buf);
	socket_send(agent, buf,sizeof(struct auto_cmd));
	
	socket_recv_ack(agent,buf);
	agent_register_check_ack(CMD_AGENT_REGISTER,NULL,buf);
}


/*side B: handle cmd agent register*/
int cmd_agent_register_handler(socket_entry* entry,char* buf)
{
	struct auto_cmd* cmd = (struct auto_cmd*)buf;
	struct agent_info* info=NULL;

	
	info = &(cmd->cmd_content.info);
	printf("AGENT register\n");
	printf("AGENT PC: %s \n",info->pc_name);
	printf("AGENT board:%s\n",info->board_name);
	printf("AGENT status:%d\n",info->status);
	if (info && info->status == AGENT_STATUS_READY ){
		printf("AGENT is ready\n");
	}
	socket_send_ack(entry,CMD_ACK);
	return 0;
}


