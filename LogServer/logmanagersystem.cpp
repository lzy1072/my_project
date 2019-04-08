#include "logmanagersystem.h"
#include <QMenu>

//缩减：设置菜单向上弹起
#define SET_MENU_POPUP_DIRECTION_UP(menu, button)  do { \
QPoint pos;	\
pos.setX(0);	\
pos.setY(-menu->sizeHint().height());	\
menu->exec(ui.button->mapToGlobal(pos));	\
} while (0)

//缩减：设置跳转日期的text，并且插入action  //每次打印当前的上一天
#define SET_MENU_GOTO_SOMEDAY_TEXT_AND_INSERT_ACTION(firstAction, nextAction)  do {\
search_someDay = search_someDay.addDays(-1);	\
current_date = search_someDay.toString("MM-dd");	\
ui.nextAction->setText(current_date);	\
goto_someday_menu.insertAction(ui.firstAction, ui.nextAction);	\
} while (0)

static int g_every_page_showLog_count = 15;

LogManagerSystem::LogManagerSystem(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	//SetWindowTextA(winId(), "LogServer");
	initUi();
	initMemeber();

	getDbPathToCStr();
	setTableStyle();
	mUpDate();

	m_timer = new QTimer(this);	//定时刷新定时器
	m_timer->start(1000);
	m_nLastTickUpt = GetTickCount();

	initConnect();
	resetGotoSomedays(1);
}

LogManagerSystem::~LogManagerSystem()
{
	delete m_UdpLogServer;

	delete m_chDbConnect;

	m_realTime_dialog->close();
	delete m_realTime_dialog;

	delete m_timer;

	delete m_menu;	//会自动释放里面的action

	delete m_days_menu;
}

void LogManagerSystem::mUpDate()
{
	CRzxCritical cri(m_cri);
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
	CSafeConnect db;
	//m_arrSql = "select rowid , * , count(rowid)  from TXLog where '";//strSql = "select rowid , * , count(rowid)  from TXLog where '";
	m_arrSql = "select count(rowid) from TXLog where '";
	m_arrSql += m_arrSqlTime;//	m_arrSqlTime = "yyyy-MM-dd hh:mm:ss ' <  datetime ";
	m_arrSql += m_arrSqlLevel;
	CSafeSet cSetCount = db.QueryDatabase(m_arrSql.data());	//数据总数设置

	//CSafeSet cSetCount = db.QueryDatabase("SELECT TOP 1 * FROM user order by id desc;");	//数据总数设置
	if(cSetCount.isEmpty())		//空表跳过，代码的鲁棒性
	{	return;		}
	string strCount;
	cSetCount.GetNext();
	strCount = cSetCount.GetString(1);
	m_DBTableCount = atoi(strCount.c_str());		//获得总数
	m_allPage = getPage();
	ui.spinBox_Page->setRange(1,m_allPage);
	ui.label_Page->setText(QString::fromLocal8Bit("共") + QString::number(m_allPage) + QString::fromLocal8Bit("页"));

	//查询语句设定
	m_arrSql = "select rowid , * from TXLog where '";//strSql = "select rowid , * from TXLog where '";	//存储sql语句
	m_arrSql += m_arrSqlTime;//	m_arrSqlTime = " yyyy-MM-dd hh:mm:ss ' <  datetime ";		
	m_arrSql += m_arrSqlLevel;//m_arrSqlLevel = " and level != 1 ";
	m_arrSql += " ORDER BY rowid limit ";
	QByteArray arrTemp = "";	
	int iSearch = m_DBTableCount - (g_every_page_showLog_count * m_currentPage);		//从iSearch开始查询
	arrTemp = QByteArray::number(iSearch, 10);//strTemp = QString::number(iSearch).toStdString();
	if (iSearch < 0){
		arrTemp = " 0 ";
		iSearch += g_every_page_showLog_count;
	}
	else{	
		iSearch = g_every_page_showLog_count;	
	}
	m_arrSql += arrTemp;							//select * from TXLog  limit iSearch
	m_arrSql += " , ";							//select * from TXLog  limit iSearch , 
	//查找iSearch -> g_every_page_count条
	arrTemp = QByteArray::number(iSearch, 10);
	m_arrSql += arrTemp;							//select * from TXLog  limit iSearch , iSearch+19
	sqlSearchShow(m_arrSql.data());
}

