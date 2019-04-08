#include "logmanagersystem.h"
#include <QMenu>

//���������ò˵����ϵ���
#define SET_MENU_POPUP_DIRECTION_UP(menu, button)  do { \
QPoint pos;	\
pos.setX(0);	\
pos.setY(-menu->sizeHint().height());	\
menu->exec(ui.button->mapToGlobal(pos));	\
} while (0)

//������������ת���ڵ�text�����Ҳ���action  //ÿ�δ�ӡ��ǰ����һ��
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

	m_timer = new QTimer(this);	//��ʱˢ�¶�ʱ��
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

	delete m_menu;	//���Զ��ͷ������action

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
	CSafeSet cSetCount = db.QueryDatabase(m_arrSql.data());	//������������

	//CSafeSet cSetCount = db.QueryDatabase("SELECT TOP 1 * FROM user order by id desc;");	//������������
	if(cSetCount.isEmpty())		//�ձ������������³����
	{	return;		}
	string strCount;
	cSetCount.GetNext();
	strCount = cSetCount.GetString(1);
	m_DBTableCount = atoi(strCount.c_str());		//�������
	m_allPage = getPage();
	ui.spinBox_Page->setRange(1,m_allPage);
	ui.label_Page->setText(QString::fromLocal8Bit("��") + QString::number(m_allPage) + QString::fromLocal8Bit("ҳ"));

	//��ѯ����趨
	m_arrSql = "select rowid , * from TXLog where '";//strSql = "select rowid , * from TXLog where '";	//�洢sql���
	m_arrSql += m_arrSqlTime;//	m_arrSqlTime = " yyyy-MM-dd hh:mm:ss ' <  datetime ";		
	m_arrSql += m_arrSqlLevel;//m_arrSqlLevel = " and level != 1 ";
	m_arrSql += " ORDER BY rowid limit ";
	QByteArray arrTemp = "";	
	int iSearch = m_DBTableCount - (g_every_page_showLog_count * m_currentPage);		//��iSearch��ʼ��ѯ
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
	//����iSearch -> g_every_page_count��
	arrTemp = QByteArray::number(iSearch, 10);
	m_arrSql += arrTemp;							//select * from TXLog  limit iSearch , iSearch+19
	sqlSearchShow(m_arrSql.data());
}

void LogManagerSystem::setTableStyle()
{
	ui.tableWidget->setColumnCount(m_col);
	if (m_debug){
		ui.tableWidget->setHorizontalHeaderLabels\
			(QStringList()<<QString::fromLocal8Bit("���")\
			<<QString::fromLocal8Bit("ͨ��")\
			<<QString::fromLocal8Bit("����")\
			<<QString::fromLocal8Bit("ʱ��")\
			<<QString::fromLocal8Bit("�߳�ID")\
			<<QString::fromLocal8Bit("�ļ�λ��")\
			<<QString::fromLocal8Bit("����"));
		//�����д�Сui.tableWidget->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);//�̶�
		ui.tableWidget->setColumnWidth(0,50);
		ui.tableWidget->setColumnWidth(1,35);
		ui.tableWidget->setColumnWidth(2,35);
		ui.tableWidget->setColumnWidth(3,140);
		ui.tableWidget->setColumnWidth(4,45);
		ui.tableWidget->setColumnWidth(5,100);
		ui.tableWidget->setColumnWidth(6,400);
		//ui.tableWidget->horizontalHeader()->setResizeMode(5, QHeaderView::ResizeToContents);//����Ӧ
	}
	else{
		ui.tableWidget->setHorizontalHeaderLabels\
			(QStringList()<<QString::fromLocal8Bit("���")\
			<<QString::fromLocal8Bit("ͨ��")\
			<<QString::fromLocal8Bit("����")\
			<<QString::fromLocal8Bit("ʱ��")\
			<<QString::fromLocal8Bit("����"));
		//�����д�С
		ui.tableWidget->setColumnWidth(0,50);
		ui.tableWidget->setColumnWidth(1,35);
		ui.tableWidget->setColumnWidth(2,35);
		ui.tableWidget->setColumnWidth(3,140);
		ui.tableWidget->setColumnWidth(4,400);

	}
	//ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ�еķ�ʽ
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //��ֹ�޸�
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //����Ϊ����ѡ�е���
	ui.tableWidget->verticalHeader()->setVisible(false);   //�����б�ͷ
}

void LogManagerSystem::slotButtonClear()
{
	stoptimer();
	m_timePoint = QDateTime::currentDateTime();
	m_arrClearTimePoint = " and '";
	m_arrClearTimePoint += m_timePoint.toString("yyyy-MM-dd hh:mm:ss").toLatin1();	//���ò�ѯ��ʱ���
	m_arrClearTimePoint += "' <  datetime ";	//"yyyy-MM-dd hh:mm:ss' <  datetime ";
	m_arrSqlTime += m_arrClearTimePoint;	//��ǰ����Ϊ1ʱ��Ҫֱ��ƴ��
	
	//ui.comboBox_Date->setCurrentIndex(0);
	slotSelectOneDay();

	mUpDate();
}

void LogManagerSystem::slotSelectDateChange(int index)
{
	stoptimer();
	//switch (index) //ʵ�����湦��
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
	m_arrSqlTime = m_timePoint.addDays(m_date).toString("yyyy-MM-dd hh:mm:ss").toLatin1();	//���ò�ѯ��ʱ���
	m_arrSqlTime += "' <  datetime ";
	if (index == 0)
	{
		m_arrSqlTime += m_arrClearTimePoint;
	}

	ui.spinBox_Page->setValue(1);	//���ڵ�һҳʱ���Ƚ���ǰҳ��Ϊ1������ȥ
	mUpDate();	//��ǰΪ��һ����ֱ��ˢ��
	resetGotoSomedays((m_date * (-1))<(m_delete_days) ? (m_date * (-1)):(m_delete_days));
}

void LogManagerSystem::slotUpDate()
{
	int nTick = GetTickCount();
	if(nTick-m_nLastTickUpt<800) return;
	ui.spinBox_Page->setValue(1);	//���ڵ�һҳʱ���Ƚ���ǰҳ��Ϊ1������ȥ
	mUpDate();	//�ڵ�һҳʱˢ��
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

	//��������
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
	}*///ʵ�����Ϲ���
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
	//������delete���ÿ�m_chDbConnect
}

void LogManagerSystem::startUdpThread()
{
	emit sigStartThread();		//֪ͨ���߳̿���
}

void LogManagerSystem::sqlSearchShow(const char* sql)
{
	CSafeConnect db;
	CSafeSet cSet = db.QueryDatabase(sql);	//strSql = "select rowid , * from TXLog order by rowid";

	string level;		//��ʹ���м������ֱ�Ӹ�QTableWidgetItem
	QByteArray arrIconPath;
	while(cSet.GetNext())	//1��rowid
	{
		level = cSet.GetString(3);	//ħ�����ִ���column
		arrIconPath = ":/LogManagerSystem/res/";
		//1 2 3���������� 4�ñ����� 5��ʼ����ɫ
		if (level < "4")
		{	arrIconPath += "1";	}
		else if("4" == level)
		{	arrIconPath += "2";	}
		else
		{	arrIconPath += "3";	}//datetime = cSet.GetString(4);	//����5(����)
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
	ui.spinBox_Page->setValue(1);	//��ҳ
}

void LogManagerSystem::slotTailPage()
{
	stoptimer();
	ui.spinBox_Page->setValue(m_allPage);	//βҳ
}

void LogManagerSystem::slotSpinboxResetSaveDay( int value )
{
	m_delete_days = value;
	stoptimer();

	m_UdpLogServer->m_stop = false;
	emit signalResetSaveDay(value);
	
	//��ѯ����Ϊall����Ӧ��value��3,4,5��
	if (m_date  == -5)	{
		resetGotoSomedays((value)<(m_date * (-1)) ? (value):(m_date * (-1)));
	}
}

void LogManagerSystem::resetGotoSomedays( int days)
{
	m_goto_days_count = days;
}

void LogManagerSystem::slotSearchGotoSomeday( int index)//��0,1,2,3,4��-����1,2,3,4,5��
{
	stoptimer();

	m_timePoint = QDateTime::currentDateTime();
	m_arrSqlTime = "";
	m_arrSqlTime = m_timePoint.addDays((-1) * (index - 1)).toString("yyyy-MM-dd").toLatin1();	//���ò�ѯ��ʱ���
	m_arrSqlTime += "' =  date(datetime) ";	//date('now', '-1 days') = date(datetime)

	ui.spinBox_Page->setValue(1);	//���ڵ�һҳʱ���Ƚ���ǰҳ��Ϊ1������ȥ
	mUpDate();	//��ǰΪ��һ����ֱ��ˢ��
}

void LogManagerSystem::onOffRealTimeDialog(bool state)
{
	bool real_time_on_off_flag = state;	//��ʼ��һ�Σ��´�

	if (real_time_on_off_flag){
		m_realTime_dialog->move(this->pos().x() + 215,this->pos().y()+180);
		m_realTime_dialog->show();
		stoptimer();
		ui.pushButton_autoUpDate->setCheckable(false);
	} 
	else{
		m_realTime_dialog->close();
		ui.pushButton_autoUpDate->setCheckable(true);

		//�򿪶�ʱˢ��
		ui.pushButton_autoUpDate->setChecked(true);	//���ð�ť
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
		//��ʱ������Ϊ�ܲ�ѯ����
		m_timePoint = QDateTime::currentDateTime();
		m_arrSqlTime = "";
		m_arrSqlTime = m_timePoint.addDays(m_date).toString("yyyy-MM-dd hh:mm:ss").toLatin1();	//���ò�ѯ��ʱ���
		m_arrSqlTime += "' <  datetime ";
		if (m_date == -1){	//���յ�����������
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
		QPoint GlobalPoint(this->mapToGlobal(QPoint(0, 0)));//��ȡ�ؼ��ڴ����е�����
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
	connect(this, SIGNAL(sigStartThread()), m_UdpLogServer, SLOT(slotChileThread()), Qt::QueuedConnection);	//���������߳�
	connect(ui.pushButton_Clear, SIGNAL(clicked()), this, SLOT(slotButtonClear()));
	connect(ui.pushButton_UpDate, SIGNAL(clicked()), this, SLOT(slotUpDate()));
	connect(m_timer, SIGNAL(timeout()), this, SLOT(slotUpDate()), Qt::DirectConnection);
	connect(ui.pushButton_UpPdge, SIGNAL(clicked()), this, SLOT(slotUpPage()));
	connect(ui.pushButton_firstPage, SIGNAL(clicked()), this, SLOT(slotHeadPage()));		//��βҳ
	connect(ui.pushButton_lastPage, SIGNAL(clicked()), this, SLOT(slotTailPage()));
	connect(ui.pushButton_DownPage, SIGNAL(clicked()), this, SLOT(slotDownPage()));
	connect(ui.spinBox_Page, SIGNAL(valueChanged(int)), this,  SLOT(slotGotoPage(int)));
	connect(m_setting_dialog, SIGNAL(signalDebugOnOff(int)), this,  SLOT(slotCheckBoxDebug(int)));
	connect(m_setting_dialog, SIGNAL(signalDeleteDayValue(int)), this, SLOT(slotSpinboxResetSaveDay(int)));	//����ɾ������
	connect(this, SIGNAL(signalResetSaveDay(int)), m_UdpLogServer, SLOT(slotReSetSQLDelete(int)), Qt::QueuedConnection);//�ȴ���ǰ����ִ����ϣ��ٵ���
	connect(ui.pushButton_realTime, SIGNAL(clicked()), this,  SLOT(slotOnRealtimeDialog()));	//ʵʱ����1
	connect(m_UdpLogServer, SIGNAL(signalSendMessageToRealTimeDia(char*, int)), m_realTime_dialog, SLOT(slotGetAndShowRealtimeMessage(char*, int)));
	connect(m_realTime_dialog, SIGNAL(m_sianal_realTime_dialog_isClose()), this, SLOT(slotSetCloseRealTimeDialog()));	//ʵʱ����2
	connect(m_realTime_dialog, SIGNAL(rejected()), this, SLOT(slotSetCloseRealTimeDialog()));	//ʵʱ����3
	connect(ui.pushButton_set, SIGNAL(clicked()), this, SLOT(slotOpenSettingDialog()));
	connect(ui.pushButton_autoUpDate, SIGNAL(clicked()), this, SLOT(slotONAutoUpDate()));
	connect(this, SIGNAL(signalStartAutoUpDate()), this, SLOT(slotONAutoUpDate()));

	connect(ui.pushButton_left, SIGNAL(clicked()), this, SLOT(slotSetStackWidgetFist()));	//��ťҳ��ҳ
	connect(ui.pushButton_right, SIGNAL(clicked()), this, SLOT(slotSetStackWidgetNext()));
	connect(ui.pushButton_secondRight, SIGNAL(clicked()), this, SLOT(slotSetStackWidgetFist()));
	connect(ui.pushButton_firstLeft, SIGNAL(clicked()), this, SLOT(slotSetStackWidgetNext()));

	connect(ui.pushButton_level, SIGNAL(clicked()), this, SLOT(slotShowLevelMenu()));	//��������
	connect(m_level_error, SIGNAL(triggered()), this, SLOT(slotOnErrorMenu()));	//������
	connect(m_level_warnning, SIGNAL(triggered()), this, SLOT(slotOnWarnningMenu()));
	connect(m_level_system, SIGNAL(triggered()), this, SLOT(slotOnSystemMenu()));

	connect(ui.pushButton_selectDays, SIGNAL(clicked()), this, SLOT(slotShowSelectDays()));	//��������
	connect(ui.action_selectOneDay, SIGNAL(triggered()), this,  SLOT(slotSelectOneDay()));	//ѡ������
	connect(ui.action_selectTheDay, SIGNAL(triggered()), this,  SLOT(slotSelectThreeDay()));
	connect(ui.action_sslectFiveDay, SIGNAL(triggered()), this,  SLOT(slotSelectFiveDay()));

	connect(ui.pushButton_gotoSomeDay, SIGNAL(clicked()), this, SLOT(slotShowGotoSomeDays()));	//��������ת
	connect(ui.action_gotoDay_now, SIGNAL(triggered()), this,  SLOT(slotGotoNow()));
	connect(ui.action_gotoDay_yestarday, SIGNAL(triggered()), this,  SLOT(slotGotoYesterday()));
	connect(ui.action_gotoDay_two, SIGNAL(triggered()), this,  SLOT(slotGotoTwoDayBefore()));
	connect(ui.action_gotoDay_three, SIGNAL(triggered()), this,  SLOT(slotGotoThreeDayBefore()));
	connect(ui.action_gotoDay_four, SIGNAL(triggered()), this,  SLOT(slotGotoFourDayBefore()));

	connect(ui.pushButton_min, SIGNAL(clicked()), this, SLOT(slotPushButtonMin()));	//��С��
}

void LogManagerSystem::initUi()
{
	this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
	//ȥ���߿�
	this->setWindowOpacity(1);    
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowTitle("LogServer");
	//this->setAttribute(Qt::WA_TranslucentBackground);
	QHeaderView* headerView = ui.tableWidget->horizontalHeader();	//��ͷ�����
	headerView->setDefaultAlignment(Qt::AlignLeft);
	ui.tableWidget->setAlternatingRowColors(true);					//���б�ɫ
}

void LogManagerSystem::initMemeber()
{
	m_UdpLogServer = new UDPLogServer(m_cri);
	m_realTime_dialog = new RealTimeDialog(this);
	m_setting_dialog = new SettingModalDialog(this);

	m_Warnning = true;		//��
	m_Error = true;		//��
	m_system = true;		//��
	m_debug = false;
	m_col = 5;		//�����������
	m_date = -1;	//�ݲ�ѯ����
	m_DBTableCount = 0;
	m_currentPage = 1;
	m_arrSql = "";
	m_allPage = 0;
	m_arrSqlLevel = " ";
	m_delete_days = 5;
	m_goto_days_count = 1;

	m_timePoint = QDateTime::currentDateTime();			//�״δ�ʹ�ã���ô����ʱ��
	m_arrSqlTime = "";
	m_arrSqlTime = m_timePoint.addDays(m_date).toString("yyyy-MM-dd hh:mm:ss").toLatin1();	//���ò�ѯ��ʱ���
	m_arrSqlTime += "' <  datetime ";

	m_menu = new QMenu(this);	//����˵�
	m_level_error = new QAction(m_menu);
	m_level_warnning = new QAction(m_menu);
	m_level_system = new QAction(m_menu);
	m_level_error->setCheckable(true);	//��ѡ
	m_level_warnning->setCheckable(true);
	m_level_system->setCheckable(true);
	m_level_error->setChecked(m_Error);
	m_level_warnning->setChecked(m_Warnning);
	m_level_system->setChecked(m_system);
	m_level_error->setText(QString::fromLocal8Bit("����"));
	m_level_warnning->setText(QString::fromLocal8Bit("����"));
	m_level_system->setText(QString::fromLocal8Bit("ϵͳ"));
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

	sqlLevelChange();	//���ڵ�һҳʱ���Ƚ���ǰҳ��Ϊ1������ȥ
	ui.spinBox_Page->setValue(1);	
	mUpDate();	//��ǰΪ��һ����ֱ��ˢ��
}

void LogManagerSystem::slotOnWarnningMenu()
{
	stoptimer();

	//state ==2(Qt::Checked)��Ϊ�棬����Ϊ��(���¹���)
	m_Warnning = !m_Warnning;
	m_level_warnning->setChecked(m_Warnning);
	if (m_Warnning == true){
		ui.label_warn->setStyleSheet("background-color: rgb(255, 255, 0);");
	}
	else{
		ui.label_warn->setStyleSheet("background-color: rgb(255, 255, 255);");
	}
	sqlLevelChange();
	ui.spinBox_Page->setValue(1);	//���ڵ�һҳʱ���Ƚ���ǰҳ��Ϊ1������ȥ
	mUpDate();	//��ǰΪ��һ����ֱ��ˢ��
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
	sqlLevelChange();	//���ڵ�һҳʱ���Ƚ���ǰҳ��Ϊ1������ȥ
	ui.spinBox_Page->setValue(1);	
	mUpDate();	//��ǰΪ��һ����ֱ��ˢ��
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
	//ѡ�е�������ѡ��δѡ�в���ѡ
	ui.action_selectOneDay->setChecked(index == 0 ? true:false);
	ui.action_selectTheDay->setChecked(index == 1 ? true:false);
	ui.action_sslectFiveDay->setChecked(index == 2 ? true:false);
}

void LogManagerSystem::resetGotoSomeDayOnOffCheck( int index )
{
	//������ѡ������Ϊѡ�У�����ѡ��
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