INC_PATH = -I../common -I./

CFLAGS =  -DLINUX=1 -ffunction-sections -fdata-sections
LDFLAGS = -Wl,--gc-sections
CC = gcc

SOURCE = user.c
SOURCE += ../common/socket_control.c
SOURCE += ../common/auto_infra.c
SOURCE += ../common/cmd_user_task_start.c
SOURCE += ../common/file_operation.c



OBJS = $(SOURCE:.c=.o)

.c.o:
	$(CC) -o $@ $(CFLAGS) $(INC_PATH) -c $<

user: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) 


