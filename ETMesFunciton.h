// mgGLFile.h: interface for the mgGLFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ET_MES_FUNCTION_H__C6A03DCE_0A14_4775_8948_7A34461F061E__INCLUDED_)
#define AFX_ET_MES_FUNCTION_H__C6A03DCE_0A14_4775_8948_7A34461F061E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//返回的任务数据
struct TASK_DATA
{
	int id;			//流程ID
	int process;	//工序编码
	int pod;		//pod序号
	int taskState;	//任务状态，0未分配，1已分配，2已完成
	int modelFile;	//大货流程目录里是否含有样式文件,0表示没有
	CString error;	//错误信息
	CString name;	//流程名
	CString model;	//样式名
	CString json;	//相关订单，版单数据，团订为空
	CString jsonArray;	//相关订单，版单数据数组，团订为空
	CStringArray order;	//排料的多流程绑定，需要返回所有流程的名字
//	CString path;	//流程路径名
};

//返回的样式信息
struct MODEL_DATA
{
	int styleID;	//款式ID
	int modelID;	//样式ID
	int save;		//存储模式: 0表示独立模式,1表示敬爱法模式,-1表示减法模式
	CString style;	//款式名
	CString uri;	//路径，此路径形式如，BuyiStyle\201803\款名
	CString LastTime;	//该款式的最后修改时间
	CString error;	//错误信息
};

struct PDM_FILE
{
	int		m_action;	//0新建,1打开已有文件,2刷新版单
//	CString m_uUrl;		//上传的地址
//	CString m_dUrl;		//下载的地址
	CString	m_projectName;	//款名
	CString m_projectID;	//关联的订单ID
	CString m_saveURL;		//保存文件地址
	CString m_filename;		//下载到本地之后的文件全路径名，这也是判断是否有文件数据的依据
};

//订单类型
enum ERP_TYPE
{
	erp_error = 0,		//错误或者失败
	erp_model = 1,		//版单
	erp_order = 2,		//成衣生产单
	erp_td = 3,			//团订订单
	erp_gd = 4,			//个订订单
	erp_task = 5,		//调度系统任务
	erp_bom = 6,		//单件用量
};

typedef CString (CALLBACK *PDMSAVEFILE)(void* pDoc, LPCTSTR style, LPCTSTR projectID, LPCTSTR fileID, LPCTSTR fileName);

//进入管理系统界面
//thisUrl是和这个文件相关的版单(生产单)的页面地址
//json用于返回管理系统的订单或者版单信息
//locetePath是假如下载文件的话的本地目录, file是下载的文件相关的信息, 根据m_filename判断是否有文件被下载
//注意此文件的projectID和json中的id不一定一样
//返回值是实际数据类型
//返回erp_error表示失败或取消
_declspec(dllexport) ERP_TYPE mesPdmLogin(ERP_TYPE type, LPCTSTR thisUrl, LPCTSTR locetePath, CString& json, PDM_FILE* file);

//mesPdmLogin的简化版本
//返回值是实际数据类型
//返回erp_error表示失败或取消
_declspec(dllexport) ERP_TYPE mesPdmNoFile(ERP_TYPE type, CString& json);

//旧版本: 提交（保存）文件的页面的入口
_declspec(dllexport) bool mesPdmSave(LPCTSTR url, PDMSAVEFILE pFun, void* pDoc);

//提交（保存）文件的页面的入口
_declspec(dllexport) bool mesPdmSave(LPCTSTR url, PDMSAVEFILE pFun, void* pDoc, const CString& json);

//将数据反馈到管理系统,json是要反馈的数据
_declspec(dllexport) bool mesPdmFeedback(ERP_TYPE type, const CString& json);

//将硬件文件,上传到管理系统
_declspec(dllexport) bool mesPdmFile(const CStringArray& order, LPCTSTR orderType, LPCTSTR name, LPCTSTR type,
									 LPCTSTR filename, CString& error);

//将充绒数据上传到管理系统
_declspec(dllexport) bool mesPdmPost(const char utf8[], int nByte, CString& error);
_declspec(dllexport) bool mesPdmPost(const CString& cr, CString& error);

//使用google浏览器内核
_declspec(dllexport) void mesPdmUseChrome();

//使用IE浏览器内核
_declspec(dllexport) void mesPdmUseIE();

//读取地址设定文件
_declspec(dllexport) void mesPdmReadSetting(LPCTSTR filename);
_declspec(dllexport) void mesPdmReadSetting(LPCTSTR filename, int appType);

//编辑订单中的物料信息
_declspec(dllexport) int mesEditFabric(ERP_TYPE type, bool bEdit, CStringArray& mName, CString& json);

