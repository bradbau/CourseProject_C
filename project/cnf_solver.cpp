#include "cnf_solver.h"
#include "ui_cnf_solver.h"

cnf_solver::cnf_solver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cnf_solver)
{
    ui->setupUi(this);
}

cnf_solver::~cnf_solver()
{
    delete ui;
}
