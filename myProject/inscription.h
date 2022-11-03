#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>

namespace Ui {
class inscription;
}

class inscription : public QDialog
{
    Q_OBJECT

public:
    //Creation de fonctions pour ouvrir et fermer les bases de donnees utilisees
    QSqlDatabase db;

    void closeDB()
    {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool openDB(QString PATH)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");

        db.setDatabaseName(PATH);
        db.open();
        if(!db.isOpen())
        {
            qDebug()<<"Failed to open the data base";
            return false;
        }
        else
        {
            qDebug()<<"Connection to database set";
            return true;
        }
    }
    int montanDue=0;
    void setMontant(int somme)
    {
        montanDue = somme;
    }

    bool echel = false;

    void setEchel(bool e)
    {
        echel = e;
    }

    QString idEtudiantDb{""};

    void setIdEtudiant(QString id)
    {
        idEtudiantDb = id;
    }

    int montPayer = 0;
    void setMontantPayer(int n)
    {
        montPayer = n;
    }

    //Fonction pour enregitrer les actions dans la base de donnee historique
    //Creation de fonctions pour enregistrer les actions dans l'historique
    void addHistorique(QString action)
    {
        QSqlQuery q;
        QString responsable{""};
        if(q.exec("SELECT [pseudo receptioniste] FROM [receptionistes] WHERE [active] = 1 ;"))
        {
            while(q.next())
            {
                responsable = q.value(0).toString();
            }
            if(q.exec("INSERT INTO [historique] ([date action],[heure action],[responsable],[action]) VALUES (date('now'),time('now'),\""+responsable+"\",\""+action+"\");"))
            {
                qDebug()<<"Enregistrement action reussit";
            }
            else
            {
                qDebug()<<"Enregistrement action error";
            }
        }
        else
            qDebug()<<"Failled to get receptioniste name";
    }

public:
    explicit inscription(QWidget *parent = nullptr);
    ~inscription();

private slots:
    void on_logout_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::inscription *ui;
};

#endif // INSCRIPTION_H
