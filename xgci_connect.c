


#include "xgci2.h"
#include "xgci_connect.h"

/*
 * In the structured programming process, when the previous 
 * layer of function call fails, the function xugusql_error() 
 * is used to obtain relevant error diagnosis information
 */
int xugusql_error(XGCIHANDLE lasthd){

    char      msg[512] = {0}, errcode[7]={0};
    unsigned  length;

   //+------------------------------+
   //| XGCI API | XGCIErrors()      |
   //+------------------------------+
    XGCIErrors(lasthd, errcode, msg, &length);
    fatal(msg);

}


/*
 * The xugusql_connect() function is used to establish 
 * a new connection with the specified XUGU database server
 */
int xugusql_connect(connect_t *pconn){

     /* {{ assign XGCI statement handle 
      * 
      * +--------------------------------+
      * | XGCI API | XGCIHandleAlloc()   |
      * +--------------------------------+
      * */
    int relt = XGCIHandleAlloc(NULL, 
        &pconn->hdenv, HT_ENV);
    if(relt < 0){
        return 1; 
    }
     /* {{ assign XGCI service handle */
    relt = XGCIHandleAlloc(pconn->hdenv, 
        &pconn->hdsvr, HT_SERVER); 
    if(relt < 0){
        return 1;
    }
     /* 
      * Set the IP address of the 
      * XG database target host
      * 
      * +----------------------------------+
      * | XGCI API | XGCIHandleAttrSet()   |
      * +----------------------------------+
      */
    XGCIHandleAttrSet(pconn->hdsvr, 
        XGCI_ATTR_SRV_IP, pconn->ip, XGCI_NTS);
    /*
     * Set the access port number 
     * of the XG database target host
     */
    XGCIHandleAttrSet(pconn->hdsvr, 
        XGCI_ATTR_SRV_PORT, &pconn->port, XGCI_NTS);
    /*
     * Set the database name of 
     * the XG database service
     */
    XGCIHandleAttrSet(pconn->hdsvr, 
        XGCI_ATTR_SRV_DBNAME, pconn->db, XGCI_NTS);

     /* {{ assign XGCI session handle */
    relt = XGCIHandleAlloc(pconn->hdsvr, 
        &pconn->hdsession, HT_SESSION);
    if(relt < 0){
        return 1;
    }
    /*set the character set */
     int char_set = XGCI_CHARSET_UTF8;
     XGCIHandleAttrSet(pconn->hdsession,XGCI_ATTR_SESS_CHARSET,(int*)&char_set,XGCI_NTS);
    /* new connection 
     * 
     * +---------------------------------+
     * | XGCI API | XGCISessionBegin()   |
     * +---------------------------------+
     * */
    relt = XGCISessionBegin(pconn->hdsession, pconn->user, pconn->pwd);
    if(relt < 0){
        xugusql_error(pconn->hdsession); 
    }

    // new connection succeeded
    return 0; 
}


/*
 * Disconnect, recycle connection resources
 */
void xugusql_disconnect(connect_t *pconn){
    
    /* {{ disconnect
     *
     * +-----------------------------+
     * | XGCI API | XGCISessionEnd() |
     * +-----------------------------+
     */ 
    int relt = XGCISessionEnd(pconn->hdsession);
    if(relt < 0){
        xugusql_error(pconn->hdsession);    
    }

    /* {{ Release the session handle 
     *
     * +------------------------------+
     * | XGCI API | XGCIHandleFree()  |
     * +------------------------------+
     */
    XGCIHandleFree(pconn->hdsession);

    // {{ Release the service handle 
    XGCIHandleFree(pconn->hdsvr);

    // {{ Release the environment handle 
    XGCIHandleFree(pconn->hdenv);

}
