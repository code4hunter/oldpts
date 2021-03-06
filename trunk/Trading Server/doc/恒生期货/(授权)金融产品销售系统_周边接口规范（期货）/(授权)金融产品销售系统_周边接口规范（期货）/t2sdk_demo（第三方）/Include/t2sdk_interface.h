/** @file
* T2_SDK头文件
* @author  T2小组
* @author  恒生电子股份有限公司
* @version 1.0.0.2
* @date    20090327
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef _T2SDK_INTERFACE_H
# define _T2SDK_INTERFACE_H

#ifdef _WIN32
	#if !defined( FUNCTION_CALL_MODE )
	#define FUNCTION_CALL_MODE		__stdcall
	#endif
#else
	#define FUNCTION_CALL_MODE
#endif

struct IKnown
{
    virtual unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv) = 0;

    virtual unsigned long  FUNCTION_CALL_MODE AddRef() = 0;

    virtual unsigned long  FUNCTION_CALL_MODE Release() =  0;
};

///解包器接口
struct IF2ResultSet : public IKnown
{

	///取字段数
    /**@return 返回字段数.
      */
    virtual int FUNCTION_CALL_MODE GetColCount()=0;

    ///取字段名
    /** @param column:字段序号(以0为基数)
      * @return 返回字段名  下标越界 返回NULL
      */
    virtual const char * FUNCTION_CALL_MODE GetColName(int column)=0;

    //取字段数据类型
    /** @param column:字段序号(以0为基数)
      * @return:见上面常量定义;下标越界 返回-1
      */
    virtual char FUNCTION_CALL_MODE GetColType(int column)=0;


   ///取数字型字段小数位数
   /** @param column:字段序号(以0为基数)
     * @return int 返回字段数据小数位数 下标越界 返回-1
     */
   virtual int FUNCTION_CALL_MODE GetColScale(int column)=0;
  
   //取字段允许存放数据的最大宽度.
   /** @param column:字段序号(以0为基数)
     * @return int 返回字段宽度 下标越界 返回-1
     */
   virtual int FUNCTION_CALL_MODE GetColWidth(int column) = 0;

   ///取字段名对应的字段序号
   /**@param columnName: 字段名
     *@return 返回字段序号. 不存在返回-1
     */
   virtual int  FUNCTION_CALL_MODE FindColIndex(const char * columnName)=0;

    //
    //按字段序号(以0为基数)，取字段值(字符串)
    /**@param column:字段序号(以0为基数)
      *@return 字符串型字段值,下标越界返回NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStrByIndex(int column)=0;

    //按字段名，取字段值(字符串)
    /**@param columnName: 字段名
      *@return 字符串型字段值,不存在返回NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStr(const char * columnName)=0;

    //按字段序号(以0为基数)，取字段值
    /**@param column:字段序号(以0为基数)
      *@return 字符型字段值,下标越界返回'\0'.
      */
     virtual char  FUNCTION_CALL_MODE  GetCharByIndex(int column)=0;

    //按字段名，取字段值
    /**@param columnName: 字段名
     *@return 字符型字段值,不存在返回'\0'
     */
    virtual char   FUNCTION_CALL_MODE GetChar(const char * columnName)=0;

    //按字段序号，取字段值
    /**@param column:字段序号(以0为基数)
      *@return double型字段值,下标越界返回0
      */
    virtual double  FUNCTION_CALL_MODE GetDoubleByIndex( int column)=0;
    
	///按字段名，取字段值
    /**@param columnName:字段名
      *@return double型字段值,不存在返回0
      */
    virtual double  FUNCTION_CALL_MODE GetDouble(const char * columnName)=0;

    ///按字段序号，取字段值
    /**@param column:字段序号(以0为基数)
      *@return int型字段值,下标越界返回0
      */
    virtual int  FUNCTION_CALL_MODE GetIntByIndex(int column)=0;

    ///按字段名，取字段值
    /**@param columnName:字段名
      *@return int型字段值,不存在返回0
      */
    virtual int FUNCTION_CALL_MODE GetInt(const char * columnName)=0;

	///按字段序号获得字段值,二进制数据
	/**@param column: 字段序号(以0为基数)
	*@param   lpRawLen: [out]数据长度
	*@return : 数据首地址
	*/
	virtual void *  FUNCTION_CALL_MODE GetRawByIndex(int column,int * lpRawLen) = 0;

	///按字段名，取字段值
	/**@param columnName:字段名
	*@param   lpRawLen: [out]数据长度
	*@return : 数据首地址
	*/
	virtual void *  FUNCTION_CALL_MODE GetRaw(const char * columnName,int * lpRawLen) = 0;


	///最后一次取的字段值是否为NULL
   /**@return 0 是， 1不是
   */
    virtual int  FUNCTION_CALL_MODE WasNull()=0;

    ///取下一条记录
    virtual void  FUNCTION_CALL_MODE Next()=0;

    ///判断是否为结尾
    /**@return 1 是，0 不是;
      */
    virtual int  FUNCTION_CALL_MODE IsEOF()=0;
   
	///判断是否为空
    /**@return 1 是，0 不是;
      */
    virtual int  FUNCTION_CALL_MODE IsEmpty()=0;
    
    virtual void * FUNCTION_CALL_MODE Destroy() = 0;
};

