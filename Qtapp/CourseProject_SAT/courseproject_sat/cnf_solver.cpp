

#include "ui_cnf_solver.h"
#include"cnf_solver.h"// 为啥我把它放ui_cnf_solver前面会报错？

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





void cnf_solver::on_pushBtn_opencnf_clicked()
{
    presentFile = QFileDialog::getOpenFileName(this, tr("打开cnf文件"),".", tr("data(*.cnf)"));
    if(presentFile.length() == 0) {
                   QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
           } else {
                   QMessageBox::information(NULL, tr("Path"), tr("You selected ") + presentFile);
           }
    QByteArray ba = presentFile.toLatin1();
    char * ch;
    ch=ba.data();
    phi = cnfStdLoad(ch);
    if(phi){
        QString cnfStr;
        cnfStr = Displaycnf(phi);
        ui->cnfBrowser->setText(cnfStr);
    }

}

void cnf_solver::on_pushBtn_solver_basic_clicked()
{
    if(presentFile.length() == 0){
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else{
        ui->resultviewer->setText(tr("正在求解公式"));
        QByteArray ba = presentFile.toLatin1();
        char * ch;
        ch=ba.data();
        if(CaseRunner_single(ch, DPLL_basic, "D:\__Learningmate\CourseProject\project\SATres_basic" )==OK){
            ui->resultviewer->setText(tr("求解成功"));
        }
    }
}
