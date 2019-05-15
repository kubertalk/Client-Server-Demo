#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "file_operation.h"

int auto_file_open(char* file_name, int auto_flags)
{
	int flags=0;
	if(auto_flags |AUTO_RDONLY)
		flags |= O_RDONLY;
	return open(file_name,O_RDONLY);
}

int auto_file_read(int fd, char* buf, int len)
{
	return read(fd,buf,len);
}
