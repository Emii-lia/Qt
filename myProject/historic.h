#ifndef HISTORIC_H
#define HISTORIC_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>

namespace Ui {
class historic;
}

class historic : public QDialog
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
    explicit historic(QWidget *parent = nullptr);
    ~historic();

private slots:
    void on_pushButton_clicked();

    void on_visionner_btn_clicked();

private:
    Ui::historic *ui;
};

#endif // HISTORIC_H
