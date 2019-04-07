
#include "ui_sudogame.h"
#include <QObject>
#include "sudogame.h"
#include"QVBoxLayout"
#include"QPushButton"
#include "sudopart.h"


static QString str_difficultLevel[3]={QObject::tr("简单"),QObject::tr("中等"),QObject::tr("困难")};
static int m_minsize = 550;
static QFont ft1("宋体",13);
static QFont ft2("Times New Roman",13);
static QFont ft3("Times New Roman",11);


sudogame::sudogame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sudogame)
{
    ui->setupUi(this);
    m_widget = new QStackedWidget(this);

    b_w = new QStackedWidget;
    QWidget *b_widget = new QWidget;
    QWidget *b_widget_select = new QWidget;
    b_w->addWidget( b_widget);
    b_w->addWidget( b_widget_select );
    b_w->setCurrentIndex(0);
    /*
    QString b_str[2]={"开始游戏","规则简介"};
    QVBoxLayout *b_layout = new QVBoxLayout(b_widget);
    b_layout->addStretch(1);
    for(int i=0; i<2 ;++i)
    {
        QPushButton *but=new QPushButton(b_str[i]);
        but->setFont(ft1);
        but->setMinimumSize(80,60);
        b_layout->addWidget(but);
        connect(but,SIGNAL(clicked(bool)),this,SLOT(b_buttonClicked()));
        b_layout->addStretch(1);
    }
//    b_layout->addStretch(1);
    b_layout->setMargin(180);
    m_widget->addWidget(b_w);
*/
    QVBoxLayout *b_sele_layout = new QVBoxLayout(b_widget_select);
    b_sele_layout->addStretch(1);
    for( int i=0 ; i<4 ; ++i)
    {
        QPushButton *s= new QPushButton(str_difficultLevel[i]);
        connect( s ,SIGNAL(clicked(bool)),this,SLOT(b_SelectedHardClicked()));
        s->setMinimumSize(80,60);
        b_sele_layout->addWidget(s);
        b_sele_layout->addStretch(1);
    }
    b_sele_layout->setMargin(180);

    QGridLayout* gl2 = new QGridLayout;
    key=new QPushButton*[10];
    QString a;
    for(int i=0;i<9;++i)
    {
        key[i]=new QPushButton(a.setNum(i+1));
        key[i]->setFont(ft3);
        gl2->addWidget(key[i],i/3,i%3,Qt::AlignCenter|Qt::AlignHCenter);
        key[i]->setMinimumSize(40,40);
        connect(key[i],SIGNAL(clicked(bool)),this,SLOT(keyboardclicked()));
    }
    key[9]=new QPushButton(tr("C"));
    QPalette pal;
    pal.setColor(QPalette::ButtonText,QColor("#ff0000"));
    key[9]->setPalette(pal);
    gl2->addWidget(key[9],3,1,Qt::AlignCenter|Qt::AlignHCenter);
    key[9]->setMinimumSize(40,40);
    key[9]->setFont(ft3);
    for( int i=0 ; i<3; ++i)
    {
        gl2->setRowStretch(i,1);
        gl2->setColumnStretch(i,1);
    }
    gl2->setRowStretch(3,1);
    connect(key[9],SIGNAL(clicked(bool)),this,SLOT(keyboardclicked()));

    widget = new QWidget();
    m_widget->addWidget(widget);
    this->setWindowTitle(tr("数独小游戏"));
    m_widget->setCurrentIndex(0);
    this->setCentralWidget(m_widget);


    widget2 = new QFrame(this);
    QGridLayout* gl = new QGridLayout(widget);
    b= new QPushButton**[9];
    for(int i=0 ;i<9 ;++i)
    {
        b[i]=new QPushButton*[9];
        for( int j=0;j<9;++j)
        {
            b[i][j]=new QPushButton;
            b[i][j]->setMinimumSize(40,40);
            b[i][j]->setFont(ft2);
            gl->addWidget(b[i][j],i,j);
            b[i][j]->setAccessibleName(QString::number(i*10+j));
            connect(b[i][j],SIGNAL(clicked()),this,SLOT(tablebuttonClicked()));
            b[i][j]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        }
    }
    gl->setMargin(50);
    gl->setVerticalSpacing(1);
    gl->setHorizontalSpacing(1);
    for(int i=0;i<9;++i)
    {
        gl->setColumnStretch(i,1);
        gl->setRowStretch(i,1);
    }
    this->setMinimumSize(m_minsize,m_minsize);

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

void sudogame::beginGameClicked(int difLevel){
    //delate the existed sudo
    sudo = generate_sudoku(difLevel);


}

