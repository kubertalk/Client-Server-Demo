#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/mysql/mysql.h"
#include "sql_operation.h"


void mysql_routine()
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_init(&mysql);

    if( !mysql_real_connect(&mysql, pHostName, pUserName, pPassword, pDbName, DbPort, 0, 0))
    {
        printf("mysql_real_connect fail\n");
       
    }

    if (mysql_real_query(&mysql, "select * from project", (unsigned long)strlen("select * from project")))
    {
        printf("mysql_real_query fail\n");
        ;
    }

    res = mysql_store_result(&mysql);
    if(NULL == res)
    {
        printf("mysql_store_result fail\n");
        printf("%s\n", mysql_error(&mysql) );
    }

    while(row = mysql_fetch_row(res))
    {
        printf("%s, %s\n", row[0], row[1]);
    }

    mysql_free_result(res);

    mysql_close(&mysql);

}