
#include "xgci_connect.h"


/* {{
 * The function xugusql_noneparam_dml() is used to show 
 * how XGCI executes SQL statements without parameters
 * */
void xugusql_noneparam_dml(connect_t *pconn, char* sql){

    // Statement statement handle
    XGCIHANDLE  hdstmt;

    /* {{ Assign XGCI statement handle
     *
     * +-------------------------------+
     * | XGCI API | XGCIHandleAlloc()  |
     * +-------------------------------+
     */
    int relt = XGCIHandleAlloc(pconn->hdsession, &hdstmt, HT_STATEMENT);
    if(relt < 0){
        xugusql_error(pconn->hdsession);
    }

    /* {{ Execute SQL statement
     * 
     * +-------------------------------+
     * | XGCI API | XGCIExecDirect()   |
     * +-------------------------------+
     */
    relt = XGCIExecDirect(hdstmt, sql, XGCI_NTS);
    if(relt < 0){
        
        xugusql_error(hdstmt);
    }

    /* {{ Release the statement handle 
     *
     * +------------------------------+
     * | XGCI API | XGCIHandleFree()  |
     * +------------------------------+
     */
    XGCIHandleFree(hdstmt);
}


/* {{
 *
 * The function xugusql_noneparam_dml() is used to show 
 * how XGCI executes SQL statements with parameters
 * */
void xugusql_withparam_dml(connect_t *pconn, char *sql){

    // Statement statement handle
    XGCIHANDLE  hdstmt;

    /* {{ Assign XGCI statement handle
     */
    int relt = XGCIHandleAlloc(pconn->hdsession, &hdstmt, HT_STATEMENT);
    if(relt < 0){
        xugusql_error(pconn->hdsession);
    }

    char  va[] = "BJX";
    int  length = strlen(va), rcode;

    /* {{ Bind parameters based on placeholder position
     * +----------------------------------+
     * | XGCI API | XGCIBindParamByPos()  |
     * +----------------------------------+
     * 
     * */
    relt = XGCIBindParamByPos(hdstmt, 1, PARAM_IN, 
          va, length+1, XG_C_CHAR, &rcode, &length, SQL_CHAR);

    /* {{ Parameter binding for large object data:
     
      void *lob = XGCILobCreate();
     
     
      struct stat  sta;
      stat("./LOB.txt", &sta);
      char *pval = (char *)calloc(1, sta.st_size+1);
     
      FILE *fp = fopen("./LOB.txt", "r+");
      if(fp != NULL){
          fread(pval, 1, sta.st_size+1, fp);
          fclose(fp);
     
          fp = NULL;
      }
      
      length = sta.st_size;
      XGCILobPutData(lob, length, pval);
      relt = XGCIBindParamByPos(hdstmt, 1, PARAM_IN, 
            lob, 8, XG_C_LOB, &rcode, &length, SQL_CLOB);
     
    */


    /* {{ Execute SQL statement
     */
    relt = XGCIExecDirect(hdstmt, sql, XGCI_NTS);
    if(relt < 0){
        
        xugusql_error(hdstmt);
    }

    /* {{ Release the statement handle 
     */
    XGCIHandleFree(hdstmt);
      
}


/* {{ Prepare for the execution of SQL statements
 *
 * */
void xugusql_prepare_dml(connect_t *pconn, char *sql){

    // Statement statement handle
    XGCIHANDLE  hdstmt;

    /* {{ Assign XGCI statement handle
     */
    int relt = XGCIHandleAlloc(pconn->hdsession, &hdstmt, HT_STATEMENT);
    if(relt < 0){
        xugusql_error(pconn->hdsession);
    }

    /* {{ Prepare SQL statements
     * +----------------------------+
     * | XGCI API | XGCIPrepare()   |
     * +----------------------------+
     * */
    relt = XGCIPrepare(hdstmt, sql, XGCI_NTS);
    if(relt < 0){
    
        xugusql_error(hdstmt);
    }

    char va[] = "BJX";
    int  length = strlen(va), rcode = 0, len = sizeof(int), i;
    /* {{ Bind parameters based on placeholder position
     * */
    relt = XGCIBindParamByPos(hdstmt, 1, PARAM_IN, 
          &i, sizeof(int), XG_C_INTEGER, &rcode, &len, SQL_INTEGER);

    relt = XGCIBindParamByPos(hdstmt, 2, PARAM_IN, 
          va, length+1, XG_C_CHAR, &rcode, &length, SQL_CHAR);

    for(i = 0; i != 10; i++){

         va[0] = va[0] + i;

         /* {{ Execute prepared SQL statements 
          * +----------------------------+
          * | XGCI API | XGCIExecute()   |
          * +----------------------------+
          * */
         relt = XGCIExecute(hdstmt);
         if(relt < 0){
         
             xugusql_error(hdstmt);
         }
    }

    /* {{ Release the statement handle 
     */
    XGCIHandleFree(hdstmt);
      
}