void LogManagerSystem::setTableStyle()
{
	ui.tableWidget->setColumnCount(m_col);
	if (m_debug){
		ui.tableWidget->setHorizontalHeaderLabels\
			(QStringList()<<QString::fromLocal8Bit("序号")\
			<<QString::fromLocal8Bit("通道")\
			<<QString::fromLocal8Bit("级别")\
			<<QString::fromLocal8Bit("时间")\
			<<QString::fromLocal8Bit("线程ID")\
			<<QString::fromLocal8Bit("文件位置")\
			<<QString::fromLocal8Bit("描述"));
		//设置列大小ui.tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);//固定
		ui.tableWidget->setColumnWidth(0,50);
		ui.tableWidget->setColumnWidth(1,35);
		ui.tableWidget->setColumnWidth(2,35);
		ui.tableWidget->setColumnWidth(3,140);
		ui.tableWidget->setColumnWidth(4,45);
		ui.tableWidget->setColumnWidth(5,100);
		ui.tableWidget->setColumnWidth(6,400);
		//ui.tableWidget->horizontalHeader()->setResizeMode(5, QHeaderView::ResizeToContents);//自适应
	}
	else{
		ui.tableWidget->setHorizontalHeaderLabels\
			(QStringList()<<QString::fromLocal8Bit("序号")\
			<<QString::fromLocal8Bit("通道")\
			<<QString::fromLocal8Bit("级别")\
			<<QString::fromLocal8Bit("时间")\
			<<QString::fromLocal8Bit("描述"));
		//设置列大小
		ui.tableWidget->setColumnWidth(0,50);
		ui.tableWidget->setColumnWidth(1,35);
		ui.tableWidget->setColumnWidth(2,35);
		ui.tableWidget->setColumnWidth(3,140);
		ui.tableWidget->setColumnWidth(4,400);

	}
	//ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
	ui.tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
}

void LogManagerSystem::slotButtonClear()
{
	stoptimer();
	m_timePoint = QDateTime::currentDateTime();
	m_arrClearTimePoint = " and '";
	m_arrClearTimePoint += m_timePoint.toString("yyyy-MM-dd hh:mm:ss").toLatin1();	//设置查询的时间点
	m_arrClearTimePoint += "' <  datetime ";	//"yyyy-MM-dd hh:mm:ss' <  datetime ";
	m_arrSqlTime += m_arrClearTimePoint;	//当前天数为1时需要直接拼接
	
	//ui.comboBox_Date->setCurrentIndex(0);
	slotSelectOneDay();

	mUpDate();
}

void LogManagerSystem::slotSelectDateChange(int index)
{
	stoptimer();
	//switch (index) //实现下面功能
	//{
	//case 0:
	//	m_date = -1;
	//	break;
	//case 1:
	//	m_date = -3;
	//	break;
	//case 2:
	//	m_date = -5;
	//	break;
	//}
	m_date = ((index<<1) + 1) * (-1);

	m_timePoint = QDateTime::currentDateTime();
	m_arrSqlTime = "";
	m_arrSqlTime = m_timePoint.addDays(m_date).toString("yyyy-MM-dd hh:mm:ss").toLatin1();	//设置查询的时间点
	m_arrSqlTime += "' <  datetime ";
	if (index == 0)
	{
		m_arrSqlTime += m_arrClearTimePoint;
	}

	ui.spinBox_Page->setValue(1);	//不在第一页时，先将当前页置为1，跳过去
	mUpDate();	//当前为第一个则直接刷新
	resetGotoSomedays((m_date * (-1))<(m_delete_days) ? (m_date * (-1)):(m_delete_days));
}

void LogManagerSystem::slotUpDate()
{
	int nTick = GetTickCount();
	if(nTick-m_nLastTickUpt<800) return;
	ui.spinBox_Page->setValue(1);	//不在第一页时，先将当前页置为1，跳过去
	mUpDate();	//在第一页时刷新
	m_nLastTickUpt = GetTickCount();
}

int LogManagerSystem::getPage()
{
	if (0 == m_DBTableCount)
		return 1;
	int result = m_DBTableCount / g_every_page_showLog_count;
	return ((m_DBTableCount % g_every_page_showLog_count) > 0)? (++result) : result;
}

void LogManagerSystem::slotUpPage()
{
	stoptimer();
	ui.spinBox_Page->stepDown();
}

void LogManagerSystem::slotDownPage()
{
	stoptimer();
	ui.spinBox_Page->stepUp();
}

