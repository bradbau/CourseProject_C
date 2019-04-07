#ifndef CNF_SOLVER_H
#define CNF_SOLVER_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"cnfparser.h"
#include"solver.h"
#include"display.h"


namespace Ui {
class cnf_solver;
}

class cnf_solver : public QDialog
{
    Q_OBJECT

public:
    explicit cnf_solver(QWidget *parent = nullptr);
    ~cnf_solver();

private slots:
    void on_pushBtn_opencnf_clicked();

    void on_pushBtn_solver_basic_clicked();


private:
    Ui::cnf_solver *ui;
    cnf_fmla* phi;
    QString presentFile;
};

#endif // CNF_SOLVER_H
