#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(989,618);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    hide();
}

void Dialog::on_pushButton_2_clicked()
{

}

void Dialog::on_ajouter_btn_clicked()
{
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");

    QString dateFinale = "2022-11-30";

    QSqlQuery qry;

    bool hasAutorisation = false;

    //***************AJOUT DANS LA LISTE*****************
    //Verification du numero de matricule
    QString IdEtudiantDB{""};//
    QString identifiant{""};//No matricule ou No concours
    identifiant = ui->ajout_inp_id->text();


    //Recuperation de IdEtudiant
    if(qry.exec("SELECT [IdEtudiant] FROM [etudiantest] WHERE [identifiant] ="+identifiant+";"))
    {
        int i=0;
        while (qry.next())
        {
            ++i;
            if(i==1)
            {
                IdEtudiantDB = qry.value(0).toString();
            }
        }
        if(i!=1)
        {
            QMessageBox::critical(this,"ERROR","Etudiant introuvable.\nVeillez verifier son numero de matricule");
            closeDB();
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"ERROR","SQL ISSUE :"+qry.lastError().text());
        closeDB();
        return;
    }

    //Verification que l'etudiant n'est pas deja dans la liste
    if(qry.exec("SELECT * FROM [echellonements] WHERE [IdEtudiant] = "+IdEtudiantDB+";"))
    {
        int j = 0;
        while(qry.next())
        {
            ++j;
        }
        if(j==1)
        {
            QMessageBox::critical(this,"ERROR","L'etudiant est deja present dans la liste de demande");
            closeDB();
            return;
        }
    }

    //Verification de l'autorisation de l'etudiant
    if(qry.exec("SELECT [autorisation] FROM [etudiantest] WHERE [IdEtudiant] ="+IdEtudiantDB+";"))
    {

        while(qry.next())
        {
            hasAutorisation = qry.value(0).toBool();
        }
    }

    if(hasAutorisation)
    {
        QMessageBox::information(this,"ERROR","Cet etudiant a deja recu l'accord d'echellonement");
        closeDB();
        return;
    }

    //Verification de la date
    QString dateDemande{""};
    dateDemande = ui->ajout_inp_date->date().toString("yyyy-MM-dd");//Nous devons limiter la date [intervalle]
    if(dateDemande>dateFinale)
    {
        QMessageBox::critical(this,"ERROR","La date butoire a ete depasse.\nEnregistrement de la demande impossible");
        closeDB();
        return;
    }

    //Verification de la pieces justicative(unique,longueur 6 caractere et chiffre)//Ces criteres sont des exemples
    bool isInt = true,isUnique = true;
    QString piecesJustivicative = ui->ajout_inp_piece->text();
    piecesJustivicative.toInt(&isInt);
    //Verification que le justificatif est unique
    if(qry.exec("SELECT [piece justificative] FROM [echellonements];"))
    {
        while (qry.next())
        {
            if(piecesJustivicative == qry.value(0).toString())
            {
                isUnique = false;
                break;
            }
        }
    }

    //Verification finale
    if(piecesJustivicative.length() == 6 && isInt && isUnique)
    {
        qry.prepare("INSERT INTO [echellonements] ([date echellonement],[piece justificative],[IdEtudiant]) VALUES ('"+dateDemande+"','"+piecesJustivicative+"',"+IdEtudiantDB+");");
        if(!qry.exec())
        {
            qDebug()<<"query issue : "<<qry.lastError().text();
            closeDB();
            return;
        }
        QMessageBox::information(this,"Action accomplie","Etudiant ajoute avec succes");
        QString ajListEchel = "Ajout a la liste d'echellonement de l'etudiant no matricule : " +identifiant;
        addHistorique(ajListEchel);

    }
    else
    {
        QMessageBox::critical(this,"ERROR","Pieces justificative invalide ou deja presente");
        closeDB();
        return;
    }
    closeDB();
}

void Dialog::on_autorisation_btn_clicked()
{
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");

    QSqlQuery qry;

    //***************AJOUT DANS LA LISTE*****************
    //Verification du numero de matricule
    QString IdEtudiantDB{""};//
    QString identifiant{""};//No matricule ou No concours
    identifiant = ui->autorisation_inp_id->text();


    //Recuperation de IdEtudiant
    if(qry.exec("SELECT [IdEtudiant] FROM [etudiantest] WHERE [identifiant] ="+identifiant+";"))
    {
        int i=0;
        while (qry.next())
        {
            ++i;
            if(i==1)
            {
                IdEtudiantDB = qry.value(0).toString();
            }
        }
        if(i!=1)
        {
            QMessageBox::critical(this,"ERROR","Etudiant introuvable.\nVeillez verifier son numero de matricule");
            closeDB();
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,"ERROR","SQL ISSUE :"+qry.lastError().text());
        closeDB();
        return;
    }
    //Verification que l'etudiant n'est pas deja dans la liste
    //Liste echellonement = liste de demande
    bool hasAutorisation = false;
    if(qry.exec("SELECT * FROM [echellonements] WHERE [IdEtudiant] = "+IdEtudiantDB+";"))
    {
        int j = 0;
        while(qry.next())
        {
            ++j;
        }
        if(j==1)
        {
            if(qry.exec("SELECT [autorisation] FROM [etudiantest] WHERE [IdEtudiant] ="+IdEtudiantDB+";"))
            {

                while(qry.next())
                {
                    hasAutorisation = qry.value(0).toBool();
                }
            }

            if(hasAutorisation)
            {
                QMessageBox::information(this,"ERROR","Cet etudiant a deja recu l'accord d'echellonement");
                closeDB();
                return;
            }
            else
            {
                if(qry.exec("UPDATE [etudiantest] SET [autorisation] = 1 WHERE [IdEtudiant] = "+IdEtudiantDB+" ;"))
                {
                    qry.prepare("DELETE FROM [echellonements]  WHERE [IdEtudiant] = "+IdEtudiantDB+" ;");
                    if(qry.exec())
                    {
                        QMessageBox::information(this,"Action accomplie","Etudiant autoriser");
                        QString accEchel = "Accord echellonement de l'etudiant no matricule : " + identifiant;
                        addHistorique(accEchel);
                    }
                }
            }
        }
        else
        {
            QMessageBox::information(this,"ERROR","L'etudiant n'est pas present dans la liste\nVeuillez l'ajouter.");
        }
    }

    closeDB();
}

void Dialog::on_vision_liste_btn_clicked()
{
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");

    //To make a query , we'll use
    QSqlQuery *q = new QSqlQuery();

    //To present your table, we need a view
    QSqlQueryModel *model = new QSqlQueryModel();

    q->prepare("SELECT e.[identifiant],e.[nom],e.[prenom],e.[niveau],ec.[date echellonement],ec.[piece justificative] FROM [echellonements] ec INNER JOIN [etudiantest] e ON ec.[IdEtudiant] = e.[IdEtudiant];");
    if(q->exec()){
        model->setQuery(*q);
        ui->vue->setModel(model);
    }
    else
    {
        qDebug()<<"sql errrror : "<<q->lastError().text();
    }

}
