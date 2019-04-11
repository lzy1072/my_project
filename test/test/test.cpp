#include "test.h"
#include "MyItem.h"
test::test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	MyItem* temp = new MyItem;
	temp->setText(0, temp->m_test);
	ui.treeWidget->addTopLevelItem(temp);
	//MyItem* a = new MyItem()
	
}

test::~test()
{

}
