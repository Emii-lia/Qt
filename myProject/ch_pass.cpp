#include "ch_pass.h"
#include "ui_ch_pass.h"

ch_pass::ch_pass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ch_pass)
{
    ui->setupUi(this);
    setFixedSize(433,344);
}

ch_pass::~ch_pass()
{
    delete ui;
}

void ch_pass::on_cancel_clicked()
{
    hide();
}

void ch_pass::on_comfirm_clicked()
{
    openDB("/home/sweetie/QT_Project/Database/projetest.sqlite");

    QString current_pwd{""},new_pwd{""},conf_pwd{""},userId{""};

    QSqlQuery qry;

    current_pwd = ui->curr_pass->text();
    new_pwd = ui->new_pass->text();
    conf_pwd = ui->r_new_pass->text();

    qry.prepare("SELECT [IdReceptioniste],[password] FROM [receptionistes] WHERE [active] = 1");

    if(qry.exec()){
        while(qry.next()){
            userId = qry.value(0).toString();
            if(current_pwd != qry.value(1).toString())
            {
                QMessageBox::critical(this,"ERROR","Mpisoloky");
                closeDB();
                return;
            }
        }
    }else
    {

        QMessageBox::critical(this,"ERROR","Tsy mety le querry voalohany");
        qDebug()<<"Qry error :"<<qry.lastError().text();
        closeDB();
        return;
    }

    if(new_pwd != conf_pwd)
    {
        QMessageBox::critical(this,"ERROR","Tsy mitovy ny mot de passe");
        closeDB();
        return;
    }


    qry.prepare("UPDATE [receptionistes] SET [password] = \""+new_pwd+"\" WHERE [IdReceptioniste] = "+userId+";");
    if(qry.exec())
    {
        QMessageBox::information(this,"Succes","Password update successfuly");
        hide();
    }else
    {
        QMessageBox::critical(this,"ERROR","Tsy mety le querry");
    }
    closeDB();
    return;
}
