
#include "dialog.h"
#include"sudogame.h"
#include "ui_dialog.h"
#include"cnf_solver.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_opencnf_clicked()
{

    cnf_solver * cnf_window = new cnf_solver(this);
    cnf_window->show();

}




void Dialog::on_pushButton_playsudoku_clicked()
{
    sudogame * gamewindow = new sudogame(this);
    gamewindow->show();
}
