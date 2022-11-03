#include "ajout_echel.h"
#include "ui_ajout_echel.h"

ajout_echel::ajout_echel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajout_echel)
{
    ui->setupUi(this);
//    setFixedSize(989,618);
    if(ui->lineEdit->text() == ""){
        ui->pushButton_3->setEnabled(false);
    }
}

ajout_echel::~ajout_echel()
{
    delete ui;
}

void ajout_echel::on_pushButton_2_clicked()
{
    hide();
}

void ajout_echel::on_pushButton_3_clicked()
{

}

void ajout_echel::on_lineEdit_textChanged(const QString &arg1)
{
    if(ui->lineEdit->text() == ""){
        ui->pushButton_3->setEnabled(false);
    }
    else {
        ui->pushButton_3->setEnabled(true);
    }
}
