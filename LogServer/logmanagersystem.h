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
	void mUpDate();		//获得设置，查询数据，刷新输出到界面
	void setTableStyle();	//改变表格样式
	int getPage();				//用总数据条数计算页数,每页默认20，从此函数修改
	void sqlLevelChange();		//处理sql and level 改变
	void sqlSearchShow(const char* sql);			//单纯sql查询并显示
	void resetGotoSomedays(int);		//设置可跳转的天数（查看某一天）
	void startTimer();	//开启关闭定时器，同时设置按钮的状态
	void stoptimer();
	void initConnect();	//连接信号槽
	void initUi();
	void initMemeber();
	void onOffRealTimeDialog(bool state);		//呼出及关闭实时对话框
	void resetSelectDaysOnOffCheck(int);	
	void resetGotoSomeDayOnOffCheck(int);
public:
	void getDbPathToCStr();		//获取数据库路径
	void startUdpThread();		//开启子线程
protected:
	virtual void moveEvent ( QMoveEvent * event );
	virtual void keyPressEvent( QKeyEvent * event );
private slots:
	void slotButtonClear();		//清除功能：点击时记录时间点，将查询时间重设为这个时间，重新选择天数改变时间点
	void slotSelectDateChange(int);
	void slotUpDate();
	void slotUpPage();
	void slotDownPage();
	void slotGotoPage(int);
	void slotHeadPage();
	void slotTailPage();
	void slotCheckBoxDebug(int state);
	void slotSpinboxResetSaveDay(int);	//改变子线程阻塞变量，重设删除语句
	void slotSearchGotoSomeday(int);		//跳转某一天（index：0,1,2,3,4）
	void slotOnRealtimeDialog();
	void slotSetCloseRealTimeDialog();	//接收实时对话框关闭事件
	void slotOpenSettingDialog();	//打开设置对话框
	void slotSetStackWidgetFist(int index = 0);	//设置StackWidget的当前页
	void slotSetStackWidgetNext(int index = 1);
	void slotONAutoUpDate();
	void slotShowLevelMenu();	//级别菜单

	void slotShowSelectDays();	//查询天数菜单
	void slotSelectOneDay();
	void slotSelectThreeDay();
	void slotSelectFiveDay();

	void slotShowGotoSomeDays();	//按日期跳转菜单
	void slotGotoNow();
	void slotGotoYesterday();
	void slotGotoTwoDayBefore();
	void slotGotoThreeDayBefore();
	void slotGotoFourDayBefore();

	void slotOnErrorMenu();
	void slotOnWarnningMenu();
	void slotOnSystemMenu();
	void slotPushButtonMin();	//最小化按钮
signals:
	void sigStartThread();		//子线程开启信号
	void signalComboBoxToClearTime(int);	//点击清除 -》 给combobox发射信号 -》 实现清除功能  （今天内 点击时间点之前的数据不查询）
	void signalResetSaveDay(int);		//发送给子线程，重设删除语句
	void signalStartAutoUpDate();		//启动定时刷新的信号
private:
	//查询日志类型
	bool m_Warnning;		//③
	bool m_Error;		//③
	bool m_system;		//③
	bool m_debug;		//
	int m_col;			//table列数
	int m_DBTableCount;	//数据库中数据量
	int m_date;	//⑤查询天数
	int m_currentPage;	//当前页数
	int m_allPage;		//总页数
	int m_delete_days;	//设置对话框中返回删除天数
	QDateTime m_timePoint;	//查询时分隔得时间点
	QByteArray m_arrSql;		//sql语句保存
	QByteArray m_arrSqlLevel;	//and level的独立运算减少6个if
	QByteArray m_arrSqlTime;	//SQL时间处理语句
	QByteArray m_arrClearTimePoint;	//点击清除时记录的时间点 的组合语句
	char* m_chDbConnect;				//存储数据库路径
	UDPLogServer* m_UdpLogServer;	//处理udp数据子线程
	RealTimeDialog* m_realTime_dialog;	//实时窗口
	QTimer* m_timer;	//定时刷新定时器
	SettingModalDialog* m_setting_dialog;	//设置对话框，模态
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
