#include "udplogserver.h"
//UDPLogServer::UDPLogServer(QObject *parent)
//	: QObject(parent)
UDPLogServer::UDPLogServer(CRzxCriticalSection &cri)
:m_cri(cri)
{
	//��ʼ��ɾ������Ϊ5��
	m_nDays = GetPrivateProfileIntA("DbUse", "days", 5, "D:\\TQ1050\\cfg\\syslog.cfg");//���ļ��л�ȡ�ַ���
	sprintf(m_szSqlDel, "DELETE FROM TXLog WHERE date('now', '-%d days') >= date(datetime)", m_nDays+1);
	m_nRec = 0;
	m_stop = true;
	m_thread = new QThread;
	this->moveToThread(m_thread);
	m_thread->start();
}

UDPLogServer::~UDPLogServer()
{
	//�����˳��߳�
	m_stop = false;		//while����ֹ���
	m_thread->quit();		//������while��1�������޷������˳�
	//m_thread->terminate();	//�����˳�
	m_thread->wait();	
	delete m_thread;
	m_thread = NULL;
}

void UDPLogServer::dataManage()
{
	qDebug()<<"00000000000000000";
	int nPort = 8888;
	// ��һ�� �������׽��ֿ�
	WORD wVersionRequested = MAKEWORD(1, 1);    // ׼�����صİ汾 �� 2.1����ʾ���汾����2  
	WSADATA wsaData;    //���ϵͳ������صİ汾�� �Լ� �׽��ֿ��е���߰汾
	int err = WSAStartup(wVersionRequested, &wsaData);   //���سɹ��򷵻�0
	if (err != 0){
		//cout << "�����׽ӿ�ʧ��" << endl;
		return;
	}

	//���ϵͳ�����ʹ�õ��׽��ֿ�� ���汾�Ų�Ϊ1 ���� ���汾�Ų�Ϊ1
	//Ҳ����˵ ���ϵͳ������صİ汾���� 1.1����ô��ֹ���׽��ֿ��ʹ��
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();     //��ֹ���׽��ֿ��ʹ��
		return;
	}

	//�ڶ������������ݱ�ʽ�׽��֣�TCPЭ��ʹ�õ���ʽ�׽��֣�
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);     //��һ�������͵������������ù���

	//�����������׽��ְ󶨵� ���ص�ַ �� �˿���
	SOCKADDR_IN  addrSrv;       //������ű��ص�ַ �� �˿� �Ľṹ��

	addrSrv.sin_family = AF_INET;     //�̶��ģ����ù�
	//htonl�ǽ�unsigned longת��Ϊ�����ֽ�˳��
	//INADDR_ANY ��ʾ�Ǳ�����IP
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   //�󶨷�������IP��ַ  
	addrSrv.sin_port = htons(nPort);
	bind(sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	SOCKADDR_IN addrClient;    //���
	int len = sizeof(SOCKADDR);
	struct timeval tv_out;
	tv_out.tv_sec = 5;//�ȴ�10��
	tv_out.tv_usec = 0;
	setsockopt(sockSrv, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv_out, sizeof(tv_out));
	while(m_stop)
	{
		//��������ǰ��ջ�����
		m_nRec = 0;
		memset(m_recvBuf, 0, sizeof(m_recvBuf));
		//���岽 �շ�����
		m_nRec = recvfrom(sockSrv, m_recvBuf, 1024, 0, (SOCKADDR *)&addrClient, &len);
		if (m_nRec > 0) {
			getRealTimeMessage();
			//������ս��
			dataDiapose();
		}
	}
	closesocket(sockSrv);
}

void UDPLogServer::dataDiapose()
{
	//�����������Ƿ�����ж�
	if(m_nRec < 1025)
	{	m_recvBuf[m_nRec] = '\0';	}
	else
	{	return ;	}

	//�ļ�����
	FILE* fp = fopen("logDebug.txt","a");
	if (NULL == fp)
		return ;
	char tLevel = '0';
	memcpy(&tLevel, &m_recvBuf[3], 1);

	//1��debug����д���ļ�
	if('7' == tLevel){
		fwrite(m_recvBuf, sizeof(char), strlen(m_recvBuf),fp);
		fprintf(fp, "\n");
	}
	else{
		//2����������������ݿ�
		//��������
		dataINIDb();
	}
	fclose(fp);
}

void UDPLogServer::dataINIDb()
{
	CSafeConnect db;
	//�����������ݽ����������ݿ�
	/*ͨ��������ʱ�䣨time����ֵ+���룩���̡߳��ļ�������*/
	string strSql = "INSERT INTO TXLog VALUES ('";	//�洢sql���
	char chTemp[1024] = "1a";
	strSql += m_recvBuf[1];
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '
	strSql += m_recvBuf[3];
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', '
	getTime(chTemp, m_recvBuf);
	strSql += chTemp;
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', 'ʱ��', '
	getMMS(chTemp,m_recvBuf);
	strSql += chTemp;
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', 'ʱ��', '����','
	getThread(chTemp, m_recvBuf);
	strSql += chTemp; 
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', 'ʱ��', '�߳�', '
	getFile(chTemp, m_recvBuf);							
	strSql += chTemp;
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', 'ʱ��', '�߳�', '�ļ��к�', '
	getDetails(chTemp, m_recvBuf);						
	strSql += chTemp;
	strSql += "')";									//INSERT INTO txcncLog VALUES ('1', '7', 'ʱ��', '�߳�', '�ļ��к�', '����')

	CRzxCritical cri(m_cri);
	db.QueryDatabase(m_szSqlDel);	//ɾ��ÿ������
	db.QueryDatabase(strSql.c_str());
}

