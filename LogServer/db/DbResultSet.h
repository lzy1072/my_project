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
    //������һ��
    virtual bool GetNext()=0;
    //��ָ��Index�е�������string�ķ�ʽ���أ�����Oracle����ID��1��ʼ
    virtual const char* GetString(unsigned int Index)=0;
	virtual void CloseSet()=0;
    virtual ~CDbResultSet(){}
};

