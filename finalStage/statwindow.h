#ifndef STATWINDOW_H
#define STATWINDOW_H

#include <statistics.h>
#include <citymanager.h>
#include <movingaverage.h>

#include <QMainWindow>
#include <QtCharts>


namespace Ui {
class StatWindow;
}


const uint8_t CHARTS_NUMBER = 7;
const uint8_t HEALTHY_INDEX = 5;
const float BASIC_X_AXIS_VALUE = 0.5;


class StatWindow : public QMainWindow
{
    Q_OBJECT

private:
    QChart* _rawChart;
    QChart* _refChart;
    QChartView* _rawView;
    QChartView* _refView;
    QGridLayout* _layout;
    QVector<CitySituation> _averagedData;
    Ui::StatWindow *ui;
    std::array<QLineSeries*, 7> _rawPoints;
    std::array<QLineSeries*, 7> _refPoints;

public:
    explicit StatWindow(QWidget *parent = nullptr);
    explicit StatWindow(Statistics* statistics, CityManager* manager, QWidget *parent = nullptr);
    ~StatWindow() override;

private slots:
    void on_aliveBoc_stateChanged(int arg1);
    void on_deadBox_stateChanged(int arg1);
    void on_healthyBox_stateChanged(int arg1);
    void on_infectedBoc_stateChanged(int arg1);
    void on_symptBox_stateChanged(int arg1);
    void on_contBox_stateChanged(int arg1);
    void on_immunityBox_stateChanged(int arg1);
    void on_endBtn_clicked();
    void on_resetBtn_clicked();

signals:
    void reset();

};

#endif // STATWINDOW_H
