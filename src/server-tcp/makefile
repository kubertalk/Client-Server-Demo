INC_PATH = -I../common -I./

CFLAGS = -DLINUX=1 -pthread -ffunction-sections -fdata-sections
LDFLAGS = -Wl,--gc-sections -pthread
CC = gcc 

SOURCE = server-tcp.c
SOURCE += ../common/cmd_agent_register.c
SOURCE += ../common/socket_control.c
SOURCE += ../common/auto_infra.c
SOURCE += ../common/cmd_agent_auto_start.c
SOURCE += ../common/cmd_user_task_start.c



OBJS = $(SOURCE:.c=.o)

.c.o:
	$(CC) -o $@ $(CFLAGS) $(INC_PATH) -c $<

server-tcp: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) 


