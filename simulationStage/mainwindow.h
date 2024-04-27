#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ball.h>
#include <citymanager.h>
#include <cityvisualizer.h>
#include <districtvisualizer.h>
#include <statistics.h>
#include <who.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>
#include <QMainWindow>

#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


const uint REQUIRED_TICKS = 1500;
const uint8_t FPS = 30;
const uint8_t PERCENTS = 100;
const ushort BASIC_VELOCITY = 100;
const ushort DAY = 12;
const ushort HOUR = 60;
const ushort MAX_VALUE = 10;
const ushort MIN_VALUE = 1;


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    CityManager* _cityManager;
    CityVisualizer* _cityVisualizer;
    QGridLayout* _layout;
    QMap<QPair<ushort, ushort>, DistrictVisualizer*> _distrVis;
    QPair<ushort, ushort> _curDistr = {-1, -1};
    QTimer* _timer;
    Statistics _statistics;
    Ui::MainWindow *ui;
    WHO* _who;
    bool _isPaused = true;
    float _speed;
    float _tickCntr = 0;
    float _tickValue;
    uint _halfdaysCntr = 0;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(GenHandler&& generator, QWidget *parent = nullptr);
    ~MainWindow() override;

    Statistics* statistics();
    CityManager* cityManager();

public slots:
    void tick();
    void getNews(QString news);
    void nextLoop();
    void updateTime();
    void updateInfo();
    void mapSelected();
    void speedChanged();
    void endBtnClicked();
    void detrictSelected(ushort x, ushort y);
    void pauseStateChanged();

signals:
    void endSimulation();
};
#endif // MAINWINDOW_H
