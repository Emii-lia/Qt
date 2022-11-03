#ifndef LISTE_GENERALE_H
#define LISTE_GENERALE_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>

namespace Ui {
class liste_generale;
}

class liste_generale : public QDialog
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
    //Creation de fonction pour recuperer la valeur des filtres et des requetes
    //Composant of the request
    QString qryNiv{""},qryPay{""};

    void setFiltre(QString valueNiv,QString valuePaye)
    {
        qryNiv = valueNiv;
        qryPay = valuePaye;
    }


public:
    explicit liste_generale(QWidget *parent = nullptr);
    ~liste_generale();

private slots:
    void on_logout_clicked();

    void on_view_clicked();

    void on_radioButton_inscription_clicked();

    void on_radioButton_reinscription_clicked();

    void on_radioButton_listGen_clicked();

    void on_save_clicked();

private:
    Ui::liste_generale *ui;

};

#endif // LISTE_GENERALE_H
