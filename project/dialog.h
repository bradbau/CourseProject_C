#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"cnfparser.h"
#include"mainwindow.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_pushButton_opencnf_clicked();

    void on_pushButton_playsudoku_clicked();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