void LogManagerSystem::slotGotoPage(int page)
{
	m_currentPage = page;
	mUpDate();
}


void LogManagerSystem::slotCheckBoxDebug(int state)
{
	stoptimer();

	//作用如下
	//if (state == Qt::Checked)
	//{
	//	m_col = 7;
	//	m_debug = true;
	//}
	//else
	//{
	//	m_col = 5;
	//	m_debug = false;
	//}
	m_debug = state & 2;
	m_col = state + 5;

	setTableStyle();
	mUpDate();
}

void LogManagerSystem::sqlLevelChange()
{
	m_currentPage = 1;	
	m_arrSqlLevel = "";
	/*if (!m_Warnning)
	{
		m_arrSqlLevel += " and level != 1 ";
	}
	if (!m_Error)
	{
		m_arrSqlLevel += " and level != 2 ";
	}
	if (!m_system)
	{
		m_arrSqlLevel += " and level != 3 ";
	}*///实现如上功能
	m_Error ? 0:(m_arrSqlLevel += " and level > '3' ");
	m_Warnning ? 0:(m_arrSqlLevel += " and level != '4' ");
	m_system ? 0:(m_arrSqlLevel += " and level < '5' ");
}

void LogManagerSystem::getDbPathToCStr()
{
	QString qexeFullPath = QDir::currentPath();
	qexeFullPath += "/Debug";
	std::string sPath = qexeFullPath.toStdString();
	sPath += "\\DbCfgSqlite.cfg";
	char* tempCh = (char*)sPath.c_str();
	int tempLength = strlen(tempCh);

	m_chDbConnect = new char[tempLength+1];
	if (m_chDbConnect == NULL){
		m_chDbConnect = new char[tempLength+1];
	}
	memcpy(m_chDbConnect,tempCh,tempLength);
	m_chDbConnect[tempLength] = '\0';
	//析构中delete、置空m_chDbConnect
}

void LogManagerSystem::startUdpThread()
{
	emit sigStartThread();		//通知子线程开启
}

void LogManagerSystem::sqlSearchShow(const char* sql)
{
	CSafeConnect db;
	CSafeSet cSet = db.QueryDatabase(sql);	//strSql = "select rowid , * from TXLog order by rowid";

	string level;		//不使用中间变量，直接给QTableWidgetItem
	QByteArray arrIconPath;
	while(cSet.GetNext())	//1是rowid
	{
		level = cSet.GetString(3);	//魔鬼数字代表column
		arrIconPath = ":/LogManagerSystem/res/";
		//1 2 3都用致命， 4用报警， 5开始常规色
		if (level < "4")
		{	arrIconPath += "1";	}
		else if("4" == level)
		{	arrIconPath += "2";	}
		else
		{	arrIconPath += "3";	}//datetime = cSet.GetString(4);	//跳过5(毫秒)
		arrIconPath += ".png";	
		ui.tableWidget->insertRow(0);
		ui.tableWidget->setItem(0, 0, new QTableWidgetItem(cSet.GetString(1)));
		ui.tableWidget->setItem(0, 1, new QTableWidgetItem(cSet.GetString(2)));
		ui.tableWidget->setItem(0, 2, new QTableWidgetItem(QIcon(arrIconPath),0));
		ui.tableWidget->setItem(0, 3, new QTableWidgetItem(cSet.GetString(4)));
		if (m_debug){
			ui.tableWidget->setItem(0, 4, new QTableWidgetItem(cSet.GetString(6)));
			ui.tableWidget->setItem(0, 5, new QTableWidgetItem(cSet.GetString(7)));
		}
		ui.tableWidget->setItem(0, m_col - 1, new QTableWidgetItem(QString::fromLocal8Bit(cSet.GetString(8))));
	}
}

void LogManagerSystem::slotHeadPage()
{
	stoptimer();
	ui.spinBox_Page->setValue(1);	//首页
}

void LogManagerSystem::slotTailPage()
{
	stoptimer();
	ui.spinBox_Page->setValue(m_allPage);	//尾页
}

void LogManagerSystem::slotSpinboxResetSaveDay( int value )
{
	m_delete_days = value;
	stoptimer();

	m_UdpLogServer->m_stop = false;
	emit signalResetSaveDay(value);
	
	//查询天数为all才响应，value（3,4,5）
	if (m_date  == -5)	{
		resetGotoSomedays((value)<(m_date * (-1)) ? (value):(m_date * (-1)));
	}
}

void LogManagerSystem::resetGotoSomedays( int days)
{
	m_goto_days_count = days;
}

void LogManagerSystem::slotSearchGotoSomeday( int index)//（0,1,2,3,4）-》（1,2,3,4,5）
{
	stoptimer();

	m_timePoint = QDateTime::currentDateTime();
	m_arrSqlTime = "";
	m_arrSqlTime = m_timePoint.addDays((-1) * (index - 1)).toString("yyyy-MM-dd").toLatin1();	//设置查询的时间点
	m_arrSqlTime += "' =  date(datetime) ";	//date('now', '-1 days') = date(datetime)

	ui.spinBox_Page->setValue(1);	//不在第一页时，先将当前页置为1，跳过去
	mUpDate();	//当前为第一个则直接刷新
}

void LogManagerSystem::onOffRealTimeDialog(bool state)
{
	bool real_time_on_off_flag = state;	//初始化一次，下次

	if (real_time_on_off_flag){
		m_realTime_dialog->move(this->pos().x() + 215,this->pos().y()+180);
		m_realTime_dialog->show();
		stoptimer();
		ui.pushButton_autoUpDate->setCheckable(false);
	} 
	else{
		m_realTime_dialog->close();
		ui.pushButton_autoUpDate->setCheckable(true);

		//打开定时刷新
		ui.pushButton_autoUpDate->setChecked(true);	//设置按钮
		emit signalStartAutoUpDate();
	}
}
void LogManagerSystem::slotOnRealtimeDialog()
{
	stoptimer();
	onOffRealTimeDialog(true);
}
void LogManagerSystem::slotSetCloseRealTimeDialog()
{
	onOffRealTimeDialog(false);
}

void LogManagerSystem::startTimer()
{
	m_timer->start();
}

void LogManagerSystem::stoptimer()
{
	m_timer->stop();
	ui.pushButton_autoUpDate->setChecked(false);
}

void LogManagerSystem::slotONAutoUpDate()
{
	if (ui.pushButton_autoUpDate->isChecked()){
		//将时间语句改为总查询天数
		m_timePoint = QDateTime::currentDateTime();
		m_arrSqlTime = "";
		m_arrSqlTime = m_timePoint.addDays(m_date).toString("yyyy-MM-dd hh:mm:ss").toLatin1();	//设置查询的时间点
		m_arrSqlTime += "' <  datetime ";
		if (m_date == -1){	//接收点击清除后的语句
			m_arrSqlTime += m_arrClearTimePoint;
		}

		startTimer();
	}
	else{
		stoptimer();
	}
}

void LogManagerSystem::slotOpenSettingDialog()
{
	stoptimer();
	m_setting_dialog->exec();
}

void LogManagerSystem::moveEvent( QMoveEvent * event )
{
	m_realTime_dialog->getRegion(this->pos().x() + 9, this->pos().y() + 9,\
		this->pos().x() + 211, this->pos().y() + 170);
	static int s_x = 0;
	static int s_y = 0;
	static bool s_postion_flag = true;
	if (s_postion_flag == true){
		QPoint GlobalPoint(this->mapToGlobal(QPoint(0, 0)));//获取控件在窗体中的坐标
		s_x = GlobalPoint.x();
		s_y = GlobalPoint.y();
		s_postion_flag = false;
	}
}

void LogManagerSystem::slotSetStackWidgetFist( int index /*= 0*/ )
{
	ui.stackedWidget->setCurrentIndex(index);
}

void LogManagerSystem::slotSetStackWidgetNext( int index /*= 1*/ )
{
	ui.stackedWidget->setCurrentIndex(index);
}

void LogManagerSystem::keyPressEvent( QKeyEvent * event )
{
	if (event->key() == Qt::Key_Escape){
		slotPushButtonMin();
	}
	else if (event->key() == Qt::Key_PageUp){
		slotUpPage();
	}
	else if (event->key() == Qt::Key_PageDown){
		slotDownPage();
	}
}

