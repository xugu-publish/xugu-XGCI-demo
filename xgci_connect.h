
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>



#include "xgci2.h"

#define fatal(s) {printf("fatal: %s\n\n", s);exit(-1);}

#define get_dsn_info(K,C) {             \
                                        \
    if(!strcmp(K.Key, "ip")){           \
        C.ip = K.Value;                 \
    }else if(!strcmp(K.Key, "port")){   \
        C.port = atoi(K.Value);         \
    }else if(!strcmp(K.Key, "db")){     \
        C.db = K.Value;                 \
    }else if(!strcmp(K.Key, "user")){   \
        C.user = K.Value;               \
    }else if(!strcmp(K.Key, "pwd")){    \
        C.pwd = K.Value;                \
    }                                   \
}

typedef struct {

    char  *ip;
    int   port;
    char  *db;
    char  *user;
    char  *pwd;

    XGCIHANDLE  hdenv;
    XGCIHANDLE  hdsvr;
    XGCIHANDLE  hdsession;

}connect_t;

typedef struct {

    char   *Key;
    char   *Value;

}keyword_t;

/* {{
 * 
 * Defined in the file xgci_dml.c
 */
void xugusql_noneparam_dml(connect_t *pconn, char* sql);

/* {{
 * 
 * Defined in the file  
 */
#define xugusql_ddl(conn, sql) xugusql_noneparam_dml(conn, sql);
bool table_is_exist(connect_t *pconn,char* tab_name);

/* {{
 * 
 * Defined in the file xgci_dql.c
 */
void xugusql_noneparam_dql(connect_t *pconn, char* sql);

/* {{
 * 
 * Defined in the file xgci_dml.c
 */
void xugusql_withparam_dml(connect_t *pconn, char *sql);

/* {{
 * Defined in the file xgci_dml.c
 * */
void xugusql_prepare_dml(connect_t *pconn, char *sql);

/* {{
 * Defined in the file xgci_dml.c
 * */
void xugusql_batch_dml(connect_t *pconn, char *sql);

void xugusql_withparam_proc(connect_t *pconn, char *sql);
/* {{
 * 
 * Defined in the file xgci_connect.c
 */
int xugusql_error(XGCIHANDLE lasthd);

/* {{
 * 
 * Defined in the file xgci_connect.c
 */
int xugusql_connect(connect_t *pconn);

/* {{
 * 
 * Defined in the file xgci_connect.c
 */
void xugusql_disconnect(connect_t *pconn);

