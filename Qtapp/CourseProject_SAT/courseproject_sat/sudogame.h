#ifndef SUDOGAME_H
#define SUDOGAME_H

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
#include <QMainWindow>
#include <QObject>

#include"sudopart.h"


namespace Ui {
class sudogame;
}

class sudogame : public QMainWindow
{
    Q_OBJECT

public:
    explicit sudogame(QWidget *parent = nullptr);


    void SetLevel_1(void);
    void SetLevel_2(void);
    void SetLevel_3(void);
    ~sudogame();

    void beginGameClicked(int difLevel);

private:
    Ui::sudogame *ui;
    sudomatptr sudo;
    int diflevel = 2;//难度等级：1 2 3


    QStackedWidget *m_widget;
    QStackedWidget *b_w;
    QPushButton ***b;
//    QPushButton **others;
    QPushButton **key;
    QWidget* widget;
    QFrame* widget2;
};

#endif // SUDOGAME_H
