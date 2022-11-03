#include "liste_generale.h"
#include "ui_liste_generale.h"

/*____________________________________________*/

liste_generale::liste_generale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::liste_generale)
{
    ui->setupUi(this);
    setFixedSize(989,618);

    ui->L1->setEnabled(0);ui->L2->setEnabled(0);ui->L3->setEnabled(0);ui->M1->setEnabled(0);ui->M2->setEnabled(0);ui->D1->setEnabled(0);
    ui->paye->setEnabled(0);ui->partiel->setEnabled(0);ui->non_paye->setEnabled(0);

}

liste_generale::~liste_generale()
{
    delete ui;
}

void liste_generale::on_logout_clicked()
{
    hide();
}

void liste_generale::on_view_clicked()
{
    /*--------Opening the DB and DB for the student---------*/
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");

    //Composant of the request
    QString categories{""},filtreNiveau{""},filtrePayement{""};

    //To make a query , we'll use
    QSqlQuery *qry = new QSqlQuery();

    //To present your table, we need a view
    QSqlQueryModel *model = new QSqlQueryModel();


    if(db.isOpen())
    {
        /*************************DEBUT**********************************/

        /******************FILTRE SELON LE NIVEAU*******************/
                if(ui->L1->checkState() && ui->L2->checkState() && ui->L3->checkState() && ui->M1->checkState() && ui->M2->checkState() && ui->D1->checkState())
                {
                    filtreNiveau = "1";
                }
                else if(!ui->L1->checkState() && !ui->L2->checkState() && !ui->L3->checkState() && !ui->M1->checkState() && !ui->M2->checkState() && !ui->D1->checkState())
                {
                    QMessageBox::information(this,"ERROR","You must choose a level!!");
                    closeDB();
                    return;
                }
                else
                {
                    if(ui->L1->checkState())
                    {
                        if(filtreNiveau != "")
                            filtreNiveau += "OR";
                        filtreNiveau += " [niveau] = 'Licence 1' ";
                    }
                    if(ui->L2->checkState())
                    {
                        if(filtreNiveau != "")
                            filtreNiveau += "OR";
                        filtreNiveau += " [niveau] = 'Licence 2' ";
                    }
                    if(ui->L3->checkState())
                    {
                        if(filtreNiveau != "")
                            filtreNiveau += "OR";
                        filtreNiveau += " [niveau] = 'Licence 3' ";
                    }
                    if(ui->M1->checkState())
                    {
                        if(filtreNiveau != "")
                            filtreNiveau += "OR";
                        filtreNiveau += " [niveau] = 'Master 1' ";
                    }
                    if(ui->M2->checkState())
                    {
                        if(filtreNiveau != "")
                            filtreNiveau += "OR";
                        filtreNiveau += " [niveau] = 'Master 2' ";
                    }
                    if(ui->D1->checkState())
                    {
                        if(filtreNiveau != "")
                            filtreNiveau += "OR";
                        filtreNiveau += " [niveau] = 'Doctorant 1' ";
                    }
                }

                /******************FILTRE SELON LE STATUT FINANCIER*******************/
                if(ui->non_paye->checkState()&&ui->paye->checkState()&&ui->partiel->checkState())
                {
                    filtrePayement = '1';
                }
                else if(!ui->non_paye->checkState()&&!ui->paye->checkState()&&!ui->partiel->checkState())
                {
                    filtrePayement = '1';
                }
                else
                {
                    if(ui->non_paye->checkState())
                    {
                        if(filtrePayement != "")
                            filtrePayement += " OR ";
                        filtrePayement += " [Montant payer] IS NULL";
                    }
                    if(ui->paye->checkState())
                    {
                        if(filtrePayement != "")
                            filtrePayement += " OR ";
                        filtrePayement += " [Montant payer] = 422000";
                    }
                    if(ui->partiel->checkState())
                    {
                        if(filtrePayement != "")
                            filtrePayement += " OR ";
                        filtrePayement += " [Montant payer] < 422000";
                    }
                }

                //POUR FAIRE LA REQUETE
                qry->prepare("SELECT e.[identifiant],e.[nom],e.[prenom],e.[niveau],SUM(v.[montant]) AS 'Montant payer' FROM [etudiantest] e LEFT JOIN [versements] v ON v.[IdEtudiant] = e.[IdEtudiant] WHERE ("+filtreNiveau+") GROUP BY e.[IdEtudiant]  HAVING ("+filtrePayement+");");


                //VERIFICATION QU'IL N'Y A PAS D'ERREUR DANS LA REQUETE
                if(!qry->exec())
                {
                    QMessageBox::information(this,"ERROR","Not saved : " + qry->lastError().text());
                    return;
                }
                model->setQuery(*qry);
                ui->vue->setModel(model);
                setFiltre(filtreNiveau,filtrePayement);
        /***************************FIN*******************************/

    }
    else
    {
        QMessageBox::information(this,"FAILED","NOT CONNECTED :(");
    }

    closeDB();
    return;
}

