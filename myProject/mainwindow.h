#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>

#include "menu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    menu *myMenu;
};

#endif // MAINWINDOW_H
