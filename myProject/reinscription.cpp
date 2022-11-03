#include "reinscription.h"
#include "ui_reinscription.h"

reinscription::reinscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reinscription)
{
    ui->setupUi(this);
    setFixedSize(711,495);

}

reinscription::~reinscription()
{
    delete ui;
}

void reinscription::on_logout_clicked()
{
    hide();
}

void reinscription::on_supprimer_clicked()
{
    winRm = new rmuser(this);
    winRm->show();
}

void reinscription::on_modifier_clicked()
{
    winModif = new modifuser(this);
    winModif->show();
}

void reinscription::on_ajouter_clicked()
{
    winAdd = new adduser(this);
    winAdd->show();
}

void reinscription::on_Afficher_clicked()
{
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");
    //QSqlQuery qry;

    //To make a query , we'll use
    QSqlQuery *qry = new QSqlQuery();
    qry->prepare("SELECT [IdReceptioniste],[nom receptioniste],[prenom receptioniste],[pseudo receptioniste],[mail],[niveau acces] FROM [receptionistes];");


    //To present your table, we need a view
    QSqlQueryModel *model = new QSqlQueryModel();
    if(!qry->exec())
    {
        QMessageBox::information(this,"ERROR","SQLITE" + qry->lastError().text());
    } else
    {
        model->setQuery(*qry);
        ui->vue->setModel(model);
    }

    closeDB();
}
