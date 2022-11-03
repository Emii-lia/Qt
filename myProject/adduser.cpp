#include "adduser.h"
#include "ui_adduser.h"

adduser::adduser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduser)
{
    ui->setupUi(this);
}

adduser::~adduser()
{
    delete ui;
}

void adduser::on_pushButton_clicked()
{
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");
    QSqlQuery qry;
    //Nom requis
    QString nom = ui->inp_nom->text();
    if(nom == ""){
        QMessageBox::critical(this,"Champ requis","Vous devez entrer un nom");
        return;
    }
    //Prenom optionel
    QString prenom = ui->inp_prenom->text();
    //Filtre l'adresse mail pour avoir une adresse valide(ex: contenir'@')
    QString mail = ui->inp_mail->text();
    if(mail == "" || mail.indexOf('@')==-1)
    {
        QMessageBox::critical(this,"Champ requis","Vous devez entrer une adresse mail valide");
        return;
    }

    QString niveau{userNiv};
    //option securite(char special et > 8 char)
    QString pwd = ui->inp_pwd->text();
    QString pseudo = ui->inp_psd->text();

    qry.prepare("INSERT INTO [receptionistes] ([nom receptioniste],[prenom receptioniste],[pseudo receptioniste],[password],[niveau acces],[active],[mail]) VALUES ('"+nom+"','"+prenom+"','"+pseudo+"','"+pwd+"',"+niveau+",0,'"+mail+"');");
    if(!qry.exec())
    {
        qDebug()<<qry.lastError().text();
        closeDB();
        return;
    }
    QString addUserAction = "Ajout de l'utilisateur " + pseudo;
    //Enregistrement de l'action dans l'historique
    addHistorique(addUserAction);

    closeDB();
    hide();
}

void adduser::on_Admin_clicked()
{
    userNiv = "0";
}

void adduser::on_Root_clicked()
{
    userNiv = "1";
}
