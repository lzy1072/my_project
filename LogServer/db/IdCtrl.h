// IdCtrl.h: interface for the CIdCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDCTRL_H__1ABDC4E0_C50A_4D01_A253_046F33BC8166__INCLUDED_)
#define AFX_IDCTRL_H__1ABDC4E0_C50A_4D01_A253_046F33BC8166__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseIdType.h"

#ifndef CFG_CTR_DLL
#define CFG_CTR_DLL _declspec(dllimport)
#endif //CFG_CTR_DLL

class CCIdCtrlPriData;
class CFG_CTR_DLL CIdCtrl  
{
private:
	CCIdCtrlPriData*m_pDt;
public:
    CIdCtrl();
	CIdCtrl(const CBaseIdType & cidBegin);
	~CIdCtrl();
    void TestMe();

public:
	void Reset();
    void Init(const CBaseIdType &cidBegin);
	CBaseIdType &GetNewId();
    int AddId(const CBaseIdType &id);
    void RemoveId(const CBaseIdType&id);
};

#endif // !defined(AFX_IDCTRL_H__1ABDC4E0_C50A_4D01_A253_046F33BC8166__INCLUDED_)