/* {{ Batch execute SQL statements
 *
 * */
void xugusql_batch_dml(connect_t *pconn, char *sql){

    // Statement statement handle
    XGCIHANDLE  hdstmt;

    /* {{ Assign XGCI statement handle
     */
    int relt = XGCIHandleAlloc(pconn->hdsession, &hdstmt, HT_STATEMENT);
    if(relt < 0){
        xugusql_error(pconn->hdsession);
    }

    char *vas[5] = {
            "XXJ",
            "XXK",
            "XXL",
            "XXM",
            "XXN"};

    int rcode[5], len[5], i;
    for(i = 0; i != 5; i++){
       
        // Get actual length
        len[i] = strlen(vas[i]); 
    }

    /* {{ 
     * +----------------------------------------+
     * | XGCI API | XGCIBindParamArrayByPos()   |
     * +----------------------------------------+
     * */
    relt = XGCIBindParamArrayByPos(hdstmt, 
               1,              // bind parameter location 
               1,              // number of binding parameters
               PARAM_IN,       // parameter type
               5,              // number of batch binding parameters
               vas,            // data address of batch data
               len[i]+1,       // data size 
               XG_C_CHAR,      // data type
               rcode,          // return code
               len,            // data length
               SQL_CHAR);

    /* {{ 
     * +-----------------------------------+
     * | XGCI API | XGCIExecDirectBatch()  |
     * +-----------------------------------+
     * */
    relt = XGCIExecDirectBatch(hdstmt, sql, XGCI_NTS);
    if(relt < 0){
    
        xugusql_error(hdstmt);
    }
    
    /* {{ Release the statement handle 
     */
    XGCIHandleFree(hdstmt);
      
}
void xugusql_withparam_proc(connect_t *pconn, char *sql){

    XGCIHANDLE  hdstmt;

    /* {{ Assign XGCI statement handle
     *
     * XGCI API | XGCIHandleAlloc */
    int relt = XGCIHandleAlloc(
                    pconn->hdsession, &hdstmt, HT_STATEMENT);
    if(relt < 0){
        xugusql_error(pconn->hdsession);
    }

    int size = sizeof(int), length = sizeof(int);
    int va = 5, rcode;

    /* {{ Bind parameter, parameter type is input parameter
     *
     * XGCI API | XGCIBindParameterByPos */
    relt = XGCIBindParamByPos(
               hdstmt,          // Statement handle
               1,               // Parameter number
               PARAM_IN,        // Parameter type
               &va,             // Data
               size,            // Data size
               XG_C_INTEGER,    // Data type
               &rcode,          // Return code
               &length,         // Data length
               SQL_INTEGER);    // SQL type

    int cnt = 0;

    /* {{
     *
     * XGCI API | XGCIBindParamByPos */
    relt = XGCIBindParamByPos(
               hdstmt,        
               2,              
               PARAM_OUT,       // OUTPUT TYPE 
               &cnt,           
               size,            
               XG_C_INTEGER,   
               &rcode,          
               &length,         
               SQL_INTEGER);   

    /* {{
     * 
     * XGCI API | XGCIExecDirect */
    relt = XGCIExecDirect(hdstmt, sql, XGCI_NTS);
    if(relt < 0){
               
        xugusql_error(pconn->hdsession);
    }
  
    /* {{
     *
     * XGCI API | XGCIHandleFree */
    XGCIHandleFree(hdstmt);
}