struct IF2UnPacker;

///多结果集打包接口(一个包可有多个异构结果集)
/**执行序列:
 *
 * 0、准备： SetBuffer(),如果打包缓存区由调用者提供,则必须在BeginPack()之前准备;
 * 1、开始:  BeginPack(),打包器复位;
 *
 * 2、第一个结果集打包：
 *
 *(a)添加字段名列表域：AddField()
 *
 *(b)按照结果集二维表顺序，逐字段，逐条记录添加内容：AddValue()
 *
 * 3、设置第一个结果集的返回码(可选，如果返回码为0则不用设置) SetFirstRetCode()
 *
 * 4、打下一个结果集(可选) NewDataSet()，此处同时设置了该结果集的返回码；
 * 
 * 5、参考第2步实现一个结果集打包；
 *
 * 6、结束：EndPack(),重复调用会导致加入空结果集;
 *
 * 7、取打包结果(缓存区，缓存区大小，数据长度)
 *    打包结果也可以直接解包UnPack()返回解包接口
 *
 *使用注意事项:IPacker所使用的内存缓存区，均由调用者控制；
 *             结果集附带的返回码，只有在包格式版本0x20以上时有效；
 */
struct IF2Packer : public IKnown
{
    ///打包器初始化(使用调用者的缓存区)
	/** 第一次使用打包器时，可先使用本方法设置好缓冲区(数据长度被置为iDataLen)
	 *@param  char * pBuf  缓冲区地址
 	 *@param  int iBufSize  缓冲区空间
 	 *@param  int iDataLen  已有数据长度，新增数据加在已有数据之后（只对V1.0格式的包有效） 	 
 	 */
	virtual void FUNCTION_CALL_MODE SetBuffer(void * pBuf,int iBufSize,int iDataLen=0 )=0;

	///复位，重新开始打另一个包(字段数与记录数置为0行0例)
	/**
	 * 功能：开始打包，把包长度清零(重复使用已有的缓存区空间)
	 *@return 无
	 */
	virtual void FUNCTION_CALL_MODE BeginPack(void)=0;

	///开始打一个结果集
	/**在打单结果集的包时，可以不调用本方法,均取默认值
	 *@param const char *szDatasetName 0x20版打包需要指明结果集名字
	 *@param int iReturnCode           0x20版打包需要为每个结果集指明返回值
	 */
	virtual int FUNCTION_CALL_MODE NewDataset(const char *szDatasetName, int iReturnCode = 0)=0;

	/**
	 * 功能：向包添加字段
	 *
	 *有执行次序要求:在 NewDataset()或Reset(),SetBuffer()之后,逐个字段按顺序添加;
	 *
	 *@param szFieldName：字段名
	 *@param cFieldType ：字段类型:I整数，F浮点数，C字符，S字符串，R任意二进制数据
	 *@param iFieldWidth ：字段宽度（所占最大字节数）
	 *@param iFieldScale ：字段精度,即cFieldType='F'时的小数位数(缺省为4位小数)
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddField(const char *szFieldName,char cFieldType ='S',int iFieldWidth=255,int iFieldScale=4)=0;

	/**
	 * 功能：向包添加字符串数据
     * 有执行次序要求:必须在所有字段增加完之后,逐个字段按顺序添加;
	 *@param       szValue：字符串数据
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddStr(const char *szValue)=0;

	/**
     * 功能：向包添加整数数据
 	 *@param       iValue：整数数据
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddInt(int iValue)=0;
	
    /**
	 * 功能：向包添加浮点数据
	 *@param       fValue：浮点数据
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddDouble(double fValue)=0;

	/**
	 * 功能：向包添加一个字符
	 *@param		 cValue：字符
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddChar(char cValue)=0;

	/**
	 * 功能：向包添加一个大对象
	 *@param	void * lpBuff 数据区
	 *@param	int iLen  数据长度	 
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddRaw(void * lpBuff,int iLen)=0;

    ///结束打包
	virtual void FUNCTION_CALL_MODE EndPack()=0;
 
	/**
     * 功能：取打包结果指针
	 *@return 打包结果指针
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;
	
	/**
     * 功能：取打包结果长度
     *@return 打包结果长度
	 */
	virtual int FUNCTION_CALL_MODE GetPackLen(void) = 0;
	
