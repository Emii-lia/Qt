#include "modifuser.h"
#include "ui_modifuser.h"

modifuser::modifuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifuser)
{
    ui->setupUi(this);
}

modifuser::~modifuser()
{
    delete ui;
}

void modifuser::on_pushButton_clicked()
{
    QString id = ui->inp_ID->text();
    QString nom{""},prenom{""},niveau{userNiv};
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");
    QSqlQuery qry;
    qry.prepare("SELECT [nom receptioniste],[prenom receptioniste] FROM [receptionistes] WHERE [IdReceptioniste] = "+ id +";");
    if(!qry.exec())
    {
        qDebug()<<"ERROR SQL : "<<qry.lastError().text();
        closeDB();
        return;
    }
    else
    {
        int i(0);
        while (qry.next())
        {
            i++;
            nom = qry.value(0).toString();
            prenom = qry.value(1).toString();
        }
        if(i == 1)
        {
            QMessageBox::StandardButton confirmation = QMessageBox::question(this,"Confirmation", "Voulez-vous vraiment modifier le niveau d'acces de l'utilisateur "+ nom +" "+prenom+"?", QMessageBox::Yes | QMessageBox::No);
            if(confirmation == QMessageBox::Yes){
                qry.prepare("UPDATE [receptionistes] SET [niveau acces] = "+ niveau +" WHERE [IdReceptioniste] = "+id+";");
                if(!qry.exec())
                {
                    qDebug()<<"ERROR SQL : "<<qry.lastError().text();
                    closeDB();
                    return;
                }
                QString modifUserAction = "Modification du niveau d'acces de l'utilisateur "+ nom + " "+prenom;
                addHistorique(modifUserAction);
            }
        }
        else
        {
            QMessageBox::information(this,"ERROR 404","User not found");
        }
    }
    closeDB();
    hide();
}

void modifuser::on_Admin_clicked()
{
    userNiv = "0";
}

void modifuser::on_Root_clicked()
{
    userNiv = "1";
}
