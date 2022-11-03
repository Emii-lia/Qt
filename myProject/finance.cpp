#include "finance.h"
#include "ui_finance.h"
#include "menu.h"

finance::finance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finance)
{
    ui->setupUi(this);
//    this->showFullScreen();

    QPieSeries *series = new QPieSeries();

    series->append("Somme restant", 40);
    series->append("Somme recu", 60);

    QPieSlice *slice_1 = series->slices().at(0);
    slice_1->setLabelVisible(true);
    slice_1->setPen(QPen(Qt::darkRed, 2));
    slice_1->setBrush(Qt::red);

    QPieSlice *slice_2 = series->slices().at(1);
    slice_2->setLabelVisible(true);
    slice_2->setPen(QPen(Qt::darkGreen, 2));
    slice_2->setBrush(Qt::green);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTitle("Pie chart finance");

    QChartView *chartview = new QChartView(chart);
    chartview->setParent(ui->verticalFrame);

}

finance::~finance()
{
    delete ui;
}

void finance::on_retour_clicked()
{
    hide();
    menu myMenu;
    myMenu.setModal(true);
    myMenu.exec();
    myMenu.show();
}

void finance::on_view_clicked()
{

}
