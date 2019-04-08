#ifndef LOGMANAGERSYSTEM_H
#define LOGMANAGERSYSTEM_H

#include <QtGui/QMainWindow>
#include "ui_logmanagersystem.h"
#include <QString>
#include <string.h>
#include <stdio.h>
#include <QDir>
#include <QTimer>
#include "udplogserver.h"
#include "real_time_dialog.h"
#include "settingmodaldialog.h"
#include "Critical.h"
class LogManagerSystem : public QMainWindow
{
	Q_OBJECT

public:
	LogManagerSystem(QWidget *parent = 0, Qt::WFlags flags = 0);
	~LogManagerSystem();

private:
	void mUpDate();		//������ã���ѯ���ݣ�ˢ�����������
	void setTableStyle();	//�ı�����ʽ
	int getPage();				//����������������ҳ��,ÿҳĬ��20���Ӵ˺����޸�
	void sqlLevelChange();		//����sql and level �ı�
	void sqlSearchShow(const char* sql);			//����sql��ѯ����ʾ
	void resetGotoSomedays(int);		//���ÿ���ת���������鿴ĳһ�죩
	void startTimer();	//�����رն�ʱ����ͬʱ���ð�ť��״̬
	void stoptimer();
	void initConnect();	//�����źŲ�
	void initUi();
	void initMemeber();
	void onOffRealTimeDialog(bool state);		//�������ر�ʵʱ�Ի���
	void resetSelectDaysOnOffCheck(int);	
	void resetGotoSomeDayOnOffCheck(int);
public:
	void getDbPathToCStr();		//��ȡ���ݿ�·��
	void startUdpThread();		//�������߳�
protected:
	virtual void moveEvent ( QMoveEvent * event );
	virtual void keyPressEvent( QKeyEvent * event );
private slots:
	void slotButtonClear();		//������ܣ����ʱ��¼ʱ��㣬����ѯʱ������Ϊ���ʱ�䣬����ѡ�������ı�ʱ���
	void slotSelectDateChange(int);
	void slotUpDate();
	void slotUpPage();
	void slotDownPage();
	void slotGotoPage(int);
	void slotHeadPage();
	void slotTailPage();
	void slotCheckBoxDebug(int state);
	void slotSpinboxResetSaveDay(int);	//�ı����߳���������������ɾ�����
	void slotSearchGotoSomeday(int);		//��תĳһ�죨index��0,1,2,3,4��
	void slotOnRealtimeDialog();
	void slotSetCloseRealTimeDialog();	//����ʵʱ�Ի���ر��¼�
	void slotOpenSettingDialog();	//�����öԻ���
	void slotSetStackWidgetFist(int index = 0);	//����StackWidget�ĵ�ǰҳ
	void slotSetStackWidgetNext(int index = 1);
	void slotONAutoUpDate();
	void slotShowLevelMenu();	//����˵�

	void slotShowSelectDays();	//��ѯ�����˵�
	void slotSelectOneDay();
	void slotSelectThreeDay();
	void slotSelectFiveDay();

	void slotShowGotoSomeDays();	//��������ת�˵�
	void slotGotoNow();
	void slotGotoYesterday();
	void slotGotoTwoDayBefore();
	void slotGotoThreeDayBefore();
	void slotGotoFourDayBefore();

	void slotOnErrorMenu();
	void slotOnWarnningMenu();
	void slotOnSystemMenu();
	void slotPushButtonMin();	//��С����ť
signals:
	void sigStartThread();		//���߳̿����ź�
	void signalComboBoxToClearTime(int);	//������ -�� ��combobox�����ź� -�� ʵ���������  �������� ���ʱ���֮ǰ�����ݲ���ѯ��
	void signalResetSaveDay(int);		//���͸����̣߳�����ɾ�����
	void signalStartAutoUpDate();		//������ʱˢ�µ��ź�
private:
	//��ѯ��־����
	bool m_Warnning;		//��
	bool m_Error;		//��
	bool m_system;		//��
	bool m_debug;		//
	int m_col;			//table����
	int m_DBTableCount;	//���ݿ���������
	int m_date;	//�ݲ�ѯ����
	int m_currentPage;	//��ǰҳ��
	int m_allPage;		//��ҳ��
	int m_delete_days;	//���öԻ����з���ɾ������
	QDateTime m_timePoint;	//��ѯʱ�ָ���ʱ���
	QByteArray m_arrSql;		//sql��䱣��
	QByteArray m_arrSqlLevel;	//and level�Ķ����������6��if
	QByteArray m_arrSqlTime;	//SQLʱ�䴦�����
	QByteArray m_arrClearTimePoint;	//������ʱ��¼��ʱ��� ��������
	char* m_chDbConnect;				//�洢���ݿ�·��
	UDPLogServer* m_UdpLogServer;	//����udp�������߳�
	RealTimeDialog* m_realTime_dialog;	//ʵʱ����
	QTimer* m_timer;	//��ʱˢ�¶�ʱ��
	SettingModalDialog* m_setting_dialog;	//���öԻ���ģ̬
	int m_nLastTickUpt;
	CRzxCriticalSection m_cri;
	Ui::LogManagerSystemClass ui;

	QMenu * m_menu;
	QAction *m_level_error;
	QAction *m_level_warnning;
	QAction *m_level_system;

	QMenu* m_days_menu;

	int m_goto_days_count;
};

#endif // LOGMANAGERSYSTEM_H
