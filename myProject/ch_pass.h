#ifndef CH_PASS_H
#define CH_PASS_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>

namespace Ui {
class ch_pass;
}

class ch_pass : public QDialog
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
    explicit ch_pass(QWidget *parent = nullptr);
    ~ch_pass();

private slots:
    void on_cancel_clicked();

    void on_comfirm_clicked();

private:
    Ui::ch_pass *ui;
};

#endif // CH_PASS_H
