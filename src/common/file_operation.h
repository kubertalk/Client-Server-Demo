#ifndef __FILE_OPERATION_H__
#define __FILE_OPERATION_H__

#define AUTO_RDONLY	0x9
int auto_file_open(char* file_name, int auto_flags);
int auto_file_read(int fd, char* buf, int len);
#endif
