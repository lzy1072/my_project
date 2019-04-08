#include "real_time_dialog.h"

#define SHOW_MAX_ITEM_NUM 11

RealTimeDialog::RealTimeDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint&~Qt::WindowMinimizeButtonHint&~Qt::WindowMaximizeButtonHint);

}

RealTimeDialog::~RealTimeDialog()
{
	//�ͷ�vector��δ�ͷŵ�
	int item_num = ui.listWidget->count();
	for(int i=0; i<item_num;){
		QVector<QListWidgetItem*>::iterator iter_widget;
		iter_widget = m_vector_listWidget_items.begin();
		if (iter_widget != NULL){
			//debug��¼1�����ܱ�����
			delete (*iter_widget);
			iter_widget = m_vector_listWidget_items.erase(iter_widget);
		}
	}
}

void RealTimeDialog::slotGetAndShowRealtimeMessage( char* message, int level )
{
	//level 1���죨123����2���ƣ�4����3������otherwise����4����ɫ��7��
	QListWidgetItem* new_item = new QListWidgetItem;
	QString temp_text = QString::fromLocal8Bit(message);
	new_item->setText(temp_text);
	switch (level) {	//������ɫ
		case 7:
			new_item->setBackgroundColor(QColor(255, 255, 255));
			break;
		case 4:
			new_item->setBackgroundColor(QColor(255, 255, 0));
			break;
		case 1:
		case 2:
		case 3:
			new_item->setBackgroundColor(QColor(255, 0, 0));
			break;
		default:
			new_item->setBackgroundColor(QColor(79, 134, 240));
	}
	ui.listWidget->addItem(new_item);
	m_vector_listWidget_items.push_back(new_item);

	deleteItem();
}

void RealTimeDialog::deleteItem()
{
	//����50������ͬʱɾ��
	int item_num = ui.listWidget->count();
	if (item_num > SHOW_MAX_ITEM_NUM){
		QVector<QListWidgetItem*>::iterator iter_widget;
		iter_widget = m_vector_listWidget_items.begin();

		//debug��¼1�����ܱ�����
		delete (*iter_widget);
		//m_vector_listWidget_items.pop_front();
		m_vector_listWidget_items.erase(iter_widget);//erase����ɾ��ָ��λ�õ�Ԫ�أ�Ȼ�󷵻���һ��Ԫ�صĵ�����
	}
	//ui.listWidget->setCurrentRow(item_num + 10);	//���ֽ����ܿ���������
}

void RealTimeDialog::closeEvent( QCloseEvent* event )
{
	emit m_sianal_realTime_dialog_isClose();
}

void RealTimeDialog::moveEvent( QMoveEvent * event )
{
	if (!(m_left_top.x()<= this->pos().x() && this->pos().x() <= m_right_bottom.x() \
		&& m_left_top.y()<=this->pos().y() && this->pos().y()<=m_right_bottom.y()))
	{
		this->move(m_right_bottom.x(), m_right_bottom.y());
	}

}

void RealTimeDialog::getRegion( int left, int top, int right, int botton )
{
	m_left_top.setX(left);
	m_left_top.setY(top);
	m_right_bottom.setX(right);
	m_right_bottom.setY(botton);
}
