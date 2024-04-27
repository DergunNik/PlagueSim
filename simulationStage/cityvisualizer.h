#ifndef CITYVISUALIZER_H
#define CITYVISUALIZER_H

#include <citymanager.h>
#include <QGraphicsScene>
#include <graphicsdistrictitem.h>

#include <QWidget>


namespace Ui {
class CityVisualizer;
}


const ushort DISTRICT_RADIUS = 80;
const ushort DISTRICT_TAB = 10;


class CityVisualizer : public QWidget
{
    Q_OBJECT

private:
    Ui::CityVisualizer *ui;
    QGraphicsScene* _scene;
    uint _size;

public:
    explicit CityVisualizer(QWidget *parent = nullptr);
    explicit CityVisualizer(CityManager* cManager, QWidget *parent = nullptr);
    ~CityVisualizer() override;

    void reset(CityManager* cManager);
    void setDay(bool isDay);

private slots:
    void selectedItem(ushort x, ushort y);

signals:
    void selectedDistrict(ushort x, ushort y);
};

#endif // CITYVISUALIZER_H
