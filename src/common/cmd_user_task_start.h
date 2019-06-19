#ifndef __CMD_USER_TASK_START_H__
#define __CMD_USER_TASK_START_H__

void cmd_user_task_start(socket_entry* agent,char* script);
int cmd_user_task_start_handler(socket_entry* entry,char* buf);
#endif
