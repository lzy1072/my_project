#ifndef REAL_TIME_DIALOG_H
#define REAL_TIME_DIALOG_H
#include <QDialog>
#include <QPoint>
#include <QtGui/QMouseEvent>
#include <QCloseEvent>
#include "ui_real_time_dialog.h"

class RealTimeDialog : public QDialog
{
	Q_OBJECT

public:
	RealTimeDialog(QWidget *parent = 0);
	~RealTimeDialog();
private:
	void deleteItem();	//ɾ����delete��listwidget��item
public:
	void getRegion( int, int, int, int );	//��ȡ���ƶ���Χ
protected:
	void closeEvent(QCloseEvent* event);
	virtual void moveEvent ( QMoveEvent * event );
private slots:
	void slotGetAndShowRealtimeMessage(char* message, int level);
signals:
	void m_sianal_realTime_dialog_isClose();
private:
	Ui::realTimeDialog ui;
	QVector<QListWidgetItem*> m_vector_listWidget_items;
	QPoint m_left_top;		//���ƶ���Χ
	QPoint m_right_bottom;
};

#endif // REAL_TIME_DIALOG_H