	/**
	 * 功能：取打包结果缓冲区大小
     *@return 打包结果缓冲区大小
	 */
	virtual int FUNCTION_CALL_MODE GetPackBufSize(void) = 0;
	
	/**
	 * 功能：取打包格式版本
     *@return 版本
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;
	
	///设置结果集的返回码(0x20版以上要求)，错误结果集需要设置
	/**返回码取缺省值0，则不设置，如果设置，则必须在EndPack()之前调用
     *@return 版本
	 */
	virtual void FUNCTION_CALL_MODE SetReturnCode(unsigned long dwRetCode) = 0;

	/**直接返回当前打包结果的解包接口,必须在EndPack()之后才能调用,在打包器释放时相应的解包器实例也释放
     *@return 解包器接口，此解包接口不能调用 destroy()来释放
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE UnPack(void) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE ClearValue() = 0;
};

///解包器接口
struct IF2UnPacker : public IF2ResultSet
{
	/**取打包格式版本
     *@return 版本
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;

	/**取解包数据长度
     *@return 							0 表示成功， 其它为失败
	 */
	virtual int FUNCTION_CALL_MODE Open(void * lpBuffer,unsigned int iLen) = 0;

    ///取结果集个数(0x20以上版本支持)
    virtual int FUNCTION_CALL_MODE GetDatasetCount()=0;

    ///设置当前结果集(0x20以上版本支持)
    /**
	 *@param  int nIndex				结果集编号
	 *@return int						0表示成功，否则为失败
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDatasetByIndex(int nIndex)=0;

    ///设置当前结果集 (0x20以上版本支持)
    /**
	 *@param  const char *szDatasetName	结果集名称
	 *@return int						0 表示成功，否则为失败
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDataset(const char *szDatasetName)=0;

	/** 取解包数据区指针
	 *@return 数据区指针
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;

	/** 取解包数据长度
     *@return 解包数据长度
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetPackLen(void) = 0;

	/**取解包数据记录条数,20051207以后版本支持
     *@return 记录条数
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetRowCount(void) = 0;
};

///连接对象 CConnectionInterface 的参数配置对象CConfigInterface
/**
* 包括从文件加载、保存到文件，读写操作
*/
class CConfigInterface: public IKnown
{
public:
	/**
    * 从文件加载
    * @param szFileName 文件名，格式类似ini，具体参考开发包示例
    * @return 返回0表示成功，否则失败
    */
    virtual int FUNCTION_CALL_MODE Load(const char *szFileName) = 0;

    /**
    * 保存到文件
    * @param szFileName 文件名
    * @return 返回0表示成功，否则失败
    */
    virtual int FUNCTION_CALL_MODE Save(const char *szFileName) = 0;

    /**
    * 取字符串值
    * @param szSection 节名
    * @param szEntry   变量名
    * @param szDefault 缺省值
    * @return 字符串值，没有找到时返回szDefault
    */
    virtual const char * FUNCTION_CALL_MODE GetString(const char *szSection, const char *szEntry, const char *szDefault) = 0;

    /**
    * 取整数值
    * @param szSection 节名
    * @param szEntry   变量名
    * @param iDefault  缺省值
    * @return 整数值，没有找到时返回iDefault
    */
    virtual int FUNCTION_CALL_MODE GetInt(const char *szSection, const char *szEntry, int iDefault) = 0;

    /**
    * 设置字符串值
    * @param szSection 节名
    * @param szEntry   变量名
    * @param szValue   值
    * @return 0表示成功，否则失败
    */
    virtual int FUNCTION_CALL_MODE SetString(const char *szSection, const char *szEntry, const char *szValue) = 0;

