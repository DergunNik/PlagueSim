#include "graphicsdistrictitem.h"


GraphicsDistrictItem::GraphicsDistrictItem(const District& district, ushort radius) :
    _type(district.type()),
    _pos(district.pos()),
    _radius(radius)
{
    calcPercent(district.proportion());
}


QRectF GraphicsDistrictItem::boundingRect() const
{
    return QRectF(-_radius, -_radius, _radius * 2, _radius * 2);
}


void GraphicsDistrictItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color;
    color.setGreen(0);
    color.setRed(255 * _infectedPercent);
    color.setBlue(255 * (1 - _infectedPercent));
    painter->setBrush(QBrush(color));
    switch (_type) {
    case HOME:
        painter->drawRect(boundingRect());
        break;
    case WORK:
        painter->drawRect(-_radius / 2, -_radius, _radius, _radius * 2);
        break;
    default:
        painter->drawEllipse(boundingRect());
        break;
    }
}


void GraphicsDistrictItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    emit selected(_pos.first, _pos.second);
}


float GraphicsDistrictItem::calcPercent(const CitizensProportion &prop)
{
    auto tempProp = prop;
    auto tempSum = tempProp.asymptomaticallyInf + tempProp.explicitlyInf + tempProp.notInfected;
    if (tempSum == 0) {
        _infectedPercent = 0;
    } else {
        _infectedPercent = static_cast<float>(tempSum - tempProp.notInfected) / (tempSum);
    }
}


void GraphicsDistrictItem::reset(const District& district)
{
    _type = district.type();
    _pos = district.pos();
    calcPercent(district.proportion());
}


QPair<uint8_t, uint8_t> GraphicsDistrictItem::ID() const
{
    return _pos;
}