/*-----Filter for liste_general,inscription,reinscription -----*/


void liste_generale::on_radioButton_listGen_clicked()
{
    //initialisation Niveau
    ui->L1->setChecked(0);ui->L2->setChecked(0);ui->L3->setChecked(0);ui->M1->setChecked(0);ui->M2->setChecked(0);ui->D1->setChecked(0);
    //initialisation payement
    ui->paye->setEnabled(1);ui->partiel->setEnabled(1);ui->non_paye->setEnabled(1);

    //L1 admis et redoublant
    ui->L1->setEnabled(1);ui->L2->setEnabled(1);ui->L3->setEnabled(1);ui->M1->setEnabled(1);ui->M2->setEnabled(1);ui->D1->setEnabled(1);
}

void liste_generale::on_radioButton_inscription_clicked()
{
    //initialisation
    ui->L1->setChecked(1);ui->L2->setChecked(0);ui->L3->setChecked(0);ui->M1->setChecked(0);ui->M2->setChecked(0);
    //initialisation payement
    ui->paye->setEnabled(1);ui->partiel->setEnabled(1);ui->non_paye->setEnabled(1);

    ui->L1->setEnabled(0);
    ui->L2->setEnabled(0);ui->L3->setEnabled(0);ui->M1->setEnabled(0);ui->M2->setEnabled(0);
}

void liste_generale::on_radioButton_reinscription_clicked()
{
    //initialisation
    ui->L1->setChecked(0);ui->L2->setChecked(0);ui->L3->setChecked(0);ui->M1->setChecked(0);ui->M2->setChecked(0);ui->D1->setChecked(0);
    //initialisation payement
    ui->paye->setEnabled(1);ui->partiel->setEnabled(1);ui->non_paye->setEnabled(1);

    //L1 redoublant
    ui->L1->setEnabled(1);ui->L2->setEnabled(1);ui->L3->setEnabled(1);ui->M1->setEnabled(1);ui->M2->setEnabled(1);ui->D1->setEnabled(1);
}



//Enregistrement de la VIEW en fichier txt
void liste_generale::on_save_clicked()
{
    QString fileName{""};
    fileName = ui->filename->text();
    if(fileName=="")
        fileName = "document";
        openDB("/home/sweetie/QT_Project/Database projetest.sqlite");
    QSqlQuery qry;
    //Recuperation des filtres, ici les filtres sont des attribut le notre fenetre(Voir liste_generale.h)
    qry.prepare("SELECT e.[identifiant],e.[nom],e.[prenom],e.[niveau],SUM(v.[montant]) AS 'Montant payer' FROM [etudiantest] e LEFT JOIN [versements] v ON v.[IdEtudiant] = e.[IdEtudiant] WHERE ("+qryNiv+") GROUP BY e.[IdEtudiant]  HAVING ("+qryPay+");");

    if(qry.exec())
    {
        //Nous avons besoin d'un fichier ou inscrire la VIEW
        QFile file("/home/sweetie/PROJET FIN ANNEE/Database"+fileName+".txt");
        //Pour pouvoir ecrire sur une nouvelle ligne
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)){
            bool flag = true;
            while(qry.next()){
                QTextStream stream(&file);
                if(flag)
                {
                    for(int i=0;i<qry.record().count();i++)
                    {
                        if(i!=qry.record().count()-1)
                            stream<<qry.record().fieldName(i)<<",";
                        else
                            stream<<qry.record().fieldName(i);
                    }
                    stream<<"\n";
                }
                flag = false;
                for(int i=0;i<qry.record().count();i++)
                {
                    //Ecriture
                    if(i!=qry.record().count()-1)
                        stream<<qry.value(i).toString()<<",";
                    else
                        stream<<qry.value(i).toString();
                }
                stream<<'\n';
            }
        }
        file.close();
    }
    else
    {
        QMessageBox::information(this,"ERROR","Not saved : " + qry.lastError().text());
    }
    closeDB();
}
