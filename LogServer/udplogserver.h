#ifndef UDPLOGSERVER_H
#define UDPLOGSERVER_H

#include <QObject>
#include<Winsock2.h>   //因为使用到winSock库中的函数
#include<stdio.h>
#include<iostream>
#include <windows.h>
#include <string.h>
#include <QThread>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include "db/SafeConnect.h"
#include "Critical.h"
#pragma comment(lib,"ws2_32.lib")

class UDPLogServer : public QThread
{
	Q_OBJECT

public:
	UDPLogServer(CRzxCriticalSection &cri);
	~UDPLogServer();	 
public:
	void dataManage();		//a、udp接收数据  b、将数据存入db  c、调试信息存入文件
	void dataDiapose();		//调试信息存入文件，其它存入数据库
	void dataINIDb();		//解析需要存入数据库的信息，存入库
private:
	void getTime(char*, const char*);	//从m_recvBuf获取时间
	void getMMS(char*, const char*);	//从m_recvBuf获取毫秒
	void getThread(char*, const char*);	//从m_recvBuf获取线程
	void getFile(char*, const char*);	//从m_recvBuf获取文件
	void getDetails(char*, const char*);//从m_recvBuf获取内容
	void getRealTimeMessage();	//获取发送给实时窗口的信息；
public slots:
	void slotChileThread();			//运行服务
	void slotReSetSQLDelete(int);	//获取删除天数,重设删除语句
signals:
	void signalSendMessageToRealTimeDia(char* message, int level);	//发送给界面线程的日志信息和日志界别
	void signalSendMessageToRealTimeDia(QString message, int level);
public:
	bool m_stop;						//终止线程标记
private:
	CRzxCriticalSection &m_cri;
	char m_recvBuf[1024];		//数据缓冲区
	int m_nRec;				//接收数据长度
	int m_nDays;          // 保留m_nDays天数据
	char m_szSqlDel[256]; // 删除m_nDays天前的数据（每天做一次处理）
	char m_send_to_realTime_dialog[256];	//实时数据

	/*
	this构造中：m_thread = new QThread;
	this.moveToThread(m_thread);
	m_thread.start();
	调用类：.h:  UDPLogServer* mUdpLogServer;
	.cpp mUdpLogServer = new UDPLogServer;	//构造中已经实现监听
	*/
	QThread* m_thread;			//接纳this的子线程	
};

#endif // UDPLOGSERVER_H
