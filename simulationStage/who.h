#ifndef WHO_H
#define WHO_H

#include <statistics.h>

#include <QObject>
#include <QRandomGenerator>


const float REC_LEVEL = 0.01;
const float MASKS_LEVEL = 0.05;
const float MIN_CONT_LEVEL = 0.1;
const float VACCINE_LEVEL = 0.2;
const float ISOLATION_LEVEL = 0.3;
const float HALF_LEVEL = 0.5;
const float ONE_PRECISION = 1e-4;


class WHO : public QObject
{
    Q_OBJECT

private:
    bool _hands = false;
    bool _masks = false;
    bool _minimalContacts = false;
    bool _vaccination = false;
    bool _selfIsolation = false;
    bool _halfIsInf = false;
    bool _everyIsInf = false;
    Statistics* _stat;
    QVector<Citizen>* _citizens;

public:
    explicit WHO(QObject *parent = nullptr);
    WHO(Statistics* stat, QVector<Citizen>* citizens, QObject *parent = nullptr);

    void checkState();

    void provideMasks();
    void provideMinimalContacts();
    void provideVaccination();
    void provideSelfIsolation();


signals:
    void news(QString newsText);
};

#endif // WHO_H
