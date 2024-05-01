#ifndef WHO_H
#define WHO_H

#include <statistics.h>
#include <citymanager.h>
#include <news.h>

#include <QObject>
#include <QRandomGenerator>


const float REC_LEVEL = 0.01;
const float MASKS_LEVEL = 0.05;
const float MIN_CONT_LEVEL = 0.1;
const float VACCINE_LEVEL = 0.2;
const float ISOLATION_LEVEL = 0.3;
const float HALF_LEVEL = 0.5;
const float PRECISION = 1e-4;


class WHO : public QObject
{
    Q_OBJECT

private:
    bool _firstCase = false;
    bool _hands = false;
    bool _masks = false;
    bool _firstDeath = false;
    bool _minimalContacts = false;
    bool _vaccination = false;
    bool _selfIsolation = false;
    bool _hospitalIsFull = false;
    bool _halfIsInf = false;
    bool _halfIsDead = false;
    bool _everyIsInf = false;
    bool _end = false;
    bool _allDead = false;
    Statistics* _stat;
    CityManager* _cityManager;

public:
    explicit WHO(QObject *parent = nullptr);
    WHO(Statistics* stat, CityManager* cityManager, QObject *parent = nullptr);

    void checkState();

    void provideMasks();
    void provideMinimalContacts();
    void provideVaccination();
    void provideSelfIsolation();

    static void toHospital(Citizen& citizen, CityManager* cityManager);

signals:
    void news(QString newsText);
};

#endif // WHO_H