_declspec(dllexport) bool mesPostWebApi(LPCTSTR uri, const char utf8[], int nByte, CString& error);
_declspec(dllexport) bool mesPostWebApi(LPCTSTR uri, const CString& post, CString& error);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//job_number是工号
_declspec(dllexport) HANDLE mesLogin();

//job_number是工号
_declspec(dllexport) HANDLE mesLogin(LPCTSTR ip, int job_number);

//用于调试，返回XML数据
_declspec(dllexport) HANDLE mesLoginDebug(LPCTSTR ip, int job_number, CString& xml);

//释放登陆信息
_declspec(dllexport) void mesClose(HANDLE mesHandle);

//写日志
_declspec(dllexport) void mesWriteLog(HANDLE mesHandle, LPCTSTR text);

//客户授权使用淘工厂订单跟踪功能
_declspec(dllexport) bool tgcOauth(UINT lockNumber);

//上传淘工厂数据，并返回二维码信息
_declspec(dllexport) CString tgcUpload(HANDLE tgcHandle, UINT lockNumber, const char* json);


/*********************************这些函数不链接服务器*****************************************/

//删除文件夹
_declspec(dllexport) bool mesDeleteFolder(LPCTSTR src);

//创建文件夹，文件夹存在的话，会先删除
_declspec(dllexport) bool mesCreateFolder(LPCTSTR src);

//获得最近一次调用，服务器端的返回字符串，用于调试，只有mesLoginDebug初始化 mesHandle，才有效
_declspec(dllexport) void mesGetReturnString(HANDLE mesHandle, CString& string);


/*********************************这些函数不改变服务器*************************************/

//检查款式名是否已存在， 0表示不存在，1表示存在，2表示链接服务器失败
_declspec(dllexport) int mesCheckStyleName(HANDLE mesHandle, LPCTSTR style_name);

//检查样式名是否已存在
_declspec(dllexport) int mesCheckModelName(HANDLE mesHandle, LPCTSTR model_name);

//检查样式名是否已存在
_declspec(dllexport) int mesCheckOrderName(HANDLE mesHandle, LPCTSTR order_name);


//获得某个样式的(款式)路径,返回0表示成功
_declspec(dllexport) int mesGetModelInfo(HANDLE mesHandle, LPCTSTR model_name, MODEL_DATA& info);


//获得某个流程的名字,返回0表示成功
//id是流程id, process是工序号,帮助判断是那种流程
_declspec(dllexport) int mesGetTaskName(HANDLE mesHandle, int id, int process, CString& name);


/*************************************这些函数改变服务器***********************************/
//定时查询是否有和自己相关的事物物要处理，会向 pMainWnd 的发送 命令消息taskID，fileID
_declspec(dllexport) void mesWatcher(HANDLE mesHandle, int appType, CWnd* pMainWnd, int taskID, int fileID);

//返回0表示成功
//appType表示程序类型,1表示是排料程序,2表示是裁床调度程序,0表示打板程序和其他程序
_declspec(dllexport) int mesApplyTask(HANDLE mesHandle, int appType, TASK_DATA& rtn);

_declspec(dllexport) int mesApplyTaskByProcess(HANDLE mesHandle, int process, TASK_DATA& rtn);

//获得任务信息,id是mesApplyTask返回的的rtn.id
//此函数适于在mesApplyTask函数之后，下载失败了，重新下载或者刷新数据
//但是这个函数不适合工序35,35应该用 mesGetTaskName
_declspec(dllexport) int mesGetTaskInfo(HANDLE mesHandle, int appType, int id, TASK_DATA& rtn);

//退回到前一道工序, 返回0表示成功，出错时内部弹出对话框显示提示信息
_declspec(dllexport) int mesGoBack(HANDLE mesHandle, int id, int process);

//中断此流程, 返回0表示成功，出错时内部弹出对话框显示提示信息
_declspec(dllexport) int mesStop(HANDLE mesHandle, int id, int process);


/*************************************完成任务和文件上传***********************************/


//结束某个流程的某道工序, 返回0表示成功，出错时内部弹出对话框显示提示信息
//pstrLocalRoot，pstrFileName，pstrDirName的含义与mesUpload相同,这三个值都可以是NULL
_declspec(dllexport) int mesFinishTask(HANDLE mesHandle, int id, int process, 
									   LPCTSTR pstrLocalRoot = NULL, LPCTSTR pstrFileName = NULL, LPCTSTR pstrFileName2 = NULL, LPCTSTR pstrDirName = NULL);

