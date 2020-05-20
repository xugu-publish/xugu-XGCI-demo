#include "xgci_connect.h"

bool table_is_exist(connect_t *pconn,char* tab_name)
{
 XGCIHANDLE  hdstmt;
 bool ret = false;
 char sql[1024]={0};
 sprintf(sql,"select count(*) from all_tables where upper(table_name)=upper('%s');",tab_name);
 
 int relt = XGCIHandleAlloc(pconn->hdsession, &hdstmt, HT_STATEMENT);
 if(relt < 0){
      xugusql_error(pconn->hdsession);
 }
 relt = XGCIExecDirect(hdstmt, sql, XGCI_NTS);
  if(relt < 0){
      xugusql_error(hdstmt);
  }
  relt= XGCIFetch(hdstmt);
  if(relt < 0){
      xugusql_error(hdstmt);
  }

  long long t_num = 0;
  int retlen=0;
  relt= XGCIGetData(hdstmt,1,XG_C_BIGINT,&t_num,8,&retlen);
  if(0!=t_num)
   ret=true;
   XGCIHandleFree(hdstmt);
 
 return ret;
}