void UDPLogServer::slotChileThread()
{
	dataManage();
}

void UDPLogServer::getTime(char* result, const char* recv)
{
	int pre = 1;
	int back = 0;
	int temp = 0;
	for (int i = 0; i<1024; ++i)
	{
		if ((':' == recv[i]))
		{	++temp;	}
		if (temp < 2)
		{	++pre;	}
		if (temp < 3)
		{	++back;	}
		else
		{	break;	}
	}

	memcpy(result, &recv[pre], back - pre);

	//ʱ��תת����char* -> QString -> 0x -> 10;
	QDateTime testDate;
	QString qstrTime(result);
	qint64 iTime = qstrTime.toInt(0,16);
	testDate.setTime_t(iTime);
	string strTemp = testDate.toString("yyyy-MM-dd hh:mm:ss").toStdString();
	strcpy(result, strTemp.c_str());
}

void UDPLogServer::getThread(char* result, const char* recv)
{

	int pre = 1;
	int back = 0;
	int temp = 0;
	for (int i = 0; i<1024; ++i)
	{
		if ((':' == recv[i]))
		{	++temp;	}
		if (temp < 4)
		{	++pre;	}
		if (temp < 5)
		{	++back;	}
		else
		{	break;	}
	}
	memcpy(result, &recv[pre], back - pre);
	result[back - pre] = '\0';
	QString qstrTime(result);
	qint64 iTime = qstrTime.toInt(0,16);
	itoa(iTime, result, 10);
}

void UDPLogServer::getFile(char* result, const char* recv)
{
	int pre = 1;
	int back = 0;
	int temp = 0;
	for (int i = 0; i<1024; ++i)
	{
		if ((':' == recv[i]))
		{	++temp;	}
		if (temp < 5)
		{	++pre;	}
		if (temp < 6)
		{	++back;	}
		else
		{	break;	}
	}
	memcpy(result, &recv[pre], back - pre);
	result[back - pre] = '\0';
	for (int i = 0; i < 4; ++i)
	{
		if (']' == result[i]){
			result[i] = ':';
		}
	}
}

void UDPLogServer::getDetails(char* result, const char* recv)
{
	int pre = 1;
	int back = 0;
	int temp = 0;
	for (int i = 0; i<1024; ++i)
	{
		if ((':' == recv[i]))
		{	++temp;	}
		if (temp < 6)
		{	++pre;	}
	}
	back = strlen(m_recvBuf);
	memcpy(result, &recv[pre], back - pre);
	result[back - pre] = '\0';
}

void UDPLogServer::getMMS(char* result, const char* recv)
{
	int pre = 1;
	int back = 0;
	int temp = 0;
	for (int i = 0; i<1024; ++i)
	{
		if ((':' == recv[i]))
		{	++temp;	}
		if (temp < 3)
		{	++pre;	}
		if (temp < 4)
		{	++back;	}
		else
		{	break;	}
	}

	memcpy(result, &recv[pre], back - pre);
	result[back - pre] = '\0';
}

void UDPLogServer::slotReSetSQLDelete(int value)
{
	sprintf(m_szSqlDel, "DELETE FROM TXLog WHERE date('now', '-%d days') >= date(datetime)", value+1);
	m_stop = true;
	dataManage();
}

void UDPLogServer::getRealTimeMessage()
{
	/*[1:7:5c1dacf0:29f:e74:78]AProxy.cpp:st:rv[220426248] end[86:40960] beg[0] buf[<axes><sub>pos</sub><
	  1 toInt ���ӻ�time  ����*/
	memset(&m_send_to_realTime_dialog, 0, sizeof(m_send_to_realTime_dialog));
	memcpy(&m_send_to_realTime_dialog[0], &m_recvBuf[0], 3);	//"[1:"
	m_send_to_realTime_dialog[3] = '\0';
	char chSend_level = m_recvBuf[3];	//"7"
	int send_level = atoi(&chSend_level);

	//��ȡʱ��
	char sendTo_realTime_time[10];
	memcpy(&sendTo_realTime_time[0], &m_recvBuf[5], 8);
	sendTo_realTime_time[8] = '\0';
	QDateTime testDate;//ʱ��תת����char* -> QString -> 0x -> 10;
	QString qstrTime(sendTo_realTime_time);
	qint64 iTime = qstrTime.toInt(0,16);
	testDate.setTime_t(iTime);
	string strTemp = testDate.toString("[hh:mm:ss]:").toStdString();
	memcpy(&m_send_to_realTime_dialog[strlen(m_send_to_realTime_dialog)], strTemp.c_str(), sizeof(strTemp));
	
	//��ʱ����沿�ָ���
	//memcpy(&m_send_to_realTime_dialog[strlen(m_send_to_realTime_dialog)], &m_recvBuf[14], strlen(m_recvBuf) - 13);	//����14�ǽ���һλ��'\0'Ҳ����
	int copy_length = strlen(m_recvBuf);
	if (copy_length > 256){
		copy_length = 255;//�ܿ�������
	}
	copy_length -= 14;	//13Ϊ��ʱ���:�� Ϊֹ���ַ�����
	memcpy(&m_send_to_realTime_dialog[strlen(m_send_to_realTime_dialog)], &m_recvBuf[14], copy_length);	//���һλ������
	m_send_to_realTime_dialog[copy_length + 14] = '\0';//�����ַ����뻺�����ַ������Ȳ�ͬ����Ҫ���ӽ�����	

	emit signalSendMessageToRealTimeDia(m_send_to_realTime_dialog, send_level);
}
