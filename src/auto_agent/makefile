INC_PATH = -I../common -I./

CFLAGS =  -DLINUX=1 -ffunction-sections -fdata-sections
LDFLAGS = -Wl,--gc-sections
CC = gcc

SOURCE = agent.c
SOURCE += ../common/cmd_agent_register.c
SOURCE += ../common/socket_control.c
SOURCE += ../common/auto_infra.c
SOURCE += ../common/cmd_auto_start.c




OBJS = $(SOURCE:.c=.o)

.c.o:
	$(CC) -o $@ $(CFLAGS) $(INC_PATH) -c $<

agent: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) 


