#include "graphicsdistrictitem.h"


GraphicsDistrictItem::GraphicsDistrictItem(const District& district, ushort radius) :
    _type(district.type()),
    _pos(district.pos()),
    _radius(radius)
{
    calcPercent(district.proportion());

    QString toolTip;
    switch (_type) {
    case HOME:
        toolTip = "Жилой район";
        break;
    case WORK:
        toolTip = "Рабочий район";
        break;
    case RECREATION:
        toolTip = "Разлекательный район";
        break;
    case HOSPITAL:
        toolTip = "Больница";
        break;
    }
    toolTip += ". ID: " + QString::number(_pos.first) + "/" + QString::number(_pos.second);
    setToolTip(toolTip);
}


QRectF GraphicsDistrictItem::boundingRect() const
{
    return QRectF(-_radius, -_radius, _radius * 2, _radius * 2);
}


void GraphicsDistrictItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (_infectedPercent > 2) {
        painter->setBrush(QBrush(Qt::white));
        painter->drawRect(boundingRect().x(),
                          boundingRect().y() + boundingRect().height() * (1 - STATUS_PERCENT_HEIGHT),
                          boundingRect().width(),
                          boundingRect().height() * STATUS_PERCENT_HEIGHT);
    } else {
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(boundingRect().x(),
                          boundingRect().y() + boundingRect().height() * (1 - STATUS_PERCENT_HEIGHT),
                          boundingRect().width() * _infectedPercent,
                          boundingRect().height() * STATUS_PERCENT_HEIGHT);
        painter->setBrush(QBrush(Qt::blue));
        painter->drawRect(boundingRect().x() + boundingRect().width() * _infectedPercent,
                          boundingRect().y() + boundingRect().height() * (1 - STATUS_PERCENT_HEIGHT),
                          boundingRect().width() * (1 - _infectedPercent),
                          boundingRect().height() * STATUS_PERCENT_HEIGHT);
    }

    QRect imageRect = QRect(-_radius, -_radius, _radius * 2, _radius * 2 * (1 - STATUS_PERCENT_HEIGHT));
    switch (_type) {
    case HOME:
        painter->drawPixmap(imageRect, QPixmap(":/homeS"));
        break;
    case WORK:
        painter->drawPixmap(imageRect, QPixmap(":/workS"));
        break;
    case HOSPITAL:
        painter->drawPixmap(imageRect, QPixmap(":/hospS"));
        break;
    default:
        painter->drawPixmap(imageRect, QPixmap(":/recrS"));
        break;
    }
}


void GraphicsDistrictItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    emit selected(_pos.first, _pos.second);
}


void GraphicsDistrictItem::calcPercent(const CitizensProportion &prop)
{
    if (prop.asymptomaticallyInf + prop.explicitlyInf + prop.notInfected == 0) {
        _infectedPercent = NO_PEOPLE_IN_DISTRICT;
        return;
    }

    auto tempSum = prop.asymptomaticallyInf + prop.explicitlyInf + prop.notInfected;
    if (tempSum == 0) {
        _infectedPercent = 0;
    } else {
        _infectedPercent = static_cast<float>(tempSum - prop.notInfected) / (tempSum);
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
