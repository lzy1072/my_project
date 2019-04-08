/********************************************************************************
** Form generated from reading UI file 'logmanagersystem.ui'
**
** Created: Mon Feb 25 11:11:54 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGMANAGERSYSTEM_H
#define UI_LOGMANAGERSYSTEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogManagerSystemClass
{
public:
    QAction *action_selectOneDay;
    QAction *action_selectTheDay;
    QAction *action_sslectFiveDay;
    QAction *action_gotoDay_now;
    QAction *action_gotoDay_yestarday;
    QAction *action_gotoDay_two;
    QAction *action_gotoDay_three;
    QAction *action_gotoDay_four;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_title;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_min;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_error;
    QLabel *label_warn;
    QLabel *label_system;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *spinBox_Page;
    QLabel *label_Page;
    QWidget *widget_buttom;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_firstLeft;
    QPushButton *pushButton_firstPage;
    QPushButton *pushButton_UpPdge;
    QPushButton *pushButton_DownPage;
    QPushButton *pushButton_lastPage;
    QPushButton *pushButton_selectDays;
    QPushButton *pushButton_gotoSomeDay;
    QPushButton *pushButton_level;
    QPushButton *pushButton_autoUpDate;
    QPushButton *pushButton_right;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_left;
    QPushButton *pushButton_realTime;
    QPushButton *pushButton_UpDate;
    QPushButton *pushButton_set;
    QPushButton *pushButton_Clear;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QPushButton *pushButton_secondRight;

    void setupUi(QMainWindow *LogManagerSystemClass)
    {
        if (LogManagerSystemClass->objectName().isEmpty())
            LogManagerSystemClass->setObjectName(QString::fromUtf8("LogManagerSystemClass"));
        LogManagerSystemClass->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LogManagerSystemClass->sizePolicy().hasHeightForWidth());
        LogManagerSystemClass->setSizePolicy(sizePolicy);
        LogManagerSystemClass->setMinimumSize(QSize(800, 600));
        LogManagerSystemClass->setMaximumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/LogManagerSystem/res/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        LogManagerSystemClass->setWindowIcon(icon);
        LogManagerSystemClass->setStyleSheet(QString::fromUtf8(""));
        LogManagerSystemClass->setToolButtonStyle(Qt::ToolButtonTextOnly);
        LogManagerSystemClass->setTabShape(QTabWidget::Rounded);
        LogManagerSystemClass->setDockNestingEnabled(false);
        action_selectOneDay = new QAction(LogManagerSystemClass);
        action_selectOneDay->setObjectName(QString::fromUtf8("action_selectOneDay"));
        action_selectOneDay->setCheckable(true);
        action_selectTheDay = new QAction(LogManagerSystemClass);
        action_selectTheDay->setObjectName(QString::fromUtf8("action_selectTheDay"));
        action_selectTheDay->setCheckable(true);
        action_sslectFiveDay = new QAction(LogManagerSystemClass);
        action_sslectFiveDay->setObjectName(QString::fromUtf8("action_sslectFiveDay"));
        action_sslectFiveDay->setCheckable(true);
        action_gotoDay_now = new QAction(LogManagerSystemClass);
        action_gotoDay_now->setObjectName(QString::fromUtf8("action_gotoDay_now"));
        action_gotoDay_now->setCheckable(true);
        action_gotoDay_yestarday = new QAction(LogManagerSystemClass);
        action_gotoDay_yestarday->setObjectName(QString::fromUtf8("action_gotoDay_yestarday"));
        action_gotoDay_yestarday->setCheckable(true);
        action_gotoDay_two = new QAction(LogManagerSystemClass);
        action_gotoDay_two->setObjectName(QString::fromUtf8("action_gotoDay_two"));
        action_gotoDay_two->setCheckable(true);
        action_gotoDay_three = new QAction(LogManagerSystemClass);
        action_gotoDay_three->setObjectName(QString::fromUtf8("action_gotoDay_three"));
        action_gotoDay_three->setCheckable(true);
        action_gotoDay_four = new QAction(LogManagerSystemClass);
        action_gotoDay_four->setObjectName(QString::fromUtf8("action_gotoDay_four"));
        action_gotoDay_four->setCheckable(true);
        centralWidget = new QWidget(LogManagerSystemClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_title = new QWidget(centralWidget);
        widget_title->setObjectName(QString::fromUtf8("widget_title"));
        widget_title->setMinimumSize(QSize(800, 28));
        widget_title->setMaximumSize(QSize(800, 28));
        widget_title->setStyleSheet(QString::fromUtf8("background-color: rgb(210, 231, 255);\n"
"border-color: rgb(0, 255, 255);"));
        horizontalLayout_2 = new QHBoxLayout(widget_title);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 0, 5, 0);
        label = new QLabel(widget_title);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(25, 25));
        label->setMaximumSize(QSize(25, 25));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/LogManagerSystem/res/title.png);\n"
""));
        label->setTextFormat(Qt::LogText);
        label->setPixmap(QPixmap(QString::fromUtf8(":/LogManagerSystem/res/title.png")));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(widget_title);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(622, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_min = new QPushButton(widget_title);
        pushButton_min->setObjectName(QString::fromUtf8("pushButton_min"));
        pushButton_min->setMinimumSize(QSize(23, 23));
        pushButton_min->setMaximumSize(QSize(23, 23));
        pushButton_min->setFlat(true);

        horizontalLayout_2->addWidget(pushButton_min);


        verticalLayout_2->addWidget(widget_title);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 20));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, -1, 0);
        label_error = new QLabel(widget);
        label_error->setObjectName(QString::fromUtf8("label_error"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_error->sizePolicy().hasHeightForWidth());
        label_error->setSizePolicy(sizePolicy1);
        label_error->setMinimumSize(QSize(30, 0));
        label_error->setMaximumSize(QSize(30, 16777215));
        label_error->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        label_error->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_error);

        label_warn = new QLabel(widget);
        label_warn->setObjectName(QString::fromUtf8("label_warn"));
        sizePolicy1.setHeightForWidth(label_warn->sizePolicy().hasHeightForWidth());
        label_warn->setSizePolicy(sizePolicy1);
        label_warn->setMinimumSize(QSize(30, 0));
        label_warn->setMaximumSize(QSize(30, 16777215));
        label_warn->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        label_warn->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_warn);

        label_system = new QLabel(widget);
        label_system->setObjectName(QString::fromUtf8("label_system"));
        sizePolicy1.setHeightForWidth(label_system->sizePolicy().hasHeightForWidth());
        label_system->setSizePolicy(sizePolicy1);
        label_system->setMinimumSize(QSize(30, 0));
        label_system->setMaximumSize(QSize(30, 16777215));
        label_system->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(85, 170, 255);"));
        label_system->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_system);

        horizontalSpacer = new QSpacerItem(598, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(67, 20));
        groupBox->setMaximumSize(QSize(67, 20));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        spinBox_Page = new QSpinBox(groupBox);
        spinBox_Page->setObjectName(QString::fromUtf8("spinBox_Page"));
        sizePolicy.setHeightForWidth(spinBox_Page->sizePolicy().hasHeightForWidth());
        spinBox_Page->setSizePolicy(sizePolicy);
        spinBox_Page->setMaximumSize(QSize(24, 16777215));
        spinBox_Page->setMouseTracking(true);
        spinBox_Page->setFocusPolicy(Qt::NoFocus);
        spinBox_Page->setContextMenuPolicy(Qt::DefaultContextMenu);
        spinBox_Page->setLayoutDirection(Qt::RightToLeft);
        spinBox_Page->setStyleSheet(QString::fromUtf8("background-color:rgb(240, 240, 240);"));
        spinBox_Page->setWrapping(false);
        spinBox_Page->setFrame(false);
        spinBox_Page->setReadOnly(true);
        spinBox_Page->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_Page->setKeyboardTracking(true);
        spinBox_Page->setMaximum(1000);
        spinBox_Page->setValue(1);

        horizontalLayout_3->addWidget(spinBox_Page);

        label_Page = new QLabel(groupBox);
        label_Page->setObjectName(QString::fromUtf8("label_Page"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_Page->sizePolicy().hasHeightForWidth());
        label_Page->setSizePolicy(sizePolicy2);
        label_Page->setMinimumSize(QSize(42, 0));
        label_Page->setMaximumSize(QSize(42, 16777215));

        horizontalLayout_3->addWidget(label_Page);


        horizontalLayout->addWidget(groupBox);


        verticalLayout_2->addWidget(widget);

        widget_buttom = new QWidget(centralWidget);
        widget_buttom->setObjectName(QString::fromUtf8("widget_buttom"));
        widget_buttom->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widget_buttom);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 6);
        tableWidget = new QTableWidget(widget_buttom);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMinimumSize(QSize(0, 10));
        tableWidget->setMouseTracking(true);
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setFrameShape(QFrame::Box);
        tableWidget->setFrameShadow(QFrame::Plain);

        verticalLayout->addWidget(tableWidget);

        stackedWidget = new QStackedWidget(widget_buttom);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(36, 36));
        stackedWidget->setMaximumSize(QSize(800, 50));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayout_4 = new QHBoxLayout(page);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_firstLeft = new QPushButton(page);
        pushButton_firstLeft->setObjectName(QString::fromUtf8("pushButton_firstLeft"));
        pushButton_firstLeft->setEnabled(true);
        pushButton_firstLeft->setMinimumSize(QSize(36, 36));
        pushButton_firstLeft->setMaximumSize(QSize(40, 40));
        pushButton_firstLeft->setCheckable(false);
        pushButton_firstLeft->setChecked(false);
        pushButton_firstLeft->setAutoDefault(false);
        pushButton_firstLeft->setDefault(false);
        pushButton_firstLeft->setFlat(false);

        horizontalLayout_4->addWidget(pushButton_firstLeft);

        pushButton_firstPage = new QPushButton(page);
        pushButton_firstPage->setObjectName(QString::fromUtf8("pushButton_firstPage"));
        pushButton_firstPage->setMinimumSize(QSize(54, 36));
        pushButton_firstPage->setMaximumSize(QSize(54, 36));

        horizontalLayout_4->addWidget(pushButton_firstPage);

        pushButton_UpPdge = new QPushButton(page);
        pushButton_UpPdge->setObjectName(QString::fromUtf8("pushButton_UpPdge"));
        pushButton_UpPdge->setMinimumSize(QSize(54, 36));
        pushButton_UpPdge->setMaximumSize(QSize(54, 36));

        horizontalLayout_4->addWidget(pushButton_UpPdge);

        pushButton_DownPage = new QPushButton(page);
        pushButton_DownPage->setObjectName(QString::fromUtf8("pushButton_DownPage"));
        pushButton_DownPage->setMinimumSize(QSize(54, 36));
        pushButton_DownPage->setMaximumSize(QSize(54, 36));

        horizontalLayout_4->addWidget(pushButton_DownPage);

        pushButton_lastPage = new QPushButton(page);
        pushButton_lastPage->setObjectName(QString::fromUtf8("pushButton_lastPage"));
        pushButton_lastPage->setMinimumSize(QSize(54, 36));
        pushButton_lastPage->setMaximumSize(QSize(54, 36));

        horizontalLayout_4->addWidget(pushButton_lastPage);

        pushButton_selectDays = new QPushButton(page);
        pushButton_selectDays->setObjectName(QString::fromUtf8("pushButton_selectDays"));
        pushButton_selectDays->setMinimumSize(QSize(54, 36));
        pushButton_selectDays->setMaximumSize(QSize(54, 36));
        pushButton_selectDays->setCheckable(false);
        pushButton_selectDays->setChecked(false);

        horizontalLayout_4->addWidget(pushButton_selectDays);

        pushButton_gotoSomeDay = new QPushButton(page);
        pushButton_gotoSomeDay->setObjectName(QString::fromUtf8("pushButton_gotoSomeDay"));
        pushButton_gotoSomeDay->setMinimumSize(QSize(54, 36));
        pushButton_gotoSomeDay->setMaximumSize(QSize(54, 36));
        pushButton_gotoSomeDay->setCheckable(false);
        pushButton_gotoSomeDay->setChecked(false);

        horizontalLayout_4->addWidget(pushButton_gotoSomeDay);

        pushButton_level = new QPushButton(page);
        pushButton_level->setObjectName(QString::fromUtf8("pushButton_level"));
        pushButton_level->setMinimumSize(QSize(54, 36));
        pushButton_level->setMaximumSize(QSize(54, 16777215));

        horizontalLayout_4->addWidget(pushButton_level);

        pushButton_autoUpDate = new QPushButton(page);
        pushButton_autoUpDate->setObjectName(QString::fromUtf8("pushButton_autoUpDate"));
        pushButton_autoUpDate->setMinimumSize(QSize(54, 36));
        pushButton_autoUpDate->setMaximumSize(QSize(54, 36));
        pushButton_autoUpDate->setCheckable(true);
        pushButton_autoUpDate->setChecked(true);
        pushButton_autoUpDate->setAutoRepeat(false);
        pushButton_autoUpDate->setAutoExclusive(false);
        pushButton_autoUpDate->setAutoDefault(false);
        pushButton_autoUpDate->setFlat(false);

        horizontalLayout_4->addWidget(pushButton_autoUpDate);

        pushButton_right = new QPushButton(page);
        pushButton_right->setObjectName(QString::fromUtf8("pushButton_right"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_right->sizePolicy().hasHeightForWidth());
        pushButton_right->setSizePolicy(sizePolicy3);
        pushButton_right->setMinimumSize(QSize(36, 36));
        pushButton_right->setMaximumSize(QSize(40, 40));

        horizontalLayout_4->addWidget(pushButton_right);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_5 = new QHBoxLayout(page_2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_left = new QPushButton(page_2);
        pushButton_left->setObjectName(QString::fromUtf8("pushButton_left"));
        sizePolicy3.setHeightForWidth(pushButton_left->sizePolicy().hasHeightForWidth());
        pushButton_left->setSizePolicy(sizePolicy3);
        pushButton_left->setMinimumSize(QSize(36, 36));
        pushButton_left->setMaximumSize(QSize(40, 40));

        horizontalLayout_5->addWidget(pushButton_left);

        pushButton_realTime = new QPushButton(page_2);
        pushButton_realTime->setObjectName(QString::fromUtf8("pushButton_realTime"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(60);
        sizePolicy4.setVerticalStretch(40);
        sizePolicy4.setHeightForWidth(pushButton_realTime->sizePolicy().hasHeightForWidth());
        pushButton_realTime->setSizePolicy(sizePolicy4);
        pushButton_realTime->setMinimumSize(QSize(54, 36));
        pushButton_realTime->setMaximumSize(QSize(54, 36));

        horizontalLayout_5->addWidget(pushButton_realTime);

        pushButton_UpDate = new QPushButton(page_2);
        pushButton_UpDate->setObjectName(QString::fromUtf8("pushButton_UpDate"));
        pushButton_UpDate->setMinimumSize(QSize(54, 36));
        pushButton_UpDate->setMaximumSize(QSize(54, 36));

        horizontalLayout_5->addWidget(pushButton_UpDate);

        pushButton_set = new QPushButton(page_2);
        pushButton_set->setObjectName(QString::fromUtf8("pushButton_set"));
        sizePolicy.setHeightForWidth(pushButton_set->sizePolicy().hasHeightForWidth());
        pushButton_set->setSizePolicy(sizePolicy);
        pushButton_set->setMinimumSize(QSize(54, 36));
        pushButton_set->setMaximumSize(QSize(54, 36));
        pushButton_set->setLayoutDirection(Qt::LeftToRight);
        pushButton_set->setDefault(false);
        pushButton_set->setFlat(false);

        horizontalLayout_5->addWidget(pushButton_set);

        pushButton_Clear = new QPushButton(page_2);
        pushButton_Clear->setObjectName(QString::fromUtf8("pushButton_Clear"));
        pushButton_Clear->setMinimumSize(QSize(54, 36));
        pushButton_Clear->setMaximumSize(QSize(54, 36));
        pushButton_Clear->setCheckable(false);
        pushButton_Clear->setChecked(false);

        horizontalLayout_5->addWidget(pushButton_Clear);

        groupBox_2 = new QGroupBox(page_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(54, 36));
        groupBox_2->setMaximumSize(QSize(54, 36));

        horizontalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(page_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(54, 36));
        groupBox_3->setMaximumSize(QSize(54, 36));

        horizontalLayout_5->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(page_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(54, 36));
        groupBox_4->setMaximumSize(QSize(54, 36));

        horizontalLayout_5->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(page_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        groupBox_5->setMinimumSize(QSize(54, 36));
        groupBox_5->setMaximumSize(QSize(54, 36));

        horizontalLayout_5->addWidget(groupBox_5);

        pushButton_secondRight = new QPushButton(page_2);
        pushButton_secondRight->setObjectName(QString::fromUtf8("pushButton_secondRight"));
        pushButton_secondRight->setEnabled(true);
        sizePolicy.setHeightForWidth(pushButton_secondRight->sizePolicy().hasHeightForWidth());
        pushButton_secondRight->setSizePolicy(sizePolicy);
        pushButton_secondRight->setMinimumSize(QSize(36, 36));
        pushButton_secondRight->setMaximumSize(QSize(40, 40));

        horizontalLayout_5->addWidget(pushButton_secondRight);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        verticalLayout_2->addWidget(widget_buttom);

        LogManagerSystemClass->setCentralWidget(centralWidget);

        retranslateUi(LogManagerSystemClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LogManagerSystemClass);
    } // setupUi

    void retranslateUi(QMainWindow *LogManagerSystemClass)
    {
        LogManagerSystemClass->setWindowTitle(QApplication::translate("LogManagerSystemClass", "LogServer", 0, QApplication::UnicodeUTF8));
        action_selectOneDay->setText(QApplication::translate("LogManagerSystemClass", "1\345\244\251", 0, QApplication::UnicodeUTF8));
        action_selectTheDay->setText(QApplication::translate("LogManagerSystemClass", "3\345\244\251", 0, QApplication::UnicodeUTF8));
        action_sslectFiveDay->setText(QApplication::translate("LogManagerSystemClass", "\346\211\200\346\234\211", 0, QApplication::UnicodeUTF8));
        action_gotoDay_now->setText(QApplication::translate("LogManagerSystemClass", "\344\273\212\345\244\251", 0, QApplication::UnicodeUTF8));
        action_gotoDay_yestarday->setText(QApplication::translate("LogManagerSystemClass", "\346\230\250\345\244\251", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_gotoDay_yestarday->setToolTip(QApplication::translate("LogManagerSystemClass", "\346\230\250\345\244\251", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_gotoDay_two->setText(QApplication::translate("LogManagerSystemClass", "\345\211\215\345\244\251", 0, QApplication::UnicodeUTF8));
        action_gotoDay_three->setText(QApplication::translate("LogManagerSystemClass", "3\345\244\251\345\211\215", 0, QApplication::UnicodeUTF8));
        action_gotoDay_four->setText(QApplication::translate("LogManagerSystemClass", "4\345\244\251\345\211\215", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_2->setText(QApplication::translate("LogManagerSystemClass", "\346\227\245\345\277\227\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        pushButton_min->setText(QApplication::translate("LogManagerSystemClass", "-", 0, QApplication::UnicodeUTF8));
        label_error->setText(QApplication::translate("LogManagerSystemClass", "\351\224\231\350\257\257", 0, QApplication::UnicodeUTF8));
        label_warn->setText(QApplication::translate("LogManagerSystemClass", "\350\255\246\345\221\212", 0, QApplication::UnicodeUTF8));
        label_system->setText(QApplication::translate("LogManagerSystemClass", "\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        spinBox_Page->setSpecialValueText(QString());
        spinBox_Page->setSuffix(QString());
        spinBox_Page->setPrefix(QString());
        label_Page->setText(QApplication::translate("LogManagerSystemClass", "\345\205\2610\351\241\265", 0, QApplication::UnicodeUTF8));
        pushButton_firstLeft->setText(QApplication::translate("LogManagerSystemClass", "<<", 0, QApplication::UnicodeUTF8));
        pushButton_firstLeft->setShortcut(QApplication::translate("LogManagerSystemClass", "F9", 0, QApplication::UnicodeUTF8));
        pushButton_firstPage->setText(QApplication::translate("LogManagerSystemClass", "\351\246\226  \351\241\265", 0, QApplication::UnicodeUTF8));
        pushButton_firstPage->setShortcut(QApplication::translate("LogManagerSystemClass", "F1", 0, QApplication::UnicodeUTF8));
        pushButton_UpPdge->setText(QApplication::translate("LogManagerSystemClass", "\344\270\212\347\277\273\351\241\265", 0, QApplication::UnicodeUTF8));
        pushButton_UpPdge->setShortcut(QApplication::translate("LogManagerSystemClass", "F2", 0, QApplication::UnicodeUTF8));
        pushButton_DownPage->setText(QApplication::translate("LogManagerSystemClass", "\344\270\213\347\277\273\351\241\265", 0, QApplication::UnicodeUTF8));
        pushButton_DownPage->setShortcut(QApplication::translate("LogManagerSystemClass", "F3", 0, QApplication::UnicodeUTF8));
        pushButton_lastPage->setText(QApplication::translate("LogManagerSystemClass", "\345\260\276  \351\241\265", 0, QApplication::UnicodeUTF8));
        pushButton_lastPage->setShortcut(QApplication::translate("LogManagerSystemClass", "F4", 0, QApplication::UnicodeUTF8));
        pushButton_selectDays->setText(QApplication::translate("LogManagerSystemClass", "\345\244\251\346\225\260", 0, QApplication::UnicodeUTF8));
        pushButton_selectDays->setShortcut(QApplication::translate("LogManagerSystemClass", "F5", 0, QApplication::UnicodeUTF8));
        pushButton_gotoSomeDay->setText(QApplication::translate("LogManagerSystemClass", "\350\267\263\350\275\254", 0, QApplication::UnicodeUTF8));
        pushButton_gotoSomeDay->setShortcut(QApplication::translate("LogManagerSystemClass", "F6", 0, QApplication::UnicodeUTF8));
        pushButton_level->setText(QApplication::translate("LogManagerSystemClass", "\347\272\247\345\210\253", 0, QApplication::UnicodeUTF8));
        pushButton_level->setShortcut(QApplication::translate("LogManagerSystemClass", "F7", 0, QApplication::UnicodeUTF8));
        pushButton_autoUpDate->setText(QApplication::translate("LogManagerSystemClass", "\345\256\232\346\227\266\345\210\267\346\226\260", 0, QApplication::UnicodeUTF8));
        pushButton_autoUpDate->setShortcut(QApplication::translate("LogManagerSystemClass", "F8", 0, QApplication::UnicodeUTF8));
        pushButton_right->setText(QApplication::translate("LogManagerSystemClass", ">>", 0, QApplication::UnicodeUTF8));
        pushButton_right->setShortcut(QApplication::translate("LogManagerSystemClass", "F10", 0, QApplication::UnicodeUTF8));
        pushButton_left->setText(QApplication::translate("LogManagerSystemClass", "<<", 0, QApplication::UnicodeUTF8));
        pushButton_left->setShortcut(QApplication::translate("LogManagerSystemClass", "F9", 0, QApplication::UnicodeUTF8));
        pushButton_realTime->setText(QApplication::translate("LogManagerSystemClass", "\345\256\236\346\227\266", 0, QApplication::UnicodeUTF8));
        pushButton_realTime->setShortcut(QApplication::translate("LogManagerSystemClass", "F1", 0, QApplication::UnicodeUTF8));
        pushButton_UpDate->setText(QApplication::translate("LogManagerSystemClass", "F5\345\210\267\346\226\260", 0, QApplication::UnicodeUTF8));
        pushButton_UpDate->setShortcut(QApplication::translate("LogManagerSystemClass", "F2", 0, QApplication::UnicodeUTF8));
        pushButton_set->setText(QApplication::translate("LogManagerSystemClass", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_set->setShortcut(QApplication::translate("LogManagerSystemClass", "F3", 0, QApplication::UnicodeUTF8));
        pushButton_Clear->setText(QApplication::translate("LogManagerSystemClass", "\346\270\205\351\231\244", 0, QApplication::UnicodeUTF8));
        pushButton_Clear->setShortcut(QApplication::translate("LogManagerSystemClass", "F4", "F8", QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        groupBox_3->setTitle(QString());
        groupBox_4->setTitle(QString());
        groupBox_5->setTitle(QString());
        pushButton_secondRight->setText(QApplication::translate("LogManagerSystemClass", ">>", 0, QApplication::UnicodeUTF8));
        pushButton_secondRight->setShortcut(QApplication::translate("LogManagerSystemClass", "F10", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LogManagerSystemClass: public Ui_LogManagerSystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGMANAGERSYSTEM_H
