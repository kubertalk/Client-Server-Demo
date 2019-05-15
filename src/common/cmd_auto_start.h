#ifndef __CMD_AUTO_START_H__
#define __CMD_AUTO_START_H__

void cmd_auto_start(socket_entry* agent,char* script);
int cmd_auto_start_handler(socket_entry* entry,char* buf);
#endif