void LogManagerSystem::initConnect()
{
	connect(this, SIGNAL(sigStartThread()), m_UdpLogServer, SLOT(slotChileThread()), Qt::QueuedConnection);	//连接启动线程
	connect(ui.pushButton_Clear, SIGNAL(clicked()), this, SLOT(slotButtonClear()));
	connect(ui.pushButton_UpDate, SIGNAL(clicked()), this, SLOT(slotUpDate()));
	connect(m_timer, SIGNAL(timeout()), this, SLOT(slotUpDate()), Qt::DirectConnection);
	connect(ui.pushButton_UpPdge, SIGNAL(clicked()), this, SLOT(slotUpPage()));
	connect(ui.pushButton_firstPage, SIGNAL(clicked()), this, SLOT(slotHeadPage()));		//首尾页
	connect(ui.pushButton_lastPage, SIGNAL(clicked()), this, SLOT(slotTailPage()));
	connect(ui.pushButton_DownPage, SIGNAL(clicked()), this, SLOT(slotDownPage()));
	connect(ui.spinBox_Page, SIGNAL(valueChanged(int)), this,  SLOT(slotGotoPage(int)));
	connect(m_setting_dialog, SIGNAL(signalDebugOnOff(int)), this,  SLOT(slotCheckBoxDebug(int)));
	connect(m_setting_dialog, SIGNAL(signalDeleteDayValue(int)), this, SLOT(slotSpinboxResetSaveDay(int)));	//重设删除天数
	connect(this, SIGNAL(signalResetSaveDay(int)), m_UdpLogServer, SLOT(slotReSetSQLDelete(int)), Qt::QueuedConnection);//等待当前函数执行完毕，再调用
	connect(ui.pushButton_realTime, SIGNAL(clicked()), this,  SLOT(slotOnRealtimeDialog()));	//实时更改1
	connect(m_UdpLogServer, SIGNAL(signalSendMessageToRealTimeDia(char*, int)), m_realTime_dialog, SLOT(slotGetAndShowRealtimeMessage(char*, int)));
	connect(m_realTime_dialog, SIGNAL(m_sianal_realTime_dialog_isClose()), this, SLOT(slotSetCloseRealTimeDialog()));	//实时更改2
	connect(m_realTime_dialog, SIGNAL(rejected()), this, SLOT(slotSetCloseRealTimeDialog()));	//实时更改3
	connect(ui.pushButton_set, SIGNAL(clicked()), this, SLOT(slotOpenSettingDialog()));
	connect(ui.pushButton_autoUpDate, SIGNAL(clicked()), this, SLOT(slotONAutoUpDate()));
	connect(this, SIGNAL(signalStartAutoUpDate()), this, SLOT(slotONAutoUpDate()));

	connect(ui.pushButton_left, SIGNAL(clicked()), this, SLOT(slotSetStackWidgetFist()));	//按钮页翻页
	connect(ui.pushButton_right, SIGNAL(clicked()), this, SLOT(slotSetStackWidgetNext()));
	connect(ui.pushButton_secondRight, SIGNAL(clicked()), this, SLOT(slotSetStackWidgetFist()));
	connect(ui.pushButton_firstLeft, SIGNAL(clicked()), this, SLOT(slotSetStackWidgetNext()));

	connect(ui.pushButton_level, SIGNAL(clicked()), this, SLOT(slotShowLevelMenu()));	//级别设置
	connect(m_level_error, SIGNAL(triggered()), this, SLOT(slotOnErrorMenu()));	//级别变更
	connect(m_level_warnning, SIGNAL(triggered()), this, SLOT(slotOnWarnningMenu()));
	connect(m_level_system, SIGNAL(triggered()), this, SLOT(slotOnSystemMenu()));

	connect(ui.pushButton_selectDays, SIGNAL(clicked()), this, SLOT(slotShowSelectDays()));	//天数设置
	connect(ui.action_selectOneDay, SIGNAL(triggered()), this,  SLOT(slotSelectOneDay()));	//选择天数
	connect(ui.action_selectTheDay, SIGNAL(triggered()), this,  SLOT(slotSelectThreeDay()));
	connect(ui.action_sslectFiveDay, SIGNAL(triggered()), this,  SLOT(slotSelectFiveDay()));

	connect(ui.pushButton_gotoSomeDay, SIGNAL(clicked()), this, SLOT(slotShowGotoSomeDays()));	//按日期跳转
	connect(ui.action_gotoDay_now, SIGNAL(triggered()), this,  SLOT(slotGotoNow()));
	connect(ui.action_gotoDay_yestarday, SIGNAL(triggered()), this,  SLOT(slotGotoYesterday()));
	connect(ui.action_gotoDay_two, SIGNAL(triggered()), this,  SLOT(slotGotoTwoDayBefore()));
	connect(ui.action_gotoDay_three, SIGNAL(triggered()), this,  SLOT(slotGotoThreeDayBefore()));
	connect(ui.action_gotoDay_four, SIGNAL(triggered()), this,  SLOT(slotGotoFourDayBefore()));

	connect(ui.pushButton_min, SIGNAL(clicked()), this, SLOT(slotPushButtonMin()));	//最小化
}

