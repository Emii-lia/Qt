#ifndef PROFIL_H
#define PROFIL_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>

#include "ch_pass.h"

namespace Ui {
class profil;
}

class profil : public QDialog
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
    explicit profil(QWidget *parent = nullptr);
    ~profil();

private slots:
    void on_ch_pass_clicked();


    void on_ch_user_clicked();

    void on_visionner_clicked();

private:
    Ui::profil *ui;
   ch_pass *passwd;

};

#endif // PROFIL_H
