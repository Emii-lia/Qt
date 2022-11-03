#ifndef AJOUT_ECHEL_H
#define AJOUT_ECHEL_H

#include <QDialog>

namespace Ui {
class ajout_echel;
}

class ajout_echel : public QDialog
{
    Q_OBJECT

public:
    explicit ajout_echel(QWidget *parent = nullptr);
    ~ajout_echel();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::ajout_echel *ui;
};

#endif // AJOUT_ECHEL_H
