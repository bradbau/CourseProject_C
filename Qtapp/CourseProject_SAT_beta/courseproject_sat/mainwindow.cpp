
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTableView>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFontDialog>
#include <QFrame>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "sudopart.h"
#include "savesudo.h"
#include "cnfparser.h"
#include "display.h"


//cut

static const int saveloadNumber=5;

static QString str_hardclass[3]={"简单","中等","困难"};
static int levelnow=0;
static int helpTimes=3;
static bool begining=0;
static const int m_minsize=550;
static int x_t=0,y_t=0;//current index of 9*9
static QFont ft1("宋体",13);
static QFont ft2("Times New Roman",13);
static QFont ft3("Times New Roman",11);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),Game(nullptr)
{
    ui->setupUi(this);
    m_widget = new QStackedWidget;

    b_w = new QStackedWidget;
    QWidget *b_widget = new QWidget;
    QWidget *b_widget_select = new QWidget;
    b_w->addWidget( b_widget);
    b_w->addWidget( b_widget_select );
    b_w->setCurrentIndex(0);
    QString b_str[1]={"开始游戏"};
    QVBoxLayout *b_layout = new QVBoxLayout(b_widget);
    b_layout->addStretch(1);
    for(int i=0; i<1 ;++i)
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

    QVBoxLayout *b_sele_layout = new QVBoxLayout(b_widget_select);
    b_sele_layout->addStretch(1);
    for( int i=0 ; i<3 ; ++i)
    {
        QPushButton *s= new QPushButton(str_hardclass[i]);
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

    for(int i=0; i<3 ; ++i)
    {
        QAction *s= new QAction(str_hardclass[i]);
        ui->newGame->addAction(s);
        connect(s,SIGNAL(triggered(bool)),this,SLOT(newGameClicked()));
    }




    gl2->setSpacing(0);
    widget2->setMinimumSize(120,160);
    widget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    widget2->setLayout(gl2);
    widget2->close();

    setButtonInit();

    this->resize( m_minsize+50,m_minsize+50);

    int wid=this->width();
    int hei=this->height();
    //获取设备屏幕大小
    QRect screenRect = QApplication::desktop()->screenGeometry();
    int wid2=screenRect.width();
    int hei2=screenRect.height();
    if( screenRect.height() >1040 )
    {
        double scale=double(hei2)/1080;
        wid*=scale;
        hei*=scale;
    }
    this->setMaximumSize(  double(hei2)/hei*wid  , hei2   );
    this->setGeometry(     (wid2-wid)/3 ,(hei2-hei)/3  ,wid ,hei  );
}
void MainWindow::resizeEvent(QResizeEvent *)
{
    widget2->show();
    widget2->resize( 1.0*widget->width()/m_minsize*120  , 1.0*widget->height()/m_minsize*160  );
    int a=widget2->width()/3;
    int b=widget2->height()/4;
    for( int i=0 ; i<10 ;++i)
    {
        key[i]->resize(a,b);
    }
    key[9]->resize(a-2,b-2);
    widget2->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tablebuttonClicked()
{
    widget2->close();
    QPushButton*btn = qobject_cast<QPushButton*>(sender());
    int n=btn->accessibleName().toInt();
    int i=n/10,j=n%10;
    x_t=i;y_t=j;
    if(!clickable[x_t][y_t])
        return;
    QRect r1=btn->geometry();
    int xa=b[0][0]->width();
    int m1=  widget2->width() ;
    int m2=  widget2->height() ;
    if(  this->height()-r1.y()-10  > m2 )
        widget2->move( r1.x()-(m1-xa)/2-3 ,  r1.y()+10  );
    else
        widget2->move( r1.x()-(m1-xa)/2-3 ,  this->height()-m2 );
    widget2->show();
}

void MainWindow::keyboardclicked()
{
    widget2->close();

    if(b[x_t][y_t]->text()==("×"))
        return;

    QPushButton*btn = qobject_cast<QPushButton*>(sender());

    int num=btn->text().toInt();
    if(num)
    {
        b[x_t][y_t]->setText(QString::number(num));
        (*Game)[x_t][y_t]=num;
    }
    else
    {
        b[x_t][y_t]->setText("");
        (*Game)[x_t][y_t]=0;
    }
    recoverwrong();
    Game->check1(x_t,y_t,wrong1);
    Game->check2(x_t,y_t,wrong2);
    showAllWrong();
    if(checkwin())
    {

        QMessageBox::about(this, "",tr("恭喜你，解答正确！"));

    }
}


bool MainWindow::checkwin()
{
    if(wrong1.empty()&&wrong2.empty()&&Game->checkwin())
        return 1;
    return 0;
}

void MainWindow::setButtonInit()
{
//    static char a1[] =  "background-color: #A2B5CD;" ;
    static char a2[] =  "background-color: #ffffff;" ;
    for(int i=0 ;i<9 ;++i)
    {
        for( int j=0;j<9;++j)
        {
            b[i][j]->setStyleSheet(a2);
        }
    }
}


void MainWindow::newGameClicked()

{
    widget2->close();
    if( begining)
    {
        if (QMessageBox::No == QMessageBox::question(this,tr("新游戏？"),
                                                  tr("确认放弃当前游戏？"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes))
            return;
    }
    static QString str[3]={"简单","中等","困难"};
    QAction *btn = qobject_cast<QAction*>(sender());
    int i=0;
    for( ; i< 4 ; ++i)
    {
        if( str[i]==btn->text() )
            break;
    }
    levelnow=i;
    if( !begining)
    {
        begining=1;
        m_widget->setCurrentIndex(1);
    }
    beginGameClicked(i);
}




void MainWindow::paintEvent(QPaintEvent *)
{
    if(begining==1)
    {
        int bm=ui->menuBar->geometry().bottom();
        QPainter p(this);
        QPen ss;
        ss.setWidth(3);
        ss.setColor(Qt::red);
        p.setPen(ss);

        for( int i=3 ; i<8; i+=3)
        {
            int x1= (b[0][i]->geometry().left()+b[0][i-1]->geometry().right())/2;
            int y1= b[0][i]->geometry().top();
            int y2=b[8][i]->geometry().bottom();
            p.drawLine( x1+1 ,y1+2+bm,x1+1,y2+bm );
        }
        for( int i=3 ; i<8; i+=3)
        {
            int y1= (b[i][0]->geometry().top()+b[i-1][0]->geometry().bottom())/2;
            int x1= b[i][0]->geometry().left();
            int x2=b[i][8]->geometry().right();
            p.drawLine( x1+2 ,y1+1+bm,x2-2,y1+1+bm );
        }
    }
}





void MainWindow::beginGameClicked(int hard)
{
    delete Game;
    Game = new SudoKu(hard);
    SudoKu & game=*Game;
    clickable=vvbool (9,std::vector<bool>(9,1));

    QString a;
    for(int i=0;i<9;++i)
    {
        for(int j=0;j<9;++j)
        {
            b[i][j]->setStyleSheet("background-color: #ffffff;");
            if(game[i][j]!=0)
            {
                b[i][j]->setText(a.setNum(game[i][j]));
                b[i][j]->setStyleSheet("background-color: #A2B5CD;");
                clickable[i][j]=0;
            }
            else
                b[i][j]->setText("");
        }
    }
    recoverwrong();

}

void MainWindow::b_buttonClicked()
{
    static QString b_str[1]={"开始游戏"};
    QPushButton*btn = qobject_cast<QPushButton*>(sender());
    if(btn->text()==b_str[0])
    {
        b_w->setCurrentIndex(1);
    }

}
void MainWindow::b_SelectedHardClicked()
{
    QPushButton*btn = qobject_cast<QPushButton*>(sender());
    int i=0;
    for( ; i<3 ; ++i)
    {
        if(btn->text()==str_hardclass[i])
        {
            break;
        }
    }
    begining=1;
    m_widget->setCurrentIndex(1);
    beginGameClicked(i);
}

void MainWindow::showwrong1(int i, int j)
{
    static QPalette pal;
    pal.setColor(QPalette::ButtonText,QColor("#ff0000"));
    b[i][j]->setPalette(pal);
}
void MainWindow::notshowwrong1(int i, int j)
{
    static QPalette pal;
    pal.setColor(QPalette::ButtonText,QColor("#000000"));
    b[i][j]->setPalette(pal);
}

void MainWindow::showwrong2(int i, int j)
{
    QPalette pal;
    pal.setColor(QPalette::ButtonText,QColor("#ff0000"));
    b[i][j]->setPalette(pal);
    b[i][j]->setText("×");
}
void MainWindow::notshowwrong2(int i, int j)
{
    QPalette pal;
    pal.setColor(QPalette::ButtonText,QColor("#000000"));
    b[i][j]->setPalette(pal);
    b[i][j]->setText("");
}
void MainWindow::showAllWrong()
{
    if(!wrong1.empty())
    {
        for(const std::pair<int,int>&ss:wrong1)
        {
            showwrong1(ss.first,ss.second);
        }
    }
    if(!wrong2.empty())
    {
        for(const std::pair<int,int>&ss:wrong2)
        {
            showwrong2(ss.first,ss.second);
        }
    }
}

void MainWindow::recoverwrong()
{
    typedef std::set<std::pair<int,int> >::iterator it;
    for(it ss=wrong1.begin();ss!=wrong1.end(); )
    {
        if(!Game->haswrong((*ss).first,(*ss).second))
        {
            notshowwrong1((*ss).first,(*ss).second);
            wrong1.erase(ss++);
        }
        else
            ++ss;
    }
    for(it ss=wrong2.begin();ss!=wrong2.end(); )
    {
        if(!Game->haswrong2((*ss).first,(*ss).second))
        {
            notshowwrong2((*ss).first,(*ss).second);
            wrong2.erase(ss++);
        }
        else
            ++ss;
    }
}

void MainWindow::on_action_cnftransfer_triggered(){
    //turn sudoku into cnf formula and save to a file
    if(Game==nullptr){
        QMessageBox::information(this, "",tr("当前没有游戏"));
    }
    else{

    //1.vvnum to suodmatptr
        sudomatptr sudo;
        sudo= Game->sudotransfer();

        //2.sudomatptr to cnfstring infile
        if(sudo!=nullptr){
            QString filename;
            QWidget *qwidget = new QWidget(this);

            //problem
            filename = QFileDialog::getSaveFileName(qwidget,tr("选择文件保存地址"), workDir,".cnf");
            //QMessageBox::warning(NULL,"show path",filename);
            if(filename.length() !=0){
               // char * Fname;
                //Fname = (char *)malloc(128*sizeof(char));
                QByteArray Fname = filename.toLatin1();
                if(SaveSudoku2cnf(sudo, Fname.data())==OK){
                    QMessageBox::information(this, "",tr("保存成功"));
                }
                else{
                    QMessageBox::information(this, "",tr("保存失败"));
                }

            }
        }
    }

}


void MainWindow::on_action_triggered()
{

    QMessageBox::information(this, tr("关于本软件"), tr("华中科技大学计算机科学与技术学院课程设计\ncs1704贾子扬\nU201714634"));
}


void MainWindow::on_action_solvebycnf_triggered()
{
    if(Game==nullptr){
        QMessageBox::information(this, "",tr("当前没有游戏"));
    }
    else{


        QString filename = workDir + "sudtemp.cnf";
        QByteArray Fname = filename.toLatin1();
        sudomatptr sudo =  Game->sudotransfer();
        if(SaveSudoku2cnf(sudo, Fname.data())==OK){
            char * Res;
            cnf_fmla *phi = cnfStdLoad(Fname.data());
            int result = DPLL_improv_v1(phi);
            if(result==1){

                int i, j;
                for(i=0; i<9; ++i){
                    for(j=0; j<9; ++j){
                        if(sudo->boxitem[i][j].isempty){
                            int t;
                            for(t=0; t<9; ++t){
                                if(sudo->boxitem[i][j].possiblenum[t]){

                                    if(phi->literalValue[sudo->boxitem[i][j].Ltrlindex[t]-1]%4<=1){
                                        b[i][j]->setText(QString::number(t+1));
                                        (*Game)[i][j]=t+1;

                                    }
                                }
                            }
                        }
                    }
                }//end of circle
                if(checkwin())
                {
                    QMessageBox::about(this, "",tr("恭喜你，解答正确！"));

                }
            }
        }
    }
}

void MainWindow::setworkDir(QString Dir){
    workDir =  Dir;
}


