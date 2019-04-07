#include "sudogame.h"
#include "ui_sudogame.h"
#include"QVBoxLayout"
#include"QPushButton"

static QString str_hardclass[3]={"简单","中等","困难"};

sudogame::sudogame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sudogame)
{
    ui->setupUi(this);
    QPushButton * startgameBtn  = new QPushButton(this);
    QPushButton * submitAnswerBtn = new QPushButton(this);
    QMenu * difLevelBtn = new QMenu(this);
    QPushButton * solveBycnfSolverBtn = new QPushButton(this);

    //set layout
    QGridLayout *LOset = new QGridLayout();
    LOset->addWidget(startgameBtn, 0, 0, 1,1);
    LOset->addWidget(submitAnswerBtn, 0,1, 1,1);
    LOset->addWidget(difLevelBtn, 1,2, 1,1);
    LOset->addWidget(solveBycnfSolverBtn,0, 3, 1,1 );

    //add action to difficulty level menu
    QAction* level_1 = new QAction(difLevelBtn);
    QAction* level_2 = new QAction(difLevelBtn);
    QAction* level_3 = new QAction(difLevelBtn);
    level_1->setText(QObject::tr(("简单")));
    level_2->setText(QObject::tr(("中等")));
    level_3->setText(QObject::tr(("困难")));
    difLevelBtn->addAction((level_1));
    difLevelBtn->addAction((level_2));
    difLevelBtn->addAction((level_3));
    connect(level_1, SIGNAL(triggered()), this, SLOT(SetLevel_1));
    connect(level_2, SIGNAL(triggered()), this, SLOT(SetLevel_2));
    connect(level_3, SIGNAL(triggered()), this, SLOT(SetLevel_3));

}


sudogame::~sudogame()
{
    delete ui;
}

void sudogame::SetLevel_1(void){
    diflevel = 1;
}

void sudogame::SetLevel_2(void){
    diflevel = 2;
}

void sudogame::SetLevel_3(void){
    diflevel = 3;
}
