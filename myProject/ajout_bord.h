#ifndef AJOUT_BORD_H
#define AJOUT_BORD_H

#include <QDialog>

namespace Ui {
class ajout_bord;
}

class ajout_bord : public QDialog
{
    Q_OBJECT

public:
    explicit ajout_bord(QWidget *parent = nullptr);
    ~ajout_bord();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ajout_bord *ui;
};

#endif // AJOUT_BORD_H
