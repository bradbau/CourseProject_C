#ifndef SUDOGAME_H
#define SUDOGAME_H

#include"sudopart.h"
#include <QMainWindow>

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

private:
    Ui::sudogame *ui;
    sudomatptr sudo;
    int diflevel = 2;//难度等级：1 2 3

};

#endif // SUDOGAME_H
