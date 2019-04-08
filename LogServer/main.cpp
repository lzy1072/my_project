#include "logmanagersystem.h"
#include <QtGui/QApplication>
#include <io.h>
#include <QTextCodec>
int main(int argc, char *argv[])
{
	//��ֹ�ظ�����win32
	HWND hProgramWnd = ::FindWindow(NULL,L"LogServer");
	HANDLE h_mutex = CreateMutexA(NULL, FALSE, "PowerCncLog");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(h_mutex);
		//��������Ѿ����ڲ�����������
		if (hProgramWnd)
		{
			typedef void (WINAPI *PSWITCHTOTHISWINDOW) (HWND,BOOL);
			PSWITCHTOTHISWINDOW SwitchToThisWindow;
			HMODULE hUser32=GetModuleHandleA("user32");
			SwitchToThisWindow=(PSWITCHTOTHISWINDOW)GetProcAddress(hUser32,"SwitchToThisWindow");
			//���ھͿ���ʹ�ô˺�����
			SwitchToThisWindow(hProgramWnd,TRUE);
		}
		return FALSE;
	}

	////���������������  ----ͨ��   ʹ�ñ��������ֿ�
	//QTextCodec::setCodecForTr(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));  
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));   
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
	//setlocale(LC_ALL,"Chinese-simplified");//�������Ļ���

	QApplication a(argc, argv);

	QString qstr_current_path = QDir::currentPath();
	string sPath = qstr_current_path.toStdString();

	int nDbInit = CSafeConnect::Init((char*)(sPath+"\\DbCfgSqlite.cfg").c_str());
	{
		CSafeConnect db;
		db.QueryDatabase\
			("CREATE TABLE IF NOT EXISTS TXLog ( aisle CHAR(4) , level CHAR(4) , datetime DATETIME , mms CHAR(8), thread CHAR(8) , file CHAR(50) , details CHAR(255))");
		// db.QueryDatabase("vacuum");	//ѹ��
	}

	LogManagerSystem w;
	w.startUdpThread();
	w.show();
	return a.exec();
}