_declspec(dllexport) int mesFinishTask2(HANDLE mesHandle, int id, int process, LPCTSTR markJson,
									   LPCTSTR pstrLocalRoot = NULL, LPCTSTR pstrFileName = NULL, LPCTSTR pstrFileName2 = NULL, LPCTSTR pstrDirName = NULL);

//专门为检查POD定制, taskName,pstrLocalRoot,pstrFileName都不为NULL，才表示该pod文件被修改了
_declspec(dllexport) int mesFinishPod(HANDLE mesHandle, int id, int pod, LPCTSTR taskName,  LPCTSTR pstrLocalRoot, LPCTSTR pstrFileName);

//创建一个新流程, 其第一道工序（process）实际上已经完成
//pstrLocalRoot，pstrFileName，pstrDirName的含义与mesUpload相同
_declspec(dllexport) int mesCreate(HANDLE mesHandle, LPCTSTR taskName, int process, 
								   LPCTSTR pstrLocalRoot, LPCTSTR pstrFileName, LPCTSTR pstrFileName2, LPCTSTR pstrDirName);

/*************************************文件上传和下载函数***********************************/

//服务器的路径名问题：

//mesUpload和mesGetDownloadUrl都是针对流程目录(BuyiWork)的，因此他们的参数 pstrRemoteRoot 从BuyiWork之下的一级子目录开始的
//假设有一个流程的名字是"FD123", 其下有Pod目录，我们需要将文件 FD123[2]#.pod上传到这个目录,
//则pstrRemoteRoot=FD123\A1, pstrFileName=FD123[2]#.pod
//假设我们要将Pod整个下载, 则pstrRemoteRoot = FD123, pstrDirName = Pod


//mesDownload可以在在服务器上的任何文件, 因此其根目录是BuyiRoot,
//因此mesDownload的参数 pstrRemoteFileName 或者 url 都是从某个预定义的主目录开始的
//其值只能是以下四个值的其中之(BuyiStyle, BuyiHistory, BuyiWork, BuyiCut)


//上传pstrFileName和pstrDirName之下的所有文件
//pstrFileName和pstrDirName可以有一个是NULL
//pstrRemoteRoot开头不要加\, 如果文件上传根目录, pstrRemoteRoot是空就可以了, 如果上传到2级子目录就写: 子目录\子目录
//pstrRemoteRoot和pstrLocalRoot最后都必须不是"\"
_declspec(dllexport) int mesUpload(HANDLE mesHandle, LPCTSTR pstrRemoteRoot, LPCTSTR pstrLocalRoot,
													LPCTSTR pstrFileName,  LPCTSTR pstrFileName2, LPCTSTR pstrDirName);


_declspec(dllexport) int mesFtpTest(HANDLE mesHandle, LPCTSTR pstrLocalRoot);

//这个函数仅仅获得流程目录中文件的"下载url", url和filename作为返回值可以直接作为mesDownload的参数
//使用它的好处在于,它可以利用FTP机制遍历服务器上的目录(pstrDirName)
_declspec(dllexport) int mesGetDownloadUrl(HANDLE mesHandle, LPCTSTR pstrRemoteRoot, LPCTSTR pstrLocalRoot,
								   LPCTSTR pstrFileName, LPCTSTR pstrDirName,
								   CStringArray& url, CStringArray& filename);

//下载一个文件, 一定从服务器下载新的
_declspec(dllexport) int mesDownload(HANDLE mesHandle, LPCTSTR pstrRemoteFileName, LPCTSTR pstrLocalFileName);

//下载多个文件目录, 一定从服务器下载新的
_declspec(dllexport) int mesDownload(HANDLE mesHandle, CStringArray& url, CStringArray& filename);

//下载多个文件目录，如果服务区文件比此时间新，则下载新的, time的形式是年月日时分201804281536
_declspec(dllexport) int mesDownload(HANDLE mesHandle, LPCTSTR time, CStringArray& url, CStringArray& filename);

//显示已经分配给自己，但是还未完成的任务，如果用户选择其中之一，则返回该任务的信息
//返回0表示用户选择了一个任务
_declspec(dllexport) int mesSelectTask(HANDLE mesHandle, int appType, int curID, TASK_DATA& rtn);


//查询和下载Pod文件, workPath是本机工作路径， fiename是下载到工作路径的文件全路径名
//返回0表示成功
_declspec(dllexport) int mesSelectPod(HANDLE mesHandle, LPCTSTR workPath, TASK_DATA& rtn, CString& fiename);


#endif // !defined(AFX_ET_MES_FUNCTION_H__C6A03DCE_0A14_4775_8948_7A34461F061E__INCLUDED_)

