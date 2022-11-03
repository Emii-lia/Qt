#include "profil.h"
#include "ui_profil.h"
//#include "mainwindow.h"
//#include "menu.h"

profil::profil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profil)
{
    ui->setupUi(this);
    setFixedSize(804,513);

}

profil::~profil()
{
    delete ui;
}

void profil::on_ch_pass_clicked()
{
    passwd = new ch_pass(this);
    passwd->show();
}

void profil::on_ch_user_clicked()
{
    hide();


}

void profil::on_visionner_clicked()
{
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");

    QSqlQuery qry;
    qDebug()<<"Coucou";

    qry.prepare("SELECT [nom receptioniste],[prenom receptioniste],[niveau acces],[mail] FROM [receptionistes] WHERE [active] = 1 ;");

    if(qry.exec())
    {
        while(qry.next())
        {
            ui->profile_nom->setText(qry.value(0).toString());
            ui->profile_prenom->setText(qry.value(1).toString());
            ui->profile_niveau->setText(qry.value(2).toBool()?"Root":"Admin");
            ui->profil_email->setText(qry.value(3).toString());
        }
    }else
    {
        qDebug()<<"sql querry : "<<qry.lastError().text();
    }
    closeDB();
    return;
}
