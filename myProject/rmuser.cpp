#include "rmuser.h"
#include "ui_rmuser.h"

rmuser::rmuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rmuser)
{
    ui->setupUi(this);
}

rmuser::~rmuser()
{
    delete ui;
}



void rmuser::on_pushButton_clicked()
{
    QString id = ui->inp_ID->text();
    QString nom{""},prenom{""};
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
            QMessageBox::StandardButton confirmation = QMessageBox::question(this,"Confirmation", "Voulez-vous vraiment supprimer l'utilisateur "+ nom +" "+prenom+"?", QMessageBox::Yes | QMessageBox::No);
            if(confirmation == QMessageBox::Yes){
                qry.prepare("DELETE FROM [receptionistes] WHERE [IdReceptioniste] = "+id+";");
                if(!qry.exec())
                {
                    qDebug()<<"ERROR SQL : "<<qry.lastError().text();
                    closeDB();
                    return;
                }
                QString rmUserAction = "Suppression de l'utilisateur "+nom+" "+prenom;
                addHistorique(rmUserAction);
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
