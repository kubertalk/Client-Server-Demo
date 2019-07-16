#ifndef __SQL_OPERATION_H__
#define __SQL_OPERATION_H__
#include "/usr/include/mysql/mysql.h"

//mysql connection
//MYSQL *pMysqlConn;
//result set
//MYSQL_RES *pMysqlRes;
//an instance of a row from results
//MYSQL_ROW MysqlRow;

const char *pHostName = "localhost"; //or set remote ip
const char *pUserName = "root";
const char *pPassword = "guagua";
const char *pDbName = "automation";
const unsigned int DbPort = 3306;

void mysql_routine();

#endif
