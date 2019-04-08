#ifndef __ANDROID_JNI_PUB_H__
#define __ANDROID_JNI_PUB_H__

// 以下日志支持AndroidJni与Linux 开关：_MY_JNI_LOG_
// linux 默认日志文件为 /var/log/messages

#include <stdio.h>
#include <string>
using namespace std;

#ifndef CFG_CTR_DLL
#define CFG_CTR_DLL _declspec(dllimport)
#endif //CFG_CTR_DLL

//#define _MY_JNI_LOG_
#ifdef _MY_JNI_LOG_
#include <jni.h>
#include <android/log.h>
#define LOG_TAG_NAME ((const char *)"AndroidJni")
//打印重大错误日记
#define LOGF(log, ...) ANDROID_LOG(ANDROID_LOG_FATAL, LOG_TAG_NAME, (const char *)__FILE__, __LINE__, ((const char *)log), ##__VA_ARGS__)
//打印错误日记
#define LOGE(log,...)  ANDROID_LOG(ANDROID_LOG_ERROR, LOG_TAG_NAME, (const char *)__FILE__, __LINE__, ((const char *)log), ##__VA_ARGS__)
//打印警告日记
#define LOGW(log, ...)  ANDROID_LOG(ANDROID_LOG_WARN, LOG_TAG_NAME, (const char *)__FILE__, __LINE__, ((const char *)log), ##__VA_ARGS__)
//打印调试日记
#define LOGD(log, ...) ANDROID_LOG(ANDROID_LOG_DEBUG, LOG_TAG_NAME, (const char *)__FILE__, __LINE__, ((const char *)log), ##__VA_ARGS__)
//打印信息日记
#define LOGI(log, ...)  ANDROID_LOG(ANDROID_LOG_INFO, LOG_TAG_NAME, (const char *)__FILE__, __LINE__, ((const char *)log), ##__VA_ARGS__)

jbyteArray strToJbyteArray(JNIEnv* env, const jbyte*pData, int nLen);
void jbyteArrayToStr(JNIEnv* env, jbyteArray barr, jbyte*&pData, int&nLen);

int CallJavaStaticWithName(JNIEnv *env, const char *pFuncName, jobject &jthis, jbyteArray arrData);
void ANDROID_LOG(int prio, const char *tag, const char *pFileName, int iLine, const char *pFmt, ...);
#else
#ifdef LINUX_SYS_LOG
#include <syslog.h>
#endif
#include <string.h>
#include <stdarg.h>
//日记类型
typedef enum
{
	FATAL_LOG=1,	//严重错误类型
	ERROR_LOG=3,		//错误类型
	WARN_LOG=4,		//警告类型
	INFO_LOG=6,		//信息类型
	DEBUG_LOG=7,		//调式类型
	LOG_ALL=8		//所有类型
}EnLog_Type;

class CFG_CTR_DLL LogWriter{  
public:  
	explicit LogWriter();
	~LogWriter();    
	void PrintLog(EnLog_Type level, const char*pFile, int nLine, const char* msg, ...);  
	void SaveFileLog(EnLog_Type level, const char*pFile, int nLine, const char* msg, ...);  
	void setLogPath(const string& logPath);         //defalut: current path  
	void setLogLevel(EnLog_Type logLevel);      //defalut: LOG_DEBUG  
private:  
private:  
	string _logPath;  
	EnLog_Type _logLevel;  
private:  
	const char* getLevelStr(EnLog_Type level);  
}; 

extern "C" CFG_CTR_DLL LogWriter* CreateLogWriter(EnLog_Type nLev = INFO_LOG);

//打印重大错误日记
#define LOGF(log, ...) CreateLogWriter()->PrintLog(FATAL_LOG, __FILE__, __LINE__, (log), ##__VA_ARGS__)

//打印错误日记
#define LOGE(log,...)  CreateLogWriter()->PrintLog(ERROR_LOG, __FILE__, __LINE__, (log), ##__VA_ARGS__)

//打印警告日记
#define LOGW(log, ...)  CreateLogWriter()->PrintLog(WARN_LOG, __FILE__, __LINE__, (log), ##__VA_ARGS__)

//打印调试日记
#define LOGD(log, ...)  CreateLogWriter()->PrintLog(DEBUG_LOG, __FILE__, __LINE__, (log), ##__VA_ARGS__)
//#define DEBUG(log, ...)

//打印信息日记
#define LOGI(log, ...)   CreateLogWriter()->PrintLog(INFO_LOG, __FILE__, __LINE__, (log), ##__VA_ARGS__)
//#define INFO(log, ...)

#endif

class CFG_CTR_DLL CTrace
{
public:
	CTrace(const char *pFuncName, const char *pFileName, int nLine);
	~CTrace();
private:
	const char *m_pFuncName;
	const char *m_pFileName;
	int m_nLine;
}; 

#define TRACE() CTrace trace((const char *)__FUNCTION__, (const char *)__FILE__, __LINE__);

#endif // __ANDROID_JNI_PUB_H__

