#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <QMainWindow>

namespace Ui {
class sudokugame;
}

class sudokugame : public QMainWindow
{
    Q_OBJECT

public:
    explicit sudokugame(QWidget *parent = nullptr);
    ~sudokugame();

private:
    Ui::sudokugame *ui;
};

#endif // SUDOKUGAME_H
