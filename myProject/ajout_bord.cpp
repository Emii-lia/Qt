#include "ajout_bord.h"
#include "ui_ajout_bord.h"

ajout_bord::ajout_bord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajout_bord)
{
    ui->setupUi(this);
//    setFixedSize(600,400);

}

ajout_bord::~ajout_bord()
{
    delete ui;
}

void ajout_bord::on_pushButton_clicked()
{
    hide();
}

void ajout_bord::on_pushButton_3_clicked()
{
    hide();
}