    /**
    * 设置整数值
    * @param szSection 节名
    * @param szEntry   变量名
    * @param iValue    值
    * @return 0表示成功，否则失败
    */
    virtual int FUNCTION_CALL_MODE SetInt(const char *szSection, const char *szEntry, int iValue) = 0;
};

class CConnectionInterface;

///连接对象 CConnectionInterface 需要的回调对象接口定义
/**
* 包括连接成功、连接断开、发送完成、收到数据等事件    
*/
class CCallbackInterface: public IKnown
{
public:
    /**
    * 套接字连接成功
    * @param lpConnection 发生该事件的连接对象
    */
    virtual void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection) = 0;

    /**
    * 完成安全连接
    * @param lpConnection 发生该事件的连接对象
    */
    virtual void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection) = 0;

    /**
    * 完成注册
    * @param lpConnection 发生该事件的连接对象
    */
    virtual void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection) = 0;

    /**
    * 连接被断开
    * @param lpConnection 发生该事件的连接对象
    */
    virtual void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection) = 0;

    /**
    * 发送完成
    * @param lpConnection 发生该事件的连接对象
    * @param hSend        发送句柄
    * @param reserved1    保留字段
    * @param reserved2    保留字段
    * @param nQueuingData 发送队列中剩余个数，使用者可以用此数值控制发送的速度，即小于某值时进行发送
    * @see Send()
    */
    virtual void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData) = 0;

    virtual void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d) = 0;

    virtual void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d) = 0;

    virtual int  FUNCTION_CALL_MODE Reserved3() = 0;

    virtual void FUNCTION_CALL_MODE Reserved4() = 0;

    virtual void FUNCTION_CALL_MODE Reserved5() = 0;

    virtual void FUNCTION_CALL_MODE Reserved6() = 0;

    virtual void FUNCTION_CALL_MODE Reserved7() = 0;

    /**
    * 收到SendBiz异步发送的请求的应答
    * @param lpConnection    发生该事件的连接对象
    * @param hSend           发送句柄
    * @param lpUnPackerOrStr 指向解包器指针或者错误信息
    * @param nResult         收包结果
    * 如果nResult等于0，表示业务数据接收成功，并且业务操作成功，lpUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于1，表示业务数据接收成功，但业务操作失败了，lpUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于2，表示收到非业务错误信息，lpUnPackerOrStr指向一个可读的字符串错误信息。
    * 如果nResult等于3，表示业务包解包失败。lpUnPackerOrStr指向NULL。
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult) = 0;
};

///T2_SDK连接对象接口
/**
* 包括连接、断开、发送、接收等
*/
class CConnectionInterface: public IKnown
{
public:
    ///连接状态，可组合
    enum ConnectionStatus
    {
        Disconnected	= 0x0000, /**< 未连接 */
        Connecting		= 0x0001, /**< socket正在连接 */
        Connected		= 0x0002, /**< socket已连接 */
        SafeConnecting	= 0x0004, /**< 正在建立安全连接 */
        SafeConnected	= 0x0008, /**< 已建立安全连接 */
        Registering		= 0x0010, /**< 正注册 */
        Registered		= 0x0020, /**< 已注册 */
        Rejected		= 0x0040  /**< 被拒绝，将被关闭 */
    };

    ///接收选项（可组合，0表示接收超时时，不删除包ID，仍可再次调用RecvBiz方法来尝试接收）
    enum RecvFlags
    {
        JustRemoveHandle = 0x0001   /**< 当接收超时时，把packet_id删除 */
    };

    /**
    * 初始化连接对象
    * @param lpCallback 回调对象
    * @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
    */
    virtual int FUNCTION_CALL_MODE Create(CCallbackInterface *lpCallback) = 0;

    /**
    * 开始连接/注册
    * @param uiTimeout 超时时间，单位毫秒，0表示不等待（使用代理连接服务器时，该参数不起作用）
    * @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE Connect(unsigned int uiTimeout) = 0;

    /**
    * 断开连接
    * @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE Close() = 0;

    virtual int FUNCTION_CALL_MODE Reserved1() = 0;

    virtual int FUNCTION_CALL_MODE Reserved2() = 0;

    virtual int FUNCTION_CALL_MODE Reserved3() = 0;

    virtual int FUNCTION_CALL_MODE Reserved4() = 0;

    virtual int FUNCTION_CALL_MODE Reserved5() = 0;

    virtual int FUNCTION_CALL_MODE Reserved6() = 0;

    /**
    * 取服务器地址
    * @param lpPort 输出的服务器端口，可以为NULL
    * @return 返回服务器地址
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;

    /**
    * 取连接状态
    * @return 返回连接状态
    */
    virtual int FUNCTION_CALL_MODE GetStatus() = 0;

