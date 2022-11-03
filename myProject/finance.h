#ifndef FINANCE_H
#define FINANCE_H

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

namespace Ui {
class finance;
}

class finance : public QDialog
{
    Q_OBJECT

public:
    explicit finance(QWidget *parent = nullptr);
    ~finance();

private slots:
    void on_retour_clicked();

    void on_view_clicked();

private:
    Ui::finance *ui;
};

#endif // FINANCE_H
