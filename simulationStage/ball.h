#ifndef BALL_H
#define BALL_H

#include <plaguebasics.h>

#include <QPoint>
#include <QObject>
#include <QGraphicsItem>
#include <QVector2D>
#include <QGraphicsScene>
#include <QPainter>


QPointF normalize(QPointF v);
float dist(QPointF a, QPointF b);
float scalar(QPointF a, QPointF b);


const float DEFAULT_VELOCITY = 10;
const ushort MS_IN_SEC = 1000;


class Ball : public QGraphicsItem
{
    Citizen* _citizen;
    QPointF _vel = {0, 0};
    QRectF _rect;
    QVector<Ball*> _vec = {};
    float _basicVel = DEFAULT_VELOCITY;
    float _rad = 0;

public:
    Ball() = default;
    Ball(QPointF pos, QPointF vel, float rad, Citizen* citizen);

    QPainterPath shape() const override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << _citizen->isInfected();
        qDebug() << _citizen->hasSyptoms();
        qDebug() << !_citizen->isAlive();
        qDebug() << _citizen->schedule().goTo(1);
        qDebug() << _citizen->schedule().work();
        qDebug() << _citizen->schedule().home();
        qDebug() << _citizen->schedule().goTo(1)->type();
        qDebug() << _citizen->schedule().work()->type();
        qDebug() << _citizen->schedule().home()->type();
        qDebug() << _citizen->immunity();
    }

    void collide(Ball* other);
    void collide(QRectF rect);

    QPointF predictMove(float delta);
    void move(float delta);

    QPointF vel() const;
    void setVel(const QPointF &newVel);
    QVector<Ball *> vec() const;
    void setVec(const QVector<Ball *> &newVec);
    QRectF rect() const;
    void setRect(const QRectF &newRect);
    float basicVel() const;
    void setBasicVel(float newBasicVel);
    Citizen *citizen() const;
    void setCitizen(Citizen *newCitizen);
};

#endif // BALL_H