void LogManagerSystem::initUi()
{
	this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
	//去除边框
	this->setWindowOpacity(1);    
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowTitle("LogServer");
	//this->setAttribute(Qt::WA_TranslucentBackground);
	QHeaderView* headerView = ui.tableWidget->horizontalHeader();	//表头左对齐
	headerView->setDefaultAlignment(Qt::AlignLeft);
	ui.tableWidget->setAlternatingRowColors(true);					//隔行变色
}

void LogManagerSystem::initMemeber()
{
	m_UdpLogServer = new UDPLogServer(m_cri);
	m_realTime_dialog = new RealTimeDialog(this);
	m_setting_dialog = new SettingModalDialog(this);

	m_Warnning = true;		//③
	m_Error = true;		//③
	m_system = true;		//③
	m_debug = false;
	m_col = 5;		//表格列数设置
	m_date = -1;	//⑤查询天数
	m_DBTableCount = 0;
	m_currentPage = 1;
	m_arrSql = "";
	m_allPage = 0;
	m_arrSqlLevel = " ";
	m_delete_days = 5;
	m_goto_days_count = 1;

	m_timePoint = QDateTime::currentDateTime();			//首次打开使用，获得打开软件时间
	m_arrSqlTime = "";
	m_arrSqlTime = m_timePoint.addDays(m_date).toString("yyyy-MM-dd hh:mm:ss").toLatin1();	//设置查询的时间点
	m_arrSqlTime += "' <  datetime ";

	m_menu = new QMenu(this);	//级别菜单
	m_level_error = new QAction(m_menu);
	m_level_warnning = new QAction(m_menu);
	m_level_system = new QAction(m_menu);
	m_level_error->setCheckable(true);	//勾选
	m_level_warnning->setCheckable(true);
	m_level_system->setCheckable(true);
	m_level_error->setChecked(m_Error);
	m_level_warnning->setChecked(m_Warnning);
	m_level_system->setChecked(m_system);
	m_level_error->setText(QString::fromLocal8Bit("错误"));
	m_level_warnning->setText(QString::fromLocal8Bit("警告"));
	m_level_system->setText(QString::fromLocal8Bit("系统"));
	m_menu->addAction(m_level_system);
	m_menu->addAction(m_level_warnning);
	m_menu->addAction(m_level_error);

	m_days_menu = new QMenu(this);
	m_days_menu->addAction(ui.action_sslectFiveDay);
	m_days_menu->addAction(ui.action_selectTheDay);
	m_days_menu->addAction(ui.action_selectOneDay);
	ui.action_selectOneDay->setChecked(true);
}

void LogManagerSystem::slotShowLevelMenu()
{
	SET_MENU_POPUP_DIRECTION_UP(m_menu, pushButton_level);
}

void LogManagerSystem::slotOnErrorMenu()
{
	stoptimer();
	m_Error = !m_Error;
	m_level_error->setChecked(m_Error);
	if (m_Error == true){
		ui.label_error->setStyleSheet("background-color: rgb(255, 0, 0)");
	}
	else{
		ui.label_error->setStyleSheet("background-color: rgb(255, 255, 255)");
	}

	sqlLevelChange();	//不在第一页时，先将当前页置为1，跳过去
	ui.spinBox_Page->setValue(1);	
	mUpDate();	//当前为第一个则直接刷新
}

void LogManagerSystem::slotOnWarnningMenu()
{
	stoptimer();

	//state ==2(Qt::Checked)置为真，否则为假(如下功能)
	m_Warnning = !m_Warnning;
	m_level_warnning->setChecked(m_Warnning);
	if (m_Warnning == true){
		ui.label_warn->setStyleSheet("background-color: rgb(255, 255, 0);");
	}
	else{
		ui.label_warn->setStyleSheet("background-color: rgb(255, 255, 255);");
	}
	sqlLevelChange();
	ui.spinBox_Page->setValue(1);	//不在第一页时，先将当前页置为1，跳过去
	mUpDate();	//当前为第一个则直接刷新
}

