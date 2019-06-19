#include <stdio.h>

#include "auto.h"
#include "socket_control.h"
void cmd_agent_auto_start(socket_entry* agent,char* script)
{
	char buf[BUFF_LEN];
	int fd;
	struct agent_cmd_script* script_file=(struct agent_cmd_script*)script;
	int len=0, left_len=0;

		
	len=socket_cmd_create(CMD_AGENT_AUTO_START, script,sizeof(struct agent_cmd_script),buf);
	socket_send(agent, buf,sizeof(struct auto_cmd));
	
	socket_recv_ack(agent,buf);
	socket_check_cmd_ack(buf);
/*
	fd=fopen(script_file.file_name,"r");
	left_len= script_file->script_len;
	while(left_len){
		len=read(fd,buf);
		socket_send(agent,buf,len);
		left_len -=len;
	}
	socket_recv_ack(agent,buf);
	socket_check_data_ack(buf);
*/
}

int cmd_agent_auto_start_handler(socket_entry* entry,char* buf)
{
	struct auto_cmd* cmd = (struct auto_cmd*)buf;
	struct agent_cmd_script* script=NULL;

	int recv_len=0, left_length=0;
	char recv_buf[BUFF_LEN];

	script = &(cmd->cmd_content.script);
	if (script && script->script_len){
			socket_send_ack(entry,CMD_ACK);
			left_length = script->script_len;
			printf("script file:\n");
			while(left_length ) {
				recv_len = socket_recv(entry, recv_buf,(left_length<BUFF_LEN)? (left_length):(BUFF_LEN));
				script_file_save(recv_buf);
				left_length -= recv_len;
				printf("%s", recv_buf);
			}
			printf("\n");
			socket_send_ack(entry, DATA_ACK);
	}
	return 0;
}
