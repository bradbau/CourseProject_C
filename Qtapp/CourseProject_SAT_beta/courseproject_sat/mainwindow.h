#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"sudoku.h"
#include"cnfparser.h"
#include"sudopart.h"

#include"savesudo.h"

class QStackedWidget;
class QFrame;
class QPushButton;
class SudoKu;
typedef std::vector<std::vector<bool> > vvbool;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent * );
    void resizeEvent(QResizeEvent* size);    
    void setworkDir(QString Dir);
    ~MainWindow();

private:

    void load(int );
    void save(int );


    bool checkwin();
    void beginGameClicked(int hard=0);
    void setButtonInit();

    void showwrong1(int i, int j);//same number
    void notshowwrong1(int i, int j);
    void showwrong2(int i, int j);//override the only number can be seen from other tab
    void notshowwrong2(int i, int j);
    void recoverwrong();
    void showAllWrong();

    QStackedWidget *m_widget;
    QStackedWidget *b_w;
    QPushButton ***b;
//    QPushButton **others;
    QPushButton **key;
    QWidget* widget;
    QFrame* widget2;
    Ui::MainWindow *ui;
    SudoKu *Game;
    vvbool clickable;
    vvint saved[5];
    std::set<std::pair<int,int> > wrong1;
    std::set<std::pair<int,int> > wrong2;
    std::set<std::pair<int,int> > save_wrong1[5];
    std::set<std::pair<int,int> > save_wrong2[5];
    QString workDir;

private slots:
    void b_buttonClicked();
    void b_SelectedHardClicked();
    void tablebuttonClicked();
    void keyboardclicked();
    void newGameClicked();

    void on_action_cnftransfer_triggered();
    void on_action_triggered();
    void on_action_solvebycnf_triggered();
};



#endif // MAINWINDOW_H
