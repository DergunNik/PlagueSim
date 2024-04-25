#include "ball.h"


Ball::Ball(QPointF pos, QPointF vel, float rad, Citizen* citizen) :
    _citizen(citizen), _vel(vel), _rad(rad)
{
    setPos(pos);
    _basicVel *= citizen->sociability();
    if (citizen->isInHospital()) {
        _basicVel = 0;
    }
}


QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}


QRectF Ball::boundingRect() const
{
    return QRectF(-_rad, -_rad, _rad * 2, _rad * 2);
}


void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::black));
    if (_citizen->isInfected() && !_citizen->hasSyptoms()) {
        painter->setBrush(QBrush(Qt::darkRed));
    } else if (_citizen->hasSyptoms()) {
        painter->setBrush(QBrush(Qt::red));
    }
    painter->setPen(QPen(Qt::black));
    if (_citizen->isContagious()) {
        painter->setPen(QPen(Qt::red));
    }

    painter->drawEllipse(-_rad, -_rad, _rad * 2, _rad * 2);
}


QPointF Ball::predictMove(float delta)
{
    return pos() + _vel * delta / MS_IN_SEC;
}


void Ball::move(float delta)
{
    for (auto now : scene()->collidingItems(this)) {
        if (dynamic_cast<Ball*>(now)) {
            collide(dynamic_cast<Ball*>(now));
        }
    }
    collide(_rect);

    _vel = normalize(_vel) * _basicVel;
    setPos(pos() + _vel * delta / MS_IN_SEC);
}


void Ball::collide(Ball* other)
{
    if (_vel.isNull()) {
        return;
    }

    QPointF n = other->pos() - pos();
    n = normalize(n);
    float dv = scalar(_vel, n);
    if (dv > 0) {
        _vel -= 2 * dv * n;
        other->_vel += 2 * dv * n;
    }

    if (!_citizen->isInfected() && other->_citizen->isContagious()) {
        _citizen->getInfected(other->_citizen->isWearingMask());
    } else if (!other->_citizen->isInfected() && _citizen->isContagious()) {
        other->_citizen->getInfected(_citizen->isWearingMask());
    }
}


void Ball::collide(QRectF rect)
{
    if (pos().y() > rect.bottom() && _vel.y() > 0) {
        _vel.ry() = -_vel.y();
    } else if (pos().y() < rect.top() && _vel.y() < 0) {
        _vel.ry() = -_vel.y();
    }
    if (pos().x() < rect.left() && _vel.x() < 0) {
        _vel.rx() = -_vel.x();
    } else if (pos().x() > rect.right() && _vel.x() > 0) {
        _vel.rx() = -_vel.x();
    }
}


float dist(QPointF a, QPointF b)
{
    return qSqrt(qPow(a.x() - b.x(), 2) + qPow(a.y() - b.y(), 2));
}


float scalar(QPointF a, QPointF b)
{
    return a.x() * b.x() + a.y() * b.y();
}


QPointF normalize(QPointF v)
{
    if(v.isNull()) {
        return v;
    }

    float m = dist(v, QPointF(0, 0));
    v.rx() /= m;
    v.ry() /= m;
    return v;
}


// getters and setters //************************************************************************************

QPointF Ball::vel() const
{
    return _vel;
}

void Ball::setVel(const QPointF &newVel)
{
    _vel = newVel;
}

QVector<Ball *> Ball::vec() const
{
    return _vec;
}

void Ball::setVec(const QVector<Ball *> &newVec)
{
    _vec = newVec;
}

QRectF Ball::rect() const
{
    return _rect;
}

void Ball::setRect(const QRectF &newRect)
{
    _rect = newRect;
}

float Ball::basicVel() const
{
    return _basicVel;
}

void Ball::setBasicVel(float newBasicVel)
{
    _basicVel = newBasicVel;
}

Citizen *Ball::citizen() const
{
    return _citizen;
}

void Ball::setCitizen(Citizen *newCitizen)
{
    _citizen = newCitizen;
}
