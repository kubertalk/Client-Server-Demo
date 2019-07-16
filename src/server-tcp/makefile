INC_PATH += -I../common \
           -I./ \
           -I /usr/include/mysql/

CFLAGS += -DLINUX=1 \
         -ffunction-sections \
         -fdata-sections 
LDFLAGS += -Wl,--gc-sections -pthread 
SQL_FLAGS = -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lm -lrt -ldl
#SQL_FLAGS = `mysql_config --libs`
CC = gcc 

SOURCE = server-tcp.c
SOURCE += ../common/cmd_agent_register.c
SOURCE += ../common/socket_control.c
SOURCE += ../common/auto_infra.c
SOURCE += ../common/cmd_agent_auto_start.c
SOURCE += ../common/cmd_user_task_start.c

SQL_SOURCE = ../common/sql_operation.c

SQL_OBJ = $(SQL_SOURCE:.c=.o) 
OBJS = $(SOURCE:.c=.o) 
#server mysql interface not used
# server-tcp-mysql: $(OBJS) $(SQL_OBJ) 
# 	$(CC) $(LDFLAGS) $(OBJS) $(SQL_OBJ) $(SQL_FLAGS) -o $@ 
server-tcp: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ 

.c.o:
	$(CC) -c $< $(CFLAGS) $(INC_PATH) -o $@ 

$(SQL_OBJ): $(SQL_SOURCE)
	$(CC) -c $< $(CFLAGS) $(INC_PATH) -o $@

clean:
	rm -f $(OBJS) $(SQL_OBJ)