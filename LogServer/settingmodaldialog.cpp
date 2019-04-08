#include "settingmodaldialog.h"
#include <QKeyEvent> 
SettingModalDialog::SettingModalDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_postion_flag = true;
	this->setModal(true);
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint&~Qt::WindowMinimizeButtonHint&~Qt::WindowMaximizeButtonHint);

	connect(ui.checkBox_Debug, SIGNAL(stateChanged(int)), this, SLOT(slotSendOnOffDebug(int)));
	connect(ui.comboBox_saveDays, SIGNAL(activated(int)), this, SLOT(slotSendNewDeleteDayValue(int)));
}

SettingModalDialog::~SettingModalDialog()
{
}

void SettingModalDialog::slotSendOnOffDebug( int state )
{
	emit signalDebugOnOff(state);
}

void SettingModalDialog::moveEvent( QMoveEvent * event )
{
	setPostion();
}

void SettingModalDialog::setPostion()
{
	if (m_postion_flag == true){
		QPoint GlobalPoint(this->mapToGlobal(QPoint(0, 0)));//获取控件在窗体中的坐标
		m_x = GlobalPoint.x();
		m_y = GlobalPoint.y();
		m_postion_flag = false;
	}
	this->move(m_x, m_y);
}

void SettingModalDialog::keyPressEvent( QKeyEvent * event )
{
	if (event->key() == Qt::Key_F2){
		ui.comboBox_saveDays->showPopup();
	}
	else if (event->key() == Qt::Key_Escape){
		this->close();
	}
}

void SettingModalDialog::slotSendNewDeleteDayValue( int index )
{
	const int kSaveMaxDays = 5;
	int value = kSaveMaxDays - index;
	emit signalDeleteDayValue(value);
}