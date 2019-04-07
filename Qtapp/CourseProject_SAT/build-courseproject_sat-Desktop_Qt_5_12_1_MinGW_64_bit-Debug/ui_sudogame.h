/********************************************************************************
** Form generated from reading UI file 'sudogame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUDOGAME_H
#define UI_SUDOGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sudogame
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sudogame)
    {
        if (sudogame->objectName().isEmpty())
            sudogame->setObjectName(QString::fromUtf8("sudogame"));
        sudogame->resize(800, 600);
        centralwidget = new QWidget(sudogame);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sudogame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sudogame);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        sudogame->setMenuBar(menubar);
        statusbar = new QStatusBar(sudogame);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        sudogame->setStatusBar(statusbar);

        retranslateUi(sudogame);

        QMetaObject::connectSlotsByName(sudogame);
    } // setupUi

    void retranslateUi(QMainWindow *sudogame)
    {
        sudogame->setWindowTitle(QApplication::translate("sudogame", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sudogame: public Ui_sudogame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUDOGAME_H
