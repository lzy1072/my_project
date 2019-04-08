#ifndef UDPLOGSERVER_H
#define UDPLOGSERVER_H

#include <QObject>
#include<Winsock2.h>   //��Ϊʹ�õ�winSock���еĺ���
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
	void dataManage();		//a��udp��������  b�������ݴ���db  c��������Ϣ�����ļ�
	void dataDiapose();		//������Ϣ�����ļ��������������ݿ�
	void dataINIDb();		//������Ҫ�������ݿ����Ϣ�������
private:
	void getTime(char*, const char*);	//��m_recvBuf��ȡʱ��
	void getMMS(char*, const char*);	//��m_recvBuf��ȡ����
	void getThread(char*, const char*);	//��m_recvBuf��ȡ�߳�
	void getFile(char*, const char*);	//��m_recvBuf��ȡ�ļ�
	void getDetails(char*, const char*);//��m_recvBuf��ȡ����
	void getRealTimeMessage();	//��ȡ���͸�ʵʱ���ڵ���Ϣ��
public slots:
	void slotChileThread();			//���з���
	void slotReSetSQLDelete(int);	//��ȡɾ������,����ɾ�����
signals:
	void signalSendMessageToRealTimeDia(char* message, int level);	//���͸������̵߳���־��Ϣ����־���
	void signalSendMessageToRealTimeDia(QString message, int level);
public:
	bool m_stop;						//��ֹ�̱߳��
private:
	CRzxCriticalSection &m_cri;
	char m_recvBuf[1024];		//���ݻ�����
	int m_nRec;				//�������ݳ���
	int m_nDays;          // ����m_nDays������
	char m_szSqlDel[256]; // ɾ��m_nDays��ǰ�����ݣ�ÿ����һ�δ���
	char m_send_to_realTime_dialog[256];	//ʵʱ����

	/*
	this�����У�m_thread = new QThread;
	this.moveToThread(m_thread);
	m_thread.start();
	�����ࣺ.h:  UDPLogServer* mUdpLogServer;
	.cpp mUdpLogServer = new UDPLogServer;	//�������Ѿ�ʵ�ּ���
	*/
	QThread* m_thread;			//����this�����߳�	
};

#endif // UDPLOGSERVER_H
