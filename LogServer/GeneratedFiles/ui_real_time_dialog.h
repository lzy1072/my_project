/********************************************************************************
** Form generated from reading UI file 'real_time_dialog.ui'
**
** Created: Mon Feb 25 11:11:54 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REAL_TIME_DIALOG_H
#define UI_REAL_TIME_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_realTimeDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;

    void setupUi(QDialog *realTimeDialog)
    {
        if (realTimeDialog->objectName().isEmpty())
            realTimeDialog->setObjectName(QString::fromUtf8("realTimeDialog"));
        realTimeDialog->setWindowModality(Qt::ApplicationModal);
        realTimeDialog->setEnabled(true);
        realTimeDialog->resize(570, 320);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(realTimeDialog->sizePolicy().hasHeightForWidth());
        realTimeDialog->setSizePolicy(sizePolicy);
        realTimeDialog->setMinimumSize(QSize(570, 320));
        realTimeDialog->setMaximumSize(QSize(570, 320));
        realTimeDialog->setContextMenuPolicy(Qt::DefaultContextMenu);
        realTimeDialog->setAcceptDrops(false);
        realTimeDialog->setInputMethodHints(Qt::ImhNone);
        realTimeDialog->setSizeGripEnabled(false);
        realTimeDialog->setModal(false);
        horizontalLayout = new QHBoxLayout(realTimeDialog);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(realTimeDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMaximumSize(QSize(16777215, 16777215));
        listWidget->setInputMethodHints(Qt::ImhNone);
        listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        listWidget->setFlow(QListView::TopToBottom);
        listWidget->setProperty("isWrapping", QVariant(false));

        horizontalLayout->addWidget(listWidget);


        retranslateUi(realTimeDialog);

        QMetaObject::connectSlotsByName(realTimeDialog);
    } // setupUi

    void retranslateUi(QDialog *realTimeDialog)
    {
        realTimeDialog->setWindowTitle(QApplication::translate("realTimeDialog", "Real_Time_Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class realTimeDialog: public Ui_realTimeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REAL_TIME_DIALOG_H
