#ifndef REINSCRIPTION_H
#define REINSCRIPTION_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>

#include "adduser.h"
#include "rmuser.h"
#include "modifuser.h"

namespace Ui {
class reinscription;
}

class reinscription : public QDialog
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




public:
    explicit reinscription(QWidget *parent = nullptr);
    ~reinscription();

private slots:
    void on_logout_clicked();

    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_ajouter_clicked();

    void on_Afficher_clicked();

private:
    Ui::reinscription *ui;

    adduser *winAdd;
    rmuser *winRm;
    modifuser *winModif;
};

#endif // REINSCRIPTION_H
