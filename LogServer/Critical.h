// Critical.h: interface for the CCritical class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRITICAL_H__765E2561_9CF6_436C_88EA_3C0C1BA8445A__INCLUDED_)
#define AFX_CRITICAL_H__765E2561_9CF6_436C_88EA_3C0C1BA8445A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class CRzxCriticalSection
{
public:
	CRzxCriticalSection()
	{
#ifndef WIN32
		pthread_mutex_t tt = PTHREAD_MUTEX_INITIALIZER;
		memcpy(&_critical, &tt, sizeof(pthread_mutex_t));
#else
		InitializeCriticalSection(&_critical);
#endif
	}
	~CRzxCriticalSection()
	{
#ifndef WIN32
#else
		DeleteCriticalSection(&_critical);
#endif
	}
private:
#ifndef WIN32
	pthread_mutex_t _critical;
#else
	CRITICAL_SECTION _critical;
#endif
	friend class CRzxCritical;
};

class CRzxCritical
{
public:
	CRzxCritical(CRzxCriticalSection &sec) : _critical(sec._critical)
	{
#ifndef WIN32
		pthread_mutex_lock(&_critical);
#else
		EnterCriticalSection(&_critical);
#endif
	}
	~CRzxCritical()
	{
#ifndef WIN32
		pthread_mutex_unlock(&_critical);
#else
		LeaveCriticalSection(&_critical);
#endif
	}
private:
#ifndef WIN32
	pthread_mutex_t &_critical;
#else
	CRITICAL_SECTION &_critical;
#endif
};

#endif // !defined(AFX_CRITICAL_H__765E2561_9CF6_436C_88EA_3C0C1BA8445A__INCLUDED_)
