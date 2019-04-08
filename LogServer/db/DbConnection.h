#pragma once

#pragma warning (disable: 4786)
#include "DbResultSet.h"
#include <string>
#include <vector>
using namespace std;

// 基础连接类（一般类型的数据库通用）
interface CDbConnection
{
public:
    virtual CDbResultSet *QueryDatabase(const string& SQL)=0;
    virtual int UpdateDatabase(const string& SQL)=0;
	virtual void Begin()=0;
	virtual void Commit()=0;
	virtual void RollBack()=0;
	virtual void SetSql(const string&SQL)=0;
	virtual void SetStr(unsigned id, const string&s)=0;
	virtual void SetInt(unsigned id, int n)=0;
	virtual void SetDate(unsigned id, int nYear, unsigned nMonth, unsigned nDay,
		unsigned nHour=0, unsigned nMin=0, unsigned nSec=0)=0;
    virtual ~CDbConnection(){}
	virtual vector<string> *GetBlobData(const string&sql)=0;
protected:
	friend class CDbCtrl;
	virtual void FreeMe()=0;
	virtual bool IsFree()=0;
};

interface IDbConnectionFactory
{
public:
	virtual CDbConnection* GetDb(int nTime = 0xefffffff)=0;
	virtual void ReleaseDb(CDbConnection*pDb)=0;
	virtual void Release()=0;
	virtual bool IsCtrlFree()=0;
};



