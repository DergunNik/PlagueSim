#ifndef DISTRICTVISUALIZER_H
#define DISTRICTVISUALIZER_H

#include <ball.h>
#include <QGraphicsScene>
#include <graphicsdistrictitem.h>

#include <QWidget>


namespace Ui {
class DistrictVisualizer;
}


const ushort CITIZEN_RADIUS = 10;
const ushort CITIZEN_TAB = 10;
const ushort HOME_RADIUS = 30;
const ushort HOME_TAB = 30;
const ushort SCENE_WIDTH = 1020;
const ushort SCENE_HEIGHT = 670;
const ushort SCENE_TAB = 10;
const ushort BASE_TAB = SCENE_TAB + CITIZEN_TAB;
const float NULL_PRECISION = 1e-6;
const float DELTA = 2.0F;

class DistrictVisualizer : public QWidget
{
    Q_OBJECT

private:
    District* _district;
    ushort _districtWidth;
    ushort _districtHeight;
    QGraphicsScene* _scene;
    Ui::DistrictVisualizer *ui;

public:
    explicit DistrictVisualizer(QWidget *parent = nullptr);
    explicit DistrictVisualizer(District* district, QWidget *parent = nullptr);
    ~DistrictVisualizer() override;

    QPointF randVect();
    void moveAll(ushort _speedMult);
    void reset(District* district);
    void update();
    void updateInfo();

public slots:
    void backBtnClicked();

signals:
    void backToMap();
};

#endif // DISTRICTVISUALIZER_H
