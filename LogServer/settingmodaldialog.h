#ifndef SETTINGMODALDIALOG_H
#define SETTINGMODALDIALOG_H

#include <QDialog>
#include "ui_settingmodaldialog.h"


class SettingModalDialog : public QDialog
{
	Q_OBJECT

public:
	SettingModalDialog(QWidget *parent = 0);
	~SettingModalDialog();

	void setPostion();
protected:
	virtual void moveEvent ( QMoveEvent * event );
	virtual void keyPressEvent(QKeyEvent * event);
private slots:
	void slotSendOnOffDebug(int);
	void slotSendNewDeleteDayValue(int);
signals:
	void signalDebugOnOff(int);
	void signalDeleteDayValue(int);
private:
	Ui::SettingModalDialog ui;
public:
	int m_x;
	int m_y;
	bool m_postion_flag;
};

#endif // SETTINGMODALDIALOG_H
