// BaseIdType.h: interface for the CBaseIdType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEIDTYPE_H__FA10246D_95E9_4B59_AEAD_3EA762C298BF__INCLUDED_)
#define AFX_BASEIDTYPE_H__FA10246D_95E9_4B59_AEAD_3EA762C298BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<vector>
using namespace std;

#ifndef CFG_CTR_DLL
#define CFG_CTR_DLL _declspec(dllimport)
#endif //CFG_CTR_DLL

#ifndef BYTE
typedef unsigned char       BYTE;
typedef BYTE            *LPBYTE;
#endif 

class CFG_CTR_DLL CBaseIdType  
{
protected:
    vector<long> m_vnData;
    int m_nDataLen;
public:
    int GetLen() const { return m_nDataLen; }
    vector<long> GetData() const { return m_vnData; }

	CBaseIdType(const CBaseIdType&);// 拷贝
	CBaseIdType(const LPBYTE lpBuf);// 设置 16进制
	CBaseIdType(const string& str=string(";"));// 设置 10进制
//    CBaseIdType(const int len=1);// 空
//    CBaseIdType(vector<long> data);// 设置
	~CBaseIdType();

    CBaseIdType& operator++();
    CBaseIdType operator++(int);
	bool operator==(const CBaseIdType&) const;
	bool operator<=(const CBaseIdType&) const;
	bool operator>=(const CBaseIdType&) const;
    CBaseIdType& operator=(const CBaseIdType&);// 拷贝
    
    void GetData(const LPBYTE lpBuf); // 获取 16进制
    CBaseIdType& CBaseIdType::operator=(const LPBYTE lpBuf);// 设置 16进制


    string GetStr();// 获取 10进制
    void SetStr(string str);// 设置 10进制

    bool IsEmpty();

};

#endif // !defined(AFX_BASEIDTYPE_H__FA10246D_95E9_4B59_AEAD_3EA762C298BF__INCLUDED_)
