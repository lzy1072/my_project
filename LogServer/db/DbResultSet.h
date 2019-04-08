#pragma once


#ifndef WIN32

#define IDB_CONNECTION_DLL
#define interface struct

#else

#ifndef IDB_CONNECTION_DLL
#define IDB_CONNECTION_DLL _declspec(dllimport)
#endif // IDB_CONNECTION_DLL
#include <objbase.h>
#endif // IDB_CONNECTION_DLL

#include <string>
using namespace std;

interface CDbResultSet
{
public:
    //移向下一行
    virtual bool GetNext()=0;
    //把指定Index列的数据以string的方式返回；采用Oracle规则，ID从1开始
    virtual const char* GetString(unsigned int Index)=0;
	virtual void CloseSet()=0;
    virtual ~CDbResultSet(){}
};

