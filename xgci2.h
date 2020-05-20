//提供给外部系统用的头文件
#ifndef  _XGCI_H_
#define  _XGCI_H_

  //#include <string> 
 //using namespace std;
//抽象数据类型
#ifdef WIN32
#include  <windows.h> 
#endif

#ifdef WIN32
#define XG_API  __stdcall
#else
#define XG_API
#endif


#ifdef __cplusplus
extern "C" { 			/* Assume C declarations for C++   */
#endif  /* __cplusplus */

#ifdef WIN32
typedef		unsigned char       uchar;
typedef		char	            int8;
typedef		__int16             int16;
typedef		unsigned __int16	ushort;
typedef		unsigned int        uint;
typedef		__int32             int32;
typedef		unsigned __int32    uint32;
typedef		unsigned long	    ulong;
typedef		__int64             int64;
typedef		unsigned __int64    uint64;
typedef     unsigned int        size_t;
#else
typedef		unsigned char       uchar;
typedef		signed char       int8;
typedef		short               int16;
typedef		unsigned short	    ushort;
typedef		int                 int32;
typedef		unsigned int        uint32;
typedef		unsigned long	    ulong;
typedef		unsigned int	    uint;
// typedef		long long           int64;
typedef		unsigned long long  uint64;
typedef   long  unsigned int        size_t;
#endif
#define _LINUX
#ifdef _LINUX_NOAIX
typedef		long long           int64;
#endif

typedef  int32    XGCIRETURN;

#if !defined(bool) && !defined(__cplusplus)
typedef char  bool;
#endif

#ifndef true
#define true   1
#define false  0
#endif


#define MAX_NUMERIC_LEN	  64

//typedef struct NUMERIC_STRUCT
//{
//	uchar		precision; //精度
//	uchar  	    scale;     //标度
//	int8		sign;	   //符号 -- 1 代表正数，0 代表负数
//	char		val[MAX_NUMERIC_LEN]; //实际数字字串
//}NUMERIC;
typedef  char NUMERIC[MAX_NUMERIC_LEN];


typedef struct  TIME_STRUCT
{
    int32   hour;
    int32   minute;
    int32   second;
}TIME;


typedef struct  tagDATE_STRUCT
{
	int32   year;
    int32   month;
    int32   day;
}DATE_STRUCT;


typedef struct  DATETIME_STRUCT
{
    int32   year;
    int32   month;
    int32   day;
    int32   hour;
    int32   minute;
    int32   second;
    int32   fraction;
}DATETIME;

typedef   DATETIME  TIMESTAMP;

typedef struct YEAR_TO_MONTH_STRUCT
{
	int32	year;
	int32	month;
}YEAR_TO_MONTH;

typedef struct DAY_TO_SECOND_STRUCT
{
    int32   day;
    int32   hour;
    int32   minute;
    int32   second;
    int32   fraction; //毫秒
}DAY_TO_SECOND;


typedef enum  tagINTERVAL_TYPE
{
	INTERVAL_YEAR					= 1,
	INTERVAL_MONTH					= 2,
	INTERVAL_DAY					= 3,
	INTERVAL_HOUR					= 4,
	INTERVAL_MINUTE					= 5,
	INTERVAL_SECOND					= 6,
	INTERVAL_YEAR_TO_MONTH			= 7,
	INTERVAL_DAY_TO_HOUR			= 8,
	INTERVAL_DAY_TO_MINUTE			= 9,
	INTERVAL_DAY_TO_SECOND			= 10,
	INTERVAL_HOUR_TO_MINUTE			= 11,
	INTERVAL_HOUR_TO_SECOND			= 12,
	INTERVAL_MINUTE_TO_SECOND		= 13
}INTERVAL_TYPE;

typedef struct INTERVAL_STRUCT
{
    INTERVAL_TYPE	 intval_type;
	union{
	       YEAR_TO_MONTH  y2m;
	       DAY_TO_SECOND  d2s;
	}intval;
}INTERVAL;

//虚谷大对象数据类型
//typedef struct  XG_LOB_STRUCT
//{
//	int32    type;    //1为CLOB，2为BLOB
//	int32    len;     //大对象的长度
//	char   * pdata;   //数据指针
//}XG_LOB;

typedef  void *  LobLocator;
typedef void *   XGCIPOINTER;
//句柄类型
typedef enum   tagHANDLE_TYPE {
	 HT_UNKNOW,       //未知类型
	 HT_ENV,          //环境句柄
	 HT_SERVER,       //服务句柄
	 HT_SESSION,      //会话句柄
	 HT_CONNPOOL,     //连接池句柄
	 HT_STATEMENT,    //语句句柄
	 HT_BIND,         //绑定句柄
	 HT_DEFINE,       //定义句柄
	 HT_ERR,          //错误句柄
	 HT_RS,//结果集 //add 2014-12-09
	 //add for describe
	 XGCI_DTYPE_PARAM,

}HANDLE_TYPE;

//结果集类型
typedef enum tagResultType
{
	RESULT_UNKNOWN,
	RESULT_INSERT,
	RESULT_SELECT,
	RESULT_UPDATE,
	RESULT_DELETE,
}ResultType;

//参数输入输出类型
typedef enum  tagPARAM_TYPE{
	PARAM_UNKNOWN= 0,
	PARAM_IN     = 1,    //复合类型参数
	PARAM_OUT    = 2,    //输入参数
	PARAM_INOUT  = 3,    //输出参数
	
}PARAM_TYPE;

//typedef  void *   XGCIHANDLE;

struct XGCIHandle{
	HANDLE_TYPE type;       //句柄类型
};


//句柄定义
typedef struct XGCIHandle * XGCIHANDLE;

typedef XGCIHANDLE      XGCIHENV;
typedef XGCIHANDLE      XGCIHSRV;
typedef XGCIHANDLE      XGCIHSESS;
typedef XGCIHANDLE      XGCIHCONNPOOL;
typedef XGCIHANDLE      XGCIHSTMT;
typedef XGCIHANDLE      XGCIHBIND;
typedef XGCIHANDLE      XGCIHDEFINE;

//SQL数据类型定义
#define  SQL_BOOL          1
#define  SQL_TINYINT       2
#define  SQL_SMALLINT      3
#define  SQL_INTEGER       4
#define  SQL_BIGINT        5
#define  SQL_FLOAT         6
#define  SQL_DOUBLE        7
#define  SQL_NUMERIC       8
#define  SQL_DATE          9
#define  SQL_TIME          10
#define  SQL_DATETIME      11
#define  SQL_CHAR          12
#define  SQL_BINARY        13
#define  SQL_CLOB          14
#define  SQL_IMAGE         15
#define  SQL_BLOB          16

#define  SQL_INTERVAL_YEAR              20
#define  SQL_INTERVAL_MONTH             21
#define  SQL_INTERVAL_DAY               22
#define  SQL_INTERVAL_HOUR              23
#define  SQL_INTERVAL_MINUTE            24
#define  SQL_INTERVAL_SECOND            25
#define  SQL_INTERVAL_YEAR_TO_MONTH     26
#define  SQL_INTERVAL_DAY_TO_SECOND     27
#define  SQL_INTERVAL_DAY_TO_HOUR       28
#define  SQL_INTERVAL_DAY_TO_MINUTE     29
#define  SQL_INTERVAL_HOUR_TO_MINUTE    30
#define  SQL_INTERVAL_HOUR_TO_SECOND    31
#define  SQL_INTERVAL_MINUTE_TO_SECOND  32

#define  SQL_TIMESTAMP     SQL_DATETIME
			
//数据类型C定义
#define  XG_C_BOOL                                1
#define  XG_C_CHAR                                2
#define  XG_C_TINYINT                             3
#define  XG_C_SHORT                               4
#define  XG_C_INTEGER                             5
#define  XG_C_BIGINT                              6
#define  XG_C_FLOAT                               7
#define  XG_C_DOUBLE                              8
#define  XG_C_NUMERIC                             9
#define  XG_C_DATE	                              10
#define  XG_C_TIME			                      11
#define  XG_C_TIME_TZ                             12
#define  XG_C_DATETIME                            13
#define  XG_C_DATETIME_TZ                         14
#define  XG_C_BINARY                              15


#define  XG_C_INTERVAL                            21
//#define  XG_C_INTERVAL_YEAR				      22
//#define  XG_C_INTERVAL_MONTH			          23
//#define  XG_C_INTERVAL_DAY				      24
//#define  XG_C_INTERVAL_HOUR				      25
//#define  XG_C_INTERVAL_MINUTE			          26
//#define  XG_C_INTERVAL_SECOND	                  27
#define  XG_C_INTERVAL_YEAR_TO_MONTH	          28
//#define  XG_C_INTERVAL_DAY_TO_HOUR		      29
//#define  XG_C_INTERVAL_DAY_TO_MINUTE	          30
#define  XG_C_INTERVAL_DAY_TO_SECOND	          31
//#define  XG_C_INTERVAL_HOUR_TO_MINUTE	          32
//#define  XG_C_INTERVAL_HOUR_TO_SECOND	          33
//#define  XG_C_INTERVAL_MINUTE_TO_SECOND	      34

#define  XG_C_TIMESTAMP                           XG_C_DATETIME

#define  XG_C_LOB                                 40
//#define  XG_C_PTR                                 40  //指针类型，用于接收大对象数据
//#define  XG_C_CLOB                                41
//#define  XG_C_BLOB                                42



#define  XG_RESET_PARAM   1
#define  XG_RESET_DEFINE  2
#define  XG_RESET         3


/*-----------------------------Attributes--------------------------------------*/
//隔离级别
#define   XGCI_ISO_READONLY    1
#define   XGCI_ISO_READCOMMIT  2
#define   XGCI_ISO_READREPEAT  3
#define   XGCI_ISO_SERIAL      4

//字符集
#define   XGCI_CHARSET_GBK     1
#define   XGCI_CHARSET_GB2312  2
#define   XGCI_CHARSET_UTF8    3

//自动提交
#define   XGCI_AUTOCOMMIT_OFF  0
#define   XGCI_AUTOCOMMIT_ON   1

//安全连接
#define   XGCI_USESSL_FALSE    0
#define   XGCI_USESSL_TRUE     1
//事务回滚级别
#define ROLLBACK_TRANS 1
#define ROLLBACK_TOSAVEPOINT 2

//prepare语句句柄中 是否启用服务器游标   
#define USE_NOT_SERVER_CUR 0
#define USE_SERVER_CURSOR 1  //启用服务器端游标,默认不启动异步接收。 //
#define USE_SERVER_CURSOR_ASYNC 2  //启用服务器端游标时，同时启用异步接收 大规模查询 //
#define  XG_USE_DEFAULT 0   //默认情况 不启动服务器游标， 消耗大，对大多数小查询来说效率不高 //

/*-----------------------------------------------------*/
//环境属性
#define   XGCI_ATTR_ENV_VERSION   1
#define   XGCI_ATTR_ENV_USE_POOL   2

// conn pool handle attribute
#define XGCI_ATTR_CONNPOOL_TIMEOUT 7
#define XGCI_ATTR_CONNPOOL_IMAX    6
#define XGCI_ATTR_CONNPOOL_IMIN    5
//服务句柄属性
#define   XGCI_ATTR_SRV_IP        21		 
#define   XGCI_ATTR_SRV_PORT      22
#define   XGCI_ATTR_SRV_URL       23
#define   XGCI_ATTR_SRV_DBNAME    24     

//add 2019-02-14 add for turn_ips 
#define  _USE_TURN_IPS_
#ifdef  _USE_TURN_IPS_
#define  XGCI_ATTR_SRV_TURN_IPS  28 
#endif

//会话句柄属性
#define   XGCI_ATTR_SESS_USER         31 		 		
#define   XGCI_ATTR_SESS_PASS         32
#define   XGCI_ATTR_SESS_CHARSET      33
#define   XGCI_ATTR_SESS_TIMEZONE     34
#define   XGCI_ATTR_SESS_ENCRYPTOR    35
#define   XGCI_ATTR_SESS_ISOLEVEL     36
#define   XGCI_ATTR_SESS_SSL          37
#define   XGCI_ATTR_SESS_AUTO_COMMIT  38
#define   XGCI_ATTR_SESS_TIMEOUT      39
#define   XGCI_ATTR_SESS_LOB_DESCRIBER  40

//语句句柄属性
#define   XGCI_ATTR_STMT_
#define   XGCI_ATTR_STMT_PREPARE_WITH_SERVER_CURSOR  42

//描述信息属性
#define XGCI_ATTR_NAME  50
#define XGCI_ATTR_DATA_TYPE 51
#define XGCI_ATTR_ALIAS      52
#define XGCI_ATTR_DATA_SIZE  53
#define XGCI_ATTR_CHAR_SIZE  54
#define XGCI_ATTR_TYPE_NAME  55
#define XGCI_ATTR_CHAR_USED  56
#define XGCI_ATTR_DATA_IS_CHAR  57
#define XGCI_ATTR_PRECISION  58
#define XGCI_ATTR_SCALE      59
#define XGCI_ATTR_DATA_IS_NOTNULL  60



//结果集属性 add 2014-0707
#define XGCI_ATTR_COL_COUNT  61
#define XGCI_ATTR_ROW_COUNT  62

#define XGCI_ATTR_EFFECT_NUM 63
#define XGCI_ATTR_RESULT_TYPE 64 // add 2015-0727

#define XGCI_ATTR_SQL_TYPE 65

#define XGCI_NTS             -1                 //NULL结尾字符串

/*-----------------------------Error Return Values--------------------------------*/
#define XGCI_SUCCESS           0               //成功
#define XGCI_SUCCESS_WITH_INFO 1               //成功，但有提示或警告信息
#define XGCI_NO_DATA        100                //到达SELECT RESULT末尾，无数据
#define XGCI_NULL_ROW       101                //接受行数据时，网络无行数据，返回空行
#define XGCI_ERROR          -1                 //错误
#define XGCI_INVALID_HANDLE -2                 //无效句柄
#define XGCI_INVALID_ARG    -3                 //无效参数
#define XGCI_NET_ERROR      -4                 //网络错误
#define XGCI_MEM_ERROR      -5                 //内存错误
#define XGCI_INVALID_ATTR   -6                 //无效属性
#define XGCI_NO_RESULT      -7                 //到达结果集链表末尾

#define XGCI_BINDPARAM_NO_ERROR  -8            //参数绑定列号出错 add 2014-12-12
 //违反唯一值约束
 #define XGCI_UNIQ_ERR -13  
#define XGCI_TIME_OUT  -14
#define XG_CON_SOCKET_CLOSE  -16
 //数值超界
 #define XGCI_DATA_LEN_ERR -17
// add 2015-07-08 connection no_use for along time disconnect by server ,
//while when execute sql it will reconnect by driver 
#define XGCI_CON_TIME_OUT  -24
#define XGCI_SQL_TIME_OUT -25

//列级返回码
#define XGCI_NULL_DATA       -1                 //列为NULL，无数据返回
#define XGCI_TRUNCATED_DATA  -2                 //数据被截断
#define XGCI_DATATYPE_ERROR  -3                 //数据类型无法转换
#define XGCI_FLOW_DATA       -4                 //数据类型越界

typedef struct SLIST
{
	struct  SLIST * next;
}SLIST;


//结果集结构
typedef struct  Result_f{

	SLIST        * next;             //接入Statement结构用	
   //add 2014-12-09 for output result_set
 /* if use these funcs please use g++ instead of gcc 
 virtual bool  nextrow();
 virtual char* getString(int iColNum);
 virtual float getFloat(int iColNum);
 virtual int getInteger(int iColNum);
 virtual void rs_close();
*/
}Result_f;
//////////////////////////////接口定义/////////////////////////////////////////////////////////

//分配句柄
XGCIRETURN XG_API XGCIHandleAlloc( XGCIHANDLE parenthndp, XGCIHANDLE * hndlpp, HANDLE_TYPE type );

XGCIRETURN XG_API XGCIHandleFree( XGCIHANDLE hndp );

//取得句柄属性
XGCIRETURN XG_API XGCIHandleAttrGet( XGCIHANDLE hndp, int32 Attribute, void * ValuePtr, int32 BuffLen );

//设置句柄属性
XGCIRETURN XG_API XGCIHandleAttrSet( XGCIHANDLE hndp, int32 Attribute, const void * ValuePtr, int32 BuffLen );

//重置语句句柄属性
XGCIRETURN XG_API XGCIFreeStmt( XGCIHSTMT hndp,int32 Option );


//开始一个会话
XGCIRETURN XG_API XGCISessionBegin(XGCIHSESS sesshndp, char * puser, char * ppwd);

//关闭一个会话
XGCIRETURN XG_API XGCISessionEnd(XGCIHSESS sesshndp);



//PREPARE一个语句，参数str_len指定字符串的长度，当其为XGCI_NTS指示为NULL结尾字符串
XGCIRETURN XG_API XGCIPrepare(XGCIHSTMT hndlp,char* sql_str,int32 str_len);

//执行prepare的查询语句
XGCIRETURN XG_API XGCIExecute(XGCIHSTMT hndlp);

XGCIRETURN XG_API XGCIExecDirect(XGCIHSTMT hndlp,char* sql_str,int32 str_len);

Result_f * XG_API  XGCIExecDirect_f(XGCIHSTMT hndlp,char* sql_str,int32 str_len);//2014-12-09
Result_f * XG_API XGCIExecute_f(XGCIHSTMT hndlp);
//如果有多个结果集的话，就取得下一个结果集

XGCIRETURN XG_API XGCINextResult(XGCIHSTMT hndlp);

//取得结果集数据,单向取得
XGCIRETURN XG_API XGCIFetch(XGCIHSTMT hndlp);

//参数 Col_Number 列号从1 开始
XGCIRETURN XG_API XGCIGetData(XGCIHSTMT hndlp, int32 ColNumber, int32 TargetCType,  void * TargetValuePtr, int32 BufferLen, int32 * StrLenPtr);

//创建一个大对象，返回大对象结构指针
LobLocator XG_API XGCILobCreate(void);

//释放一个大对象，在2。0版本增加对引用记数的支持，当记数为0时，释放该大对象所拥有的内存区
XGCIRETURN XG_API XGCILobRelease(LobLocator  pLob);

//复位大对象结构
XGCIRETURN XG_API XGCILobReset(LobLocator pLob);

//把数据放入大对象定位器中 
XGCIRETURN XG_API XGCILobPutData(LobLocator  pLob, int32 DataLen, void * pData);

//返回大对象数据区的长度,和内部数据指针
XGCIRETURN XG_API XGCILobGetDataPtr(LobLocator  pLob, int32 * pDataLen, char ** ppOutData);

//拷贝指定偏移处的大对象数据到用户指定缓冲区
XGCIRETURN XG_API XGCILobGetData(LobLocator pLob,int32 DataOffset, int32 BuffLen, char * BuffPtr,int32 * pOutLen );

//通过名字绑定参数
XGCIRETURN XG_API XGCIBindParamByName(XGCIHSTMT Hndp,char* Name,PARAM_TYPE IoType,void * ValuePtr,int32 BuffSize,
						   int32 CType, int32 * rCodep, int32 * ActualLenp, int32 SqlType);

//bind param acording pos
XGCIRETURN XG_API XGCIBindParamByPos(XGCIHSTMT Hndp,int32 Position,PARAM_TYPE type,void * ValuePtr,int32 BuffSize,
						 int32 CType, int32 * rCodep, int32 * ActualLenp, int32 SqlType);
//定义输出列绑定
XGCIRETURN XG_API XGCIDefineByPos(XGCIHSTMT Hndp,int32 ColNum,void * ValuePtr,int32 BuffSize,
						 int32 CType, int32 * rCodep, int32 * ActualLenp);
//定义属性值取得
XGCIRETURN XG_API XGCIAttrGet(XGCIHANDLE hndlp,HANDLE_TYPE type,void* attributep,uint32* sizep,int attrtype);//20140707
 
XGCIRETURN XG_API XGCITransBegin(XGCIHSESS sesshndp);
XGCIRETURN XG_API XGCITransCommit(XGCIHSESS sesshndp);
XGCIRETURN XG_API XGCITransCreateSavepoint(XGCIHSESS sesshndp,int sp_no);//savepoint number

XGCIRETURN XG_API XGCITransRollback(XGCIHSESS sesshndp,int type,int lvl);// type 1 whole 2 to level

//错误信息取得
XGCIRETURN XG_API XGCIErrors(XGCIHSTMT Hndp,char* ccode,char* errmessage,int* rlen);

// add 2018-08-30 批量参数绑定
//bind param with array values  acording pos
XGCIRETURN XG_API XGCIBindParamArrayByPos(XGCIHSTMT Hndp,int32 Position,int32 param_num,PARAM_TYPE type,int32 array_size,void * ValuePtr,int32 BuffSize, 
						 int32 CType, int32 * rCodep, int32 * ActualLenp, int32 SqlType);
// add 2018-08-30 批量数据执行
XGCIRETURN XG_API XGCIExecDirectBatch(XGCIHSTMT hndlp,char* sql_str,int32 str_len);

XGCIRETURN XG_API XGCIParamGet(XGCIHANDLE hndlp,HANDLE_TYPE type,void ** ptr_param, int param_no);

#ifdef __cplusplus
}                                    /* End of extern "C" { */
#endif  /* __cplusplus */

#endif //_XGCI_H_
