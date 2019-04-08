#pragma once

#pragma warning (disable: 4786)
#include <time.h>
#include "DbConnection.h"

extern "C" IDB_CONNECTION_DLL IDbConnectionFactory* IDbConnectionFactoryCreate(char szDbIniFile[]);

class IDB_CONNECTION_DLL CSafeSet
{
public:
    CSafeSet(CDbResultSet*pSet);
    ~CSafeSet();
    bool isEmpty(){ return _pSet==NULL; }
    virtual bool GetNext(){ return _pSet&&_pSet->GetNext(); };
    virtual const char* GetString(unsigned int Index){ return _pSet->GetString(Index); };
private:
    CSafeSet();
    CDbResultSet *_pSet;
};


class IDB_CONNECTION_DLL CSafeConnect
{
public:
    CDbResultSet* QueryDatabase(const string& SQL="")
	{
        //MY_PRINT("Sql[%s]\n", SQL.c_str());
		return m_pConn->QueryDatabase(SQL);
	}
	
	// 返回上次更新记录数
    int UpdateDatabase(const string& SQL="")
	{
        //MY_PRINT("Sql[%s]\n", SQL.c_str());
		return m_pConn->UpdateDatabase(SQL);
	}
	int UpdateDatabaseAndCommit(const string& SQL="")
	{
		int bRet = m_pConn->UpdateDatabase(SQL);
		m_pConn->Commit();
		return bRet;
	}
	int UpdateDatabaseBuf(const string& SQL="")
	{
		int bRet = m_pConn->UpdateDatabase(SQL);
		m_nCurCount++;
		m_nCurCount &= m_cuMaxCount;
		if(m_nCurCount == 0)
			m_pConn->Commit();
		return bRet;
	}
	void Begin()
	{
		m_pConn->Begin();
	}
	void Commit()
	{
		m_pConn->Commit();
	}
	void RollBack()
	{
		m_pConn->RollBack();
	}
	void SetDate(unsigned id, time_t nSec)
	{
		struct tm tmNow={0};
		//localtime_r(&nSec, &tmNow);
		SetDate(id, tmNow.tm_year+1900, tmNow.tm_mon+1, tmNow.tm_mday,
			tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
	}
	void SetSql(const string&SQL)
	{
		m_pConn->SetSql(SQL);
	}
	void SetStr(unsigned id, const string&s)
	{
		m_pConn->SetStr(id, s);
	}
	void SetInt(unsigned id, int n)
	{
		m_pConn->SetInt(id, n);
	}
	void SetDate(unsigned id, int nYear, unsigned nMonth, unsigned nDay,
		unsigned nHour=0, unsigned nMin=0, unsigned nSec=0)
	{
		m_pConn->SetDate(id, nYear, nMonth, nDay, nHour, nMin, nSec);
	}
	
	// 获取第一个查找到的字符串（一行一列）
	string GetFirstData(const string& SQL, bool&bHasFind);
	
public:
	static bool Init(char*pDbCfgFile);
	static IDbConnectionFactory*GetFac();
	CSafeConnect(char *pFile=NULL, int nTime = 0xefffffff);
	~CSafeConnect(void);
	bool Check(){ return (m_pConn!=NULL); }
private:
	const unsigned m_cuMaxCount;
	int m_nCurCount;
	CDbConnection *m_pConn;
	IDbConnectionFactory *m_pDb;
};