    /**
    * 取服务器负载，使用者可以同时创建多个连接实例同时连接不同的服务器，根据完成连接的时间以及负载决定使用哪个服务器
    * @return 返回服务器负载（非负数），越大表示越繁忙，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE GetServerLoad() = 0;

    /**
    * 取错误码对应的错误信息，目前支持简体中文和英文，支持其他语言可以通过连接对象配置errormsg
    * @param nErrorCode 错误码
    * @return 返回错误信息
    */
    virtual const char * FUNCTION_CALL_MODE GetErrorMsg(int nErrorCode) = 0;

    /**
    * 取连接错误号，当连接无法与服务端完成注册时，既可通过Connect的返回值获取错误号，
    * 也可通过调用本方法来获取错误号，然后用该错误号调用GetErrorMsg可获取可读的错误信息
    * @return 返回连接错误号
    */
    virtual int FUNCTION_CALL_MODE GetConnectError() = 0;

    /**
    * 发送业务数据
    * @param iFunID      功能号
    * @param lpPacker    打包器指针
    * @param nAsy        0表示同步，否则表示异步
    * @param iSystemNo   如果iSystemNo > 0则设置系统号
    * @param nCompressID 对业务包体进行压缩的压缩算法ID，目前只支持ID = 1的压缩算法。
    * ID = 0表示不压缩。注意，压缩只是向SDK提出建议，是否真正压缩还取决于包的实际大小。
    * 同步发送的包，通过调用RecvBiz来接收，异步发送的包，当收到应答包后，自动触发回调函数OnReceivedBiz。
    * @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1) = 0;

    /**
    * 接收业务数据
    * @param hSend            发送句柄（SendBiz的成功返回值）
    * @param lppUnPackerOrStr 如果返回值等于0，表示业务数据接收成功，并且业务操作成功，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于1，表示业务数据接收成功，但业务操作失败了，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于2，表示收到非业务错误信息，*lppUnPackerOrStr指向一个可读的字符串错误信息。
    *                         如果返回值等于3，表示业务包解包失败。*lppUnPackerOrStr原先所指向的内容不会被改变。
    * @param uiTimeout        超时时间，单位毫秒。
    * @param uiFlag           接收选项，0表示接收超时后仍可继续调用RecvBiz来接收，
    *                         JustRemoveHandle表示当接收超时后，把hSend相关数据删除
    * @return 小于0表示RecvBiz操作本身失败，通过调用GetErrorMsg可以获取详细错误信息
    * 注意！外部指针所指向的解包器的内存由SDK内部管理，外部切勿释放！
    */
    virtual int FUNCTION_CALL_MODE RecvBiz(int hSend, void **lppUnPackerOrStr, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;
};

extern "C"
{
    /**
	* 获取T2_SDK的版本号
	* @return 当前T2_SDK的版本号，目前版本为0x01000002，表示1.0.0.2
	*/
    int FUNCTION_CALL_MODE GetVersionInfo();

    /**
	* 获取一个实现CConfigInterface接口的类的指针
	* @return 实现CConfigInterface接口的类的指针
	*/
CConfigInterface* FUNCTION_CALL_MODE NewConfig();

    /**
	* 获取一个实现CConnectionInterface接口的类的指针
	* @param CConfigInterface 实现CConfigInterface接口的类的指针
	* @return实现CConnectionInterface接口的类的指针
	*/
CConnectionInterface* FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig);

/**
* @param int iVersion 业务包格式版本(取值:1 字串版,其他值 0x20版)
* 推荐使用0x20版
* @return IPacker * 打包器接口指针
*/
IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);

/**
* @param void * lpBuffer 要解包的数据（不含AR通信包头）
* @param unsigned int iLen 数据长度
* @return IUnPacker * 结果集操作接口指针
*/
IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);

/**
* @param char *EncodePass 传出的散列结果，字符串，长度不超过16（包括'\0'）
* @param const char* Password 传入的待散列的密码
* @param int Key 影响散列结果的一个整数
* @return char * 传出的散列结果地址，同EncodePass
*/
char * FUNCTION_CALL_MODE Encode(char *EncodePass, const char* Password, int Key);
}

#endif