void LogManagerSystem::slotOnSystemMenu()
{
	stoptimer();

	m_system = !m_system;
	m_level_system->setChecked(m_system);
	if (m_system == true){
		ui.label_system->setStyleSheet("background-color: rgb(85, 170, 255);");
	}
	else{
		ui.label_system->setStyleSheet("background-color: rgb(255, 255, 255);");
	}
	sqlLevelChange();	//不在第一页时，先将当前页置为1，跳过去
	ui.spinBox_Page->setValue(1);	
	mUpDate();	//当前为第一个则直接刷新
}

void LogManagerSystem::slotPushButtonMin()
{
	this->showMinimized();
}

void LogManagerSystem::slotShowSelectDays()
{
	SET_MENU_POPUP_DIRECTION_UP(m_days_menu, pushButton_selectDays);
}

void LogManagerSystem::slotSelectOneDay()
{
	slotSelectDateChange(0);
	resetSelectDaysOnOffCheck(0);
}

void LogManagerSystem::slotSelectThreeDay()
{
	slotSelectDateChange(1);
	resetSelectDaysOnOffCheck(1);
}

void LogManagerSystem::slotSelectFiveDay()
{
	slotSelectDateChange(2);
	resetSelectDaysOnOffCheck(2);
}

void LogManagerSystem::slotShowGotoSomeDays()
{
	QDate search_someDay = QDate::currentDate();
	QString current_date;
	QMenu goto_someday_menu;
	goto_someday_menu.addAction(ui.action_gotoDay_now);
	//goto_someday_menu  2,3,4,5
	if (m_goto_days_count > 1){
		SET_MENU_GOTO_SOMEDAY_TEXT_AND_INSERT_ACTION(action_gotoDay_now, action_gotoDay_yestarday);
		if (m_goto_days_count > 2){		
			SET_MENU_GOTO_SOMEDAY_TEXT_AND_INSERT_ACTION(action_gotoDay_yestarday, action_gotoDay_two);
			if (m_goto_days_count > 3){
				SET_MENU_GOTO_SOMEDAY_TEXT_AND_INSERT_ACTION(action_gotoDay_two, action_gotoDay_three);
			}
			if (m_goto_days_count > 4){
				SET_MENU_GOTO_SOMEDAY_TEXT_AND_INSERT_ACTION(action_gotoDay_three, action_gotoDay_four);
			}
		}
	}
	QPoint pos;
	pos.setX(0);
	pos.setY(-goto_someday_menu.sizeHint().height());
	goto_someday_menu.exec(ui.pushButton_gotoSomeDay->mapToGlobal(pos));
}

void LogManagerSystem::resetSelectDaysOnOffCheck(int index)
{
	//选中的天数勾选，未选中不勾选
	ui.action_selectOneDay->setChecked(index == 0 ? true:false);
	ui.action_selectTheDay->setChecked(index == 1 ? true:false);
	ui.action_sslectFiveDay->setChecked(index == 2 ? true:false);
}

void LogManagerSystem::resetGotoSomeDayOnOffCheck( int index )
{
	//将被勾选的设置为选中，否则不选中
	ui.action_gotoDay_now->setChecked(index == 0 ? true:false);
	ui.action_gotoDay_yestarday->setChecked(index == 1 ? true:false);
	ui.action_gotoDay_two->setChecked(index == 2 ? true:false);
	ui.action_gotoDay_three->setChecked(index == 3 ? true:false);
	ui.action_gotoDay_four->setChecked(index == 4 ? true:false);
}

void LogManagerSystem::slotGotoNow()
{
	slotSearchGotoSomeday(1);
	resetGotoSomeDayOnOffCheck(0);	
}

void LogManagerSystem::slotGotoYesterday()
{
	slotSearchGotoSomeday(2);
	resetGotoSomeDayOnOffCheck(1);
}

void LogManagerSystem::slotGotoTwoDayBefore()
{
	slotSearchGotoSomeday(3);
	resetGotoSomeDayOnOffCheck(2);
}

void LogManagerSystem::slotGotoThreeDayBefore()
{
	slotSearchGotoSomeday(4);
	resetGotoSomeDayOnOffCheck(3);
}

void LogManagerSystem::slotGotoFourDayBefore()
{
	slotSearchGotoSomeday(5);
	resetGotoSomeDayOnOffCheck(4);
}