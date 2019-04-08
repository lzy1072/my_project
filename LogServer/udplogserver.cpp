#include "udplogserver.h"
//UDPLogServer::UDPLogServer(QObject *parent)
//	: QObject(parent)
UDPLogServer::UDPLogServer(CRzxCriticalSection &cri)
:m_cri(cri)
{
	//初始化删除天数为5天
	m_nDays = GetPrivateProfileIntA("DbUse", "days", 5, "D:\\TQ1050\\cfg\\syslog.cfg");//从文件中获取字符串
	sprintf(m_szSqlDel, "DELETE FROM TXLog WHERE date('now', '-%d days') >= date(datetime)", m_nDays+1);
	m_nRec = 0;
	m_stop = true;
	m_thread = new QThread;
	this->moveToThread(m_thread);
	m_thread->start();
}

UDPLogServer::~UDPLogServer()
{
	//优雅退出线程
	m_stop = false;		//while的终止标记
	m_thread->quit();		//里面有while（1）导致无法正常退出
	//m_thread->terminate();	//暴力退出
	m_thread->wait();	
	delete m_thread;
	m_thread = NULL;
}

void UDPLogServer::dataManage()
{
	qDebug()<<"00000000000000000";
	int nPort = 8888;
	// 第一步 ：加载套接字库
	WORD wVersionRequested = MAKEWORD(1, 1);    // 准备加载的版本 如 2.1：表示主版本号是2  
	WSADATA wsaData;    //存放系统打算加载的版本号 以及 套接字库中的最高版本
	int err = WSAStartup(wVersionRequested, &wsaData);   //加载成功则返回0
	if (err != 0){
		//cout << "加载套接库失败" << endl;
		return;
	}

	//如果系统打算的使用的套接字库的 主版本号不为1 或者 副版本号不为1
	//也就是说 如果系统打算加载的版本不是 1.1，那么终止对套接字库的使用
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();     //终止对套接字库的使用
		return;
	}

	//第二步：创建数据报式套接字（TCP协议使用的流式套接字）
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);     //第一个参数和第三个参数不用关心

	//第三步：将套接字绑定到 本地地址 和 端口上
	SOCKADDR_IN  addrSrv;       //用来存放本地地址 和 端口 的结构体

	addrSrv.sin_family = AF_INET;     //固定的，不用管
	//htonl是将unsigned long转化为网络字节顺序
	//INADDR_ANY 表示是本机的IP
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   //绑定服务器的IP地址  
	addrSrv.sin_port = htons(nPort);
	bind(sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	SOCKADDR_IN addrClient;    //存放
	int len = sizeof(SOCKADDR);
	struct timeval tv_out;
	tv_out.tv_sec = 5;//等待10秒
	tv_out.tv_usec = 0;
	setsockopt(sockSrv, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv_out, sizeof(tv_out));
	while(m_stop)
	{
		//处理数据前清空缓冲区
		m_nRec = 0;
		memset(m_recvBuf, 0, sizeof(m_recvBuf));
		//第五步 收发数据
		m_nRec = recvfrom(sockSrv, m_recvBuf, 1024, 0, (SOCKADDR *)&addrClient, &len);
		if (m_nRec > 0) {
			getRealTimeMessage();
			//处理接收结果
			dataDiapose();
		}
	}
	closesocket(sockSrv);
}

void UDPLogServer::dataDiapose()
{
	//缓存区数据是否合理判断
	if(m_nRec < 1025)
	{	m_recvBuf[m_nRec] = '\0';	}
	else
	{	return ;	}

	//文件操作
	FILE* fp = fopen("logDebug.txt","a");
	if (NULL == fp)
		return ;
	char tLevel = '0';
	memcpy(&tLevel, &m_recvBuf[3], 1);

	//1、debug级别写入文件
	if('7' == tLevel){
		fwrite(m_recvBuf, sizeof(char), strlen(m_recvBuf),fp);
		fprintf(fp, "\n");
	}
	else{
		//2、其它级别存入数据库
		//解析数据
		dataINIDb();
	}
	fclose(fp);
}

void UDPLogServer::dataINIDb()
{
	CSafeConnect db;
	//将缓冲区数据解析放入数据库
	/*通道、级别、时间（time返回值+毫秒）、线程、文件、内容*/
	string strSql = "INSERT INTO TXLog VALUES ('";	//存储sql语句
	char chTemp[1024] = "1a";
	strSql += m_recvBuf[1];
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '
	strSql += m_recvBuf[3];
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', '
	getTime(chTemp, m_recvBuf);
	strSql += chTemp;
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', '时间', '
	getMMS(chTemp,m_recvBuf);
	strSql += chTemp;
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', '时间', '毫秒','
	getThread(chTemp, m_recvBuf);
	strSql += chTemp; 
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', '时间', '线程', '
	getFile(chTemp, m_recvBuf);							
	strSql += chTemp;
	strSql += "', '";									//INSERT INTO txcncLog VALUES ('1', '7', '时间', '线程', '文件行号', '
	getDetails(chTemp, m_recvBuf);						
	strSql += chTemp;
	strSql += "')";									//INSERT INTO txcncLog VALUES ('1', '7', '时间', '线程', '文件行号', '内容')

	CRzxCritical cri(m_cri);
	db.QueryDatabase(m_szSqlDel);	//删除每天数据
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

	//时间转转测试char* -> QString -> 0x -> 10;
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
	  1 toInt 可视化time  保留*/
	memset(&m_send_to_realTime_dialog, 0, sizeof(m_send_to_realTime_dialog));
	memcpy(&m_send_to_realTime_dialog[0], &m_recvBuf[0], 3);	//"[1:"
	m_send_to_realTime_dialog[3] = '\0';
	char chSend_level = m_recvBuf[3];	//"7"
	int send_level = atoi(&chSend_level);

	//获取时间
	char sendTo_realTime_time[10];
	memcpy(&sendTo_realTime_time[0], &m_recvBuf[5], 8);
	sendTo_realTime_time[8] = '\0';
	QDateTime testDate;//时间转转测试char* -> QString -> 0x -> 10;
	QString qstrTime(sendTo_realTime_time);
	qint64 iTime = qstrTime.toInt(0,16);
	testDate.setTime_t(iTime);
	string strTemp = testDate.toString("[hh:mm:ss]:").toStdString();
	memcpy(&m_send_to_realTime_dialog[strlen(m_send_to_realTime_dialog)], strTemp.c_str(), sizeof(strTemp));
	
	//将时间后面部分复制
	//memcpy(&m_send_to_realTime_dialog[strlen(m_send_to_realTime_dialog)], &m_recvBuf[14], strlen(m_recvBuf) - 13);	//不减14是将多一位的'\0'也复制
	int copy_length = strlen(m_recvBuf);
	if (copy_length > 256){
		copy_length = 255;//总拷贝长度
	}
	copy_length -= 14;	//13为到时间后‘:’ 为止的字符长度
	memcpy(&m_send_to_realTime_dialog[strlen(m_send_to_realTime_dialog)], &m_recvBuf[14], copy_length);	//最后一位结束符
	m_send_to_realTime_dialog[copy_length + 14] = '\0';//接收字符串与缓冲区字符串长度不同，需要增加结束符	

	emit signalSendMessageToRealTimeDia(m_send_to_realTime_dialog, send_level);
}
