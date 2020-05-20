
#include "xgci_connect.h"



typedef struct {

    int   type;
    int   size; 
    char *pval;

}value_t;


/* {{
 *
 * The function xugusql_noneparam_dql() is used to show 
 * how XGCI executes DQL statements without parameters
 * */
void xugusql_noneparam_dql(connect_t *pconn, char* sql){

    // Statement statement handle
    XGCIHANDLE  hdstmt;

    /* {{ Assign XGCI statement handle
     * +-------------------------------+
     * | XGCI API | XGCIHandleAlloc()  |
     * +-------------------------------+
     */
    int relt = XGCIHandleAlloc(pconn->hdsession, &hdstmt, HT_STATEMENT);
    if(relt < 0){
        xugusql_error(pconn->hdsession);
    }

    /* {{ Execute SQL statement
     * +-------------------------------+
     * | XGCI API | XGCIExecDirect()   |
     * +-------------------------------+
     */
    relt = XGCIExecDirect(hdstmt, sql, XGCI_NTS);
    if(relt < 0){
        xugusql_error(hdstmt);
    }

    int fds = 0, rcode;
    /* {{ Get the value of the attribute XGCI_ATTR_COL_COUNT, 
     *    which is the number of columns in the result set
     * +---------------------------+
     * | XGCI API | XGCIAttrGet()  |
     * +---------------------------+
     */
    relt = XGCIAttrGet(hdstmt, HT_STATEMENT, &fds, &rcode, XGCI_ATTR_COL_COUNT);
    if(relt < 0){
        xugusql_error(hdstmt);
    }

    int i, length;
    value_t *p_res = (value_t *)calloc(fds, sizeof(value_t));

    for(i=0; i != fds; i++){
    
        void *handle;

        XGCIParamGet(hdstmt, HT_STATEMENT, &handle, i+1);
        /*
         * {{ Get the value of the attribute XGCI_ATTR_DATA_TYPE, that is, 
         * get the data type of the specified result column
         */
        XGCIAttrGet(
            (XGCIHANDLE)handle, 
            XGCI_DTYPE_PARAM,           
            &p_res[i].type,             // column data type 
            &rcode,                     // internal return code
            XGCI_ATTR_DATA_TYPE);
        /*
         * {{ Get the value of the attribute XGCI_ATTR_DATA_SIZE, that is, 
         * get the data size of the specified result column
         */
        XGCIAttrGet(
            (XGCIHANDLE)handle, 
            XGCI_DTYPE_PARAM, 
            &p_res[i].size,            // column data size 
            &rcode,                    // internal return code
            XGCI_ATTR_DATA_SIZE);

        /* {{ Other available attributes:

               * XGCI_ATTR_SQL_TYPE
               * XGCI_ATTR_PRECISION
               * XGCI_ATTR_SCALE
               * XGCI_ATTR_NAME
               * XGCI_ATTR_TYPE_NAME
        */

        switch(p_res[i].type){
                /*
                 * The data types of the following branches
                 * can use XG_C_CHAR to bind the result set
                 * */
            case XG_C_DATETIME_TZ:
            case XG_C_DATE:
            case XG_C_TIME:
            case XG_C_DATETIME:
            case XG_C_TIME_TZ:
            case XG_C_NUMERIC:
                p_res[i].type = XG_C_CHAR;
                p_res[i].size = 64;
        
                p_res[i].pval = calloc(1, p_res[i].size);
                break;
                /*
                 * Large object data type branch
                 * */
            case XG_C_LOB:
            case XG_C_BINARY:
                p_res[i].type = XG_C_LOB;
                p_res[i].size = 8;

                /*
                 * +-------------------------------+
                 * | XGCI API | XGCILobCreate()    |
                 * +-------------------------------+
                 * */
                p_res[i].pval = XGCILobCreate();

                break;
                /*
                 * Boolean processing
                 * */
            case XG_C_BOOL:
                p_res[i].type = XG_C_CHAR;
                p_res[i].size = 1;

                p_res[i].pval = calloc(1, p_res[i].size);
            default:
                p_res[i].pval = calloc(1, p_res[i].size);
                break;
        }

        /*
         * {{ Binding result set
         * +-------------------------------+
         * | XGCI API | XGCIDefineByPos()  |
         * +-------------------------------+
         */
        relt = XGCIDefineByPos(
                        hdstmt,         // statement handle 
                        i+1,            // column number
                        p_res[i].pval,  // store the data pointer of the result column
                        p_res[i].size,  /* The memory size of the address pointed 
                                            to by the 'p_res[i].pval' pointer */
                        p_res[i].type,  // column data type 
                        &rcode,         // internal return code
                        &length);       // actual data length of result column 

        if(relt < 0){
        
            xugusql_error(hdstmt);
        }
    }

    printf("The obtained result set:\n");
    while(1){
   
        /* {{ Get result set line by line 
         * +-------------------------+
         * | XGCI API | XGCIFetch()  |
         * +-------------------------+
         *
         * */
        relt = XGCIFetch(hdstmt);
        if(relt < 0){
          
            xugusql_error(hdstmt);
        }

        if(relt == XGCI_NO_DATA){

            /*
             * After the result set is obtained, 
             * the memory resources are released
             */
            for(i=0; i != fds; i++){
                
                if(p_res[i].pval != NULL){

                    free(p_res[i].pval);
                    p_res[i].pval = NULL;
                }
            }

            free(p_res);
            p_res = NULL;

            break;
        }

        printf("\t");
        for(i=0; i!=fds; i++){

            switch(p_res[i].type){
            
                    case XG_C_CHAR:
                            printf("%s\t", p_res[i].pval);
                            break;

                    case XG_C_TINYINT:
                    case XG_C_SHORT:
                    case XG_C_INTEGER:
                            printf("%d\t", *((int*)p_res[i].pval));
                            break;

                    case XG_C_BIGINT:
                            printf("%ld\t", *((long*)p_res[i].pval));
                            break;

                    case XG_C_FLOAT:
                            printf("%f\t", *((float*)p_res[i].pval));
                            break;

                    case XG_C_DOUBLE:
                            printf("%lf\t", *((double*)p_res[i].pval));
                            break;

                    case XG_C_LOB:
                            printf("<LOB>\t");

                            char *lob = NULL;
                            int   len = 0;

                            /*
                             * +---------------------------------+
                             * | XGCI API | XGCILobGetDataPtr()  |
                             * +---------------------------------+
                             *
                             * */
                            XGCILobGetDataPtr(p_res[i].pval, &len, &lob);
                            FILE *fp = fopen("./LOB", "w+");

                            if(fp != NULL){
                                fwrite(lob, 1, len, fp);
                                
                                fclose(fp);
                                fp = NULL;
                            }

                            break;
                    default:
                            break;
            }
        }
        printf("\n");
    }

    /* {{ Release the statement handle 
     *
     * +------------------------------+
     * | XGCI API | XGCIHandleFree()  |
     * +------------------------------+
     */
    XGCIHandleFree(hdstmt);
}
