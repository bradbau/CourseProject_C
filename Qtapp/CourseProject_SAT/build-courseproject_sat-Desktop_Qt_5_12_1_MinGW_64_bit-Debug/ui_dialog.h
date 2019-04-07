/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pushButton_opencnf;
    QPushButton *pushButton_playsudoku;
    QPushButton *pushButton_setworkDir;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        pushButton_opencnf = new QPushButton(Dialog);
        pushButton_opencnf->setObjectName(QString::fromUtf8("pushButton_opencnf"));
        pushButton_opencnf->setGeometry(QRect(120, 60, 120, 31));
        pushButton_playsudoku = new QPushButton(Dialog);
        pushButton_playsudoku->setObjectName(QString::fromUtf8("pushButton_playsudoku"));
        pushButton_playsudoku->setGeometry(QRect(120, 120, 120, 31));
        pushButton_setworkDir = new QPushButton(Dialog);
        pushButton_setworkDir->setObjectName(QString::fromUtf8("pushButton_setworkDir"));
        pushButton_setworkDir->setGeometry(QRect(120, 180, 121, 31));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\350\257\276\347\250\213\350\256\276\350\256\241\346\216\247\345\210\266\345\217\260", nullptr));
        pushButton_opencnf->setText(QApplication::translate("Dialog", "cnf\345\205\254\345\274\217\346\261\202\350\247\243", nullptr));
        pushButton_playsudoku->setText(QApplication::translate("Dialog", "\346\225\260\347\213\254\346\270\270\346\210\217", nullptr));
        pushButton_setworkDir->setText(QApplication::translate("Dialog", "\345\267\245\344\275\234\347\233\256\345\275\225\350\256\276\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
