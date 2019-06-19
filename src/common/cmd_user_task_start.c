#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "auto.h"
#include "socket_control.h"
void cmd_user_task_start(socket_entry* agent,char* script)
{
	char buf[BUFF_LEN];
	char* path="/home/chunxie/test/test.txt";
	int fd;
	struct agent_cmd_script* script_file=(struct agent_cmd_script*)script;
	int len=0, left_len=0;

		
	len=socket_cmd_create(CMD_USER_TASK_START, script,sizeof(struct agent_cmd_script),buf);
	socket_send(agent, buf,sizeof(struct auto_cmd));
	
	socket_recv_ack(agent,buf);
	socket_check_cmd_ack(buf);
#if 0
	strcpy(buf,"This is my configure XML file");
	socket_send(agent,buf,108);
	socket_recv_ack(agent,buf);
	socket_check_data_ack(buf);
#else
	fd=auto_file_open(script_file->file_name,AUTO_RDONLY);//script_file->file_name,"r");
	if(fd < 0) {
		printf("open file %s failed, error %d\n",script_file->file_name, fd);
		return;
	}
	left_len= script_file->script_len;
	while(left_len){
		len=auto_file_read(fd,buf,left_len);
		socket_send(agent,buf,len);
		left_len -=len;
	}
	close(fd);
	socket_recv_ack(agent,buf);
	socket_check_data_ack(buf);
#endif
}

int cmd_user_task_start_handler(socket_entry* entry,char* buf)
{
	struct auto_cmd* cmd = (struct auto_cmd*)buf;
	struct agent_cmd_script* script=NULL;

	int recv_len=0, left_length=0, file_len=0;
	char recv_buf[BUFF_LEN];
	//char rebuffer[BUFF_LEN];

	script = &(cmd->cmd_content.script);
	printf("%s\n", script->file_name);
	char *xmlfile = script->file_name;
	if (script && script->script_len){
			socket_send_ack(entry,CMD_ACK);
			file_len = script->script_len;
			left_length = script->script_len;
			char file_buffer[file_len+1];
			while (left_length)
			{
				int recv_len = recv(entry->sock_fd, recv_buf, BUFF_LEN, 0);
				printf("%d\n", recv_len);
				strncat(file_buffer, recv_buf, recv_len);
				left_length -= recv_len;
			}
			FILE *fp = fopen(xmlfile, "w+");
			fwrite(file_buffer, 1, file_len, fp);
			if (fp == NULL)
				printf("File %s not found\n", xmlfile);
			else
			{
				printf("%s", file_buffer);
				int tosend_len = strlen(file_buffer);
				printf("%d\n", tosend_len);
				//int sent_len = 0;
				//char send_buffer
				// while (tosend_len)
				// 	{
				// 		int sent_len = send(entry->sock_fd, file_buffer, BUFF_LEN , 0);
				// 		printf("%d\n", sent_len);
				// 		tosend_len -= sent_len;
				// 	}
				
			}
			// {
			// 	int length = 0;
			//  	bzero(rebuffer, BUFF_LEN);
   //           	// 每读取一段数据，便将其发送给客户端，循环直到文件读完为止
   //           	while((length = fread(rebuffer, sizeof(char), BUFF_LEN, fp)) > 0)
   //           		//printf("%s", rebuffer);
			// }
			//printf("%s", rebuffer);
			//char file_save[file_len+1];
			//strncpy(file_save, rebuffer, strlen(rebuffer)>file_len?file_len:strlen(rebuffer));
			//printf("%s", file_save);
			// FILE *fp = fopen(file_save, "r+");
			// if (fp == NULL)
			// 	printf("File %s not found\n", file_save);
			// else
			// {
			// 	int length = 0;
			// 	bzero(rebuffer, BUFF_LEN);
   //          	// 每读取一段数据，便将其发送给客户端，循环直到文件读完为止
   //          	while((length = fread(rebuffer, sizeof(char), BUFF_LEN, fp)) > 0)
   //          		printf("%s", rebuffer);
			// }
			fclose(fp);
			printf("\nwhere\n\n\n\n");
			printf("script file: %s, len:%d\n",script->file_name,script->script_len);
			// while(left_length ) {
			// 		recv_len = socket_recv(entry, recv_buf,(left_length<BUFF_LEN)? (left_length):(BUFF_LEN));
			// 		//script_file_save(recv_buf);
			// 		left_length -= recv_len;
					
			// 		printf("%s", recv_buf);
			// 	}
			// printf("\n");
			socket_send_ack(entry, DATA_ACK);
	}

	return 0;
}
// if(recv(entry, recv_buf, BUFF_LEN, 0) < 0)
//         {
//             printf("Server Recieve Data Failed.");
//             return;
//         }