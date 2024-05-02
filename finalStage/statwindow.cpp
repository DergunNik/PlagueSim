#include "statwindow.h"
#include "ui_statwindow.h"

StatWindow::StatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StatWindow)
{
    ui->setupUi(this);
}

StatWindow::StatWindow(Statistics *statistics, CityManager* manager, QWidget *parent) :
    StatWindow(parent)
{
    float t = BASIC_X_AXIS_VALUE;
    MovingAverage<CitySituation> makeAverage(3);

    for (uint8_t i = 0; i < 7; ++i) {
        _rawPoints[i] = new QLineSeries();
        _refPoints[i] = new QLineSeries();
    }

    for (auto now : statistics->history()) {
        _averagedData.push_back(makeAverage.addData(now));

        for (uint8_t i = 0; i < CHARTS_NUMBER; ++i) {

            if (i == HEALTHY_INDEX) {
                _rawPoints[i]->append(t, now.alive - now.infected);
                _refPoints[i]->append(t, _averagedData.back().alive - _averagedData.back().infected);
            } else {
                _rawPoints[i]->append(t, now[i]);
                _refPoints[i]->append(t, _averagedData.back()[i]);
            }
        }

        t += BASIC_X_AXIS_VALUE;
    }

    _rawChart = new QChart();
    _refChart = new QChart();
    _rawChart->setTitle("Чистые данные");
    _rawChart->setAnimationOptions(QChart::AllAnimations);
    _refChart->setTitle("Скользящие средние");
    _refChart->setAnimationOptions(QChart::AllAnimations);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Time");
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Value");
    QValueAxis *axisX1 = new QValueAxis();
    axisX->setTitleText("Time");
    QValueAxis *axisY1 = new QValueAxis();
    axisY->setTitleText("Value");

    _rawChart->addAxis(axisX, Qt::AlignBottom);
    _rawChart->addAxis(axisY, Qt::AlignLeft);
    _refChart->addAxis(axisX1, Qt::AlignBottom);
    _refChart->addAxis(axisY1, Qt::AlignLeft);

    for (uint8_t i = 0; i < CHARTS_NUMBER; ++i) {
        _rawChart->addSeries(_rawPoints[i]);
        _refChart->addSeries(_refPoints[i]);
    }

    _rawChart->createDefaultAxes();
    _refChart->createDefaultAxes();

    for (uint8_t i = 0; i < CHARTS_NUMBER; ++i) {
        _rawChart->addSeries(_rawPoints[i]);
        _refChart->addSeries(_refPoints[i]);
    }

    _rawView = new QChartView(this);
    _rawView->setChart(_rawChart);
    _rawView->show();
    _refView = new QChartView(this);
    _refView->setChart(_refChart);
    _refView->show();

    _layout = new QGridLayout();
    _layout->addWidget(ui->verticalLayoutWidget, 0, 0);
    _layout->addWidget(ui->groupBox, 0, 1);
    _layout->addWidget(_rawView, 1, 0, 1, 2);
    _layout->addWidget(_refView, 2, 0, 1, 2);
    ui->centralwidget->setLayout(_layout);
}

StatWindow::~StatWindow()
{
    delete ui;
    delete _refView;
    delete _rawView;
}

void StatWindow::on_aliveBoc_stateChanged(int arg1)
{
    if (ui->aliveBoc->isChecked()) {
        _rawPoints[1]->setVisible(true);
        _refPoints[1]->setVisible(true);
    } else {
        _rawPoints[1]->setVisible(false);
        _refPoints[1]->setVisible(false);
    }
}


void StatWindow::on_deadBox_stateChanged(int arg1)
{
    if (ui->deadBox->isChecked()) {
        _rawPoints[0]->setVisible(true);
        _refPoints[0]->setVisible(true);
    } else {
        _rawPoints[0]->setVisible(false);
        _refPoints[0]->setVisible(false);
    }
}


void StatWindow::on_healthyBox_stateChanged(int arg1)
{
    if (ui->healthyBox->isChecked()) {
        _rawPoints[5]->setVisible(true);
        _refPoints[5]->setVisible(true);
    } else {
        _rawPoints[5]->setVisible(false);
        _refPoints[5]->setVisible(false);
    }
}


void StatWindow::on_infectedBoc_stateChanged(int arg1)
{
    if (ui->infectedBoc->isChecked()) {
        _rawPoints[2]->setVisible(true);
        _refPoints[2]->setVisible(true);
    } else {
        _rawPoints[2]->setVisible(false);
        _refPoints[2]->setVisible(false);
    }
}


void StatWindow::on_symptBox_stateChanged(int arg1)
{
    if (ui->symptBox->isChecked()) {
        _rawPoints[3]->setVisible(true);
        _refPoints[3]->setVisible(true);
    } else {
        _rawPoints[3]->setVisible(false);
        _refPoints[3]->setVisible(false);
    }
}


void StatWindow::on_contBox_stateChanged(int arg1)
{
    if (ui->contBox->isChecked()) {
        _rawPoints[4]->setVisible(true);
        _refPoints[4]->setVisible(true);
    } else {
        _rawPoints[4]->setVisible(false);
        _refPoints[4]->setVisible(false);
    }
}


void StatWindow::on_immunityBox_stateChanged(int arg1)
{
    if (ui->immunityBox->isChecked()) {
        _rawPoints[6]->setVisible(true);
        _refPoints[6]->setVisible(true);
    } else {
        _rawPoints[6]->setVisible(false);
        _refPoints[6]->setVisible(false);
    }
}


void StatWindow::on_endBtn_clicked()
{
    QApplication::quit();
}


void StatWindow::on_resetBtn_clicked()
{
    emit reset();
}

