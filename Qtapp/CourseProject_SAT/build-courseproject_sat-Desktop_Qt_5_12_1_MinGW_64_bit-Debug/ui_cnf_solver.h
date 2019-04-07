/********************************************************************************
** Form generated from reading UI file 'cnf_solver.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CNF_SOLVER_H
#define UI_CNF_SOLVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_cnf_solver
{
public:
    QPushButton *pushBtn_opencnf;
    QPushButton *pushBtn_solver_basic;
    QFrame *line;
    QFrame *line_2;
    QLabel *label;
    QPushButton *pushBtn_solver_v1;
    QTextBrowser *cnfBrowser;
    QLabel *label_2;
    QTextBrowser *resultviewer;
    QLabel *label_3;

    void setupUi(QDialog *cnf_solver)
    {
        if (cnf_solver->objectName().isEmpty())
            cnf_solver->setObjectName(QString::fromUtf8("cnf_solver"));
        cnf_solver->resize(490, 392);
        cnf_solver->setMinimumSize(QSize(400, 300));
        pushBtn_opencnf = new QPushButton(cnf_solver);
        pushBtn_opencnf->setObjectName(QString::fromUtf8("pushBtn_opencnf"));
        pushBtn_opencnf->setGeometry(QRect(10, 20, 101, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Arabic"));
        font.setPointSize(10);
        pushBtn_opencnf->setFont(font);
        pushBtn_solver_basic = new QPushButton(cnf_solver);
        pushBtn_solver_basic->setObjectName(QString::fromUtf8("pushBtn_solver_basic"));
        pushBtn_solver_basic->setGeometry(QRect(20, 110, 91, 31));
        pushBtn_solver_basic->setFont(font);
        line = new QFrame(cnf_solver);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 70, 131, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(cnf_solver);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(110, 0, 41, 391));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label = new QLabel(cnf_solver);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 80, 51, 31));
        QFont font1;
        font1.setPointSize(9);
        label->setFont(font1);
        pushBtn_solver_v1 = new QPushButton(cnf_solver);
        pushBtn_solver_v1->setObjectName(QString::fromUtf8("pushBtn_solver_v1"));
        pushBtn_solver_v1->setGeometry(QRect(20, 170, 91, 31));
        QFont font2;
        font2.setPointSize(10);
        pushBtn_solver_v1->setFont(font2);
        cnfBrowser = new QTextBrowser(cnf_solver);
        cnfBrowser->setObjectName(QString::fromUtf8("cnfBrowser"));
        cnfBrowser->setGeometry(QRect(140, 30, 301, 101));
        label_2 = new QLabel(cnf_solver);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 10, 81, 18));
        label_2->setFont(font1);
        resultviewer = new QTextBrowser(cnf_solver);
        resultviewer->setObjectName(QString::fromUtf8("resultviewer"));
        resultviewer->setGeometry(QRect(150, 190, 311, 151));
        label_3 = new QLabel(cnf_solver);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 150, 61, 31));
        label_3->setFont(font1);

        retranslateUi(cnf_solver);

        QMetaObject::connectSlotsByName(cnf_solver);
    } // setupUi

    void retranslateUi(QDialog *cnf_solver)
    {
        cnf_solver->setWindowTitle(QApplication::translate("cnf_solver", "Dialog", nullptr));
        pushBtn_opencnf->setText(QApplication::translate("cnf_solver", "\346\211\223\345\274\200.cnf\346\226\207\344\273\266", nullptr));
        pushBtn_solver_basic->setText(QApplication::translate("cnf_solver", "\345\237\272\346\234\254\347\211\210", nullptr));
        label->setText(QApplication::translate("cnf_solver", "\346\261\202\350\247\243\345\231\250", nullptr));
        pushBtn_solver_v1->setText(QApplication::translate("cnf_solver", "\344\274\230\345\214\226\347\211\210\346\234\2541", nullptr));
        label_2->setText(QApplication::translate("cnf_solver", "\345\205\254\345\274\217\345\206\205\345\256\271", nullptr));
        label_3->setText(QApplication::translate("cnf_solver", "\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cnf_solver: public Ui_cnf_solver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CNF_SOLVER_H
