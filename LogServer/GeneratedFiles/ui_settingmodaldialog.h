/********************************************************************************
** Form generated from reading UI file 'settingmodaldialog.ui'
**
** Created: Mon Feb 25 11:11:52 2019
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGMODALDIALOG_H
#define UI_SETTINGMODALDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SettingModalDialog
{
public:
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_Debug;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *comboBox_saveDays;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *SettingModalDialog)
    {
        if (SettingModalDialog->objectName().isEmpty())
            SettingModalDialog->setObjectName(QString::fromUtf8("SettingModalDialog"));
        SettingModalDialog->resize(300, 80);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SettingModalDialog->sizePolicy().hasHeightForWidth());
        SettingModalDialog->setSizePolicy(sizePolicy);
        SettingModalDialog->setMinimumSize(QSize(300, 80));
        SettingModalDialog->setMaximumSize(QSize(300, 80));
        horizontalLayout_4 = new QHBoxLayout(SettingModalDialog);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox_Debug = new QCheckBox(SettingModalDialog);
        checkBox_Debug->setObjectName(QString::fromUtf8("checkBox_Debug"));
        checkBox_Debug->setMinimumSize(QSize(96, 13));
        checkBox_Debug->setMaximumSize(QSize(16777215, 12));
        checkBox_Debug->setCheckable(true);
        checkBox_Debug->setChecked(false);

        horizontalLayout->addWidget(checkBox_Debug);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        horizontalLayout_4->addLayout(horizontalLayout);

        line = new QFrame(SettingModalDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, 0, -1);
        label = new QLabel(SettingModalDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 9));
        label->setMaximumSize(QSize(66, 12));

        horizontalLayout_3->addWidget(label);

        comboBox_saveDays = new QComboBox(SettingModalDialog);
        comboBox_saveDays->setObjectName(QString::fromUtf8("comboBox_saveDays"));

        horizontalLayout_3->addWidget(comboBox_saveDays);


        horizontalLayout_2->addLayout(horizontalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        retranslateUi(SettingModalDialog);

        QMetaObject::connectSlotsByName(SettingModalDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingModalDialog)
    {
        SettingModalDialog->setWindowTitle(QApplication::translate("SettingModalDialog", "SettingModalDialog", 0, QApplication::UnicodeUTF8));
        checkBox_Debug->setText(QApplication::translate("SettingModalDialog", "F1\350\260\203\350\257\225\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        checkBox_Debug->setShortcut(QApplication::translate("SettingModalDialog", "F1", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingModalDialog", "F2\344\277\235\345\255\230\345\244\251\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        comboBox_saveDays->clear();
        comboBox_saveDays->insertItems(0, QStringList()
         << QApplication::translate("SettingModalDialog", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingModalDialog", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingModalDialog", "3", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class SettingModalDialog: public Ui_SettingModalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGMODALDIALOG_H
