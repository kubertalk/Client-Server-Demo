#ifndef __CMD_AGENT_REGISTER_H__
#define __CMD_AGENT_REGISTER_H__

#include "socket_control.h"
void cmd_agent_register(socket_entry* agent);
int cmd_agent_register_handler(socket_entry* entry,char* buf);

#endif
