#include "sudokugame.h"
#include "ui_sudokugame.h"

sudokugame::sudokugame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sudokugame)
{
    ui->setupUi(this);
}

sudokugame::~sudokugame()
{
    delete ui;
}
