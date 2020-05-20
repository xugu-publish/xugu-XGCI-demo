
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

 
#include "xgci_connect.h"

int main(int argc, char *argv[])
{
    keyword_t  dsn[] = {
  
        {"ip", "127.0.0.1"},
        {"port", "5138"},
        {"db", "SYSTEM"},
        {"user", "SYSDBA"},
        {"pwd", "SYSDBA"}
    };

    connect_t  myconn;
    int i;

    for(i=0; i!=sizeof(dsn)/sizeof(keyword_t); i++){
    
        get_dsn_info(dsn[i], myconn)
    }

    int relt = xugusql_connect(&myconn);
    if(relt < 0){
   
        fatal("Failed to set handle attribute or assign handle");
    }

    /* {{ DDL
     * The function xugusql_noneparam_dml () is used 
     * to show how XGCI executes DDL statements
     */
    bool hv = table_is_exist(&myconn,"xugusql");
    if(hv){
     xugusql_ddl(&myconn,
             "drop table xugusql");
     }
    
    xugusql_ddl(&myconn, 
            "create table xugusql(c1 integer, \
                                  c2 varchar, \
                                  c3 boolean);");
    xugusql_ddl(&myconn, 
        "create or replace procedure \
            xugusql_proc(count in int, result out int) as \
         begin \
            result := 0; \
            for i in 1 .. count loop \
                insert into xugusql values(9, 'CCJ', false); \
                result := result+1; \
            end loop; \
         end;");

    /* {{ DML
     * The function xugusql_noneparam_dml() is used to show 
     * how XGCI executes SQL statements without parameters
     * */
    xugusql_noneparam_dml(&myconn, 
             "insert into xugusql values(1,'AJX', false);");

    /* {{ DML
     * The function xugusql_noneparam_dml() is used to show 
     * how XGCI executes SQL statements with parameters
     * */
    xugusql_withparam_dml(&myconn, 
             "insert into xugusql values(1, ?, true);");

    /* {{ DML
     * The function xugusql_prepare_dml () is used to show 
     * that XGCI executes prepared SQL statements 
     * */
    xugusql_prepare_dml(&myconn, 
             "insert into xugusql values(?,?,true);");

    /* {{ DML
     * The function xugusql_batch_dml() is used to show 
     * the usage of XGCI batch execution SQL
     * */
    xugusql_batch_dml(&myconn, 
             "insert into xugusql values(10,?,true);");
    
    /* {{ PROCEDURE
     *      
     * The function xgci_pro shows how to use XGCI to execute 
     * a stored procedure with parameters*/
    xugusql_withparam_proc(&myconn, "exec xugusql_proc(?,?);");

    /* {{ DQL
     * The function xugusql_noneparam_dql() is used to show 
     * that XGCI executes DQL statements without parameters
     * */
    xugusql_noneparam_dql(&myconn, "select * from xugusql;");

    /* {{ 
     *
     * Disconnect, recycle connection resources
     * */
    xugusql_disconnect(&myconn);    
}
