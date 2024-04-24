#ifndef GRAPHICSDISTRICTITEM_H
#define GRAPHICSDISTRICTITEM_H

#include <plaguebasics.h>

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class GraphicsDistrictItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    DistrictType _type;
    QPair<uint8_t, uint8_t> _pos = {-1, -1};
    float _infectedPercent = 0;
    ushort _radius;

    float calcPercent(const CitizensProportion& prop);

public:
    explicit GraphicsDistrictItem(const District& district, ushort radius);

    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void reset(const District& district);
    QPair<uint8_t, uint8_t> ID() const;

signals:
    void selected(ushort x, ushort y);
};

#endif // GRAPHICSDISTRICTITEM_H
