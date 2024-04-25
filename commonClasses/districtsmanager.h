#ifndef DISTRICTSMANAGER_H
#define DISTRICTSMANAGER_H

#include <plaguebasics.h>

#include <QRandomGenerator>
#include <QVector>


const float WORK_PERCENT_FOR_WORK = 0.7;
const float HOSPITAL_PERCENT_FOR_WORK = 0.01;

class DistrictsManager
{
private:
    QVector<District> _homes = {};
    QVector<District> _works = {};
    QVector<District> _recreations = {};
    QVector<District> _hospitals = {};

public:
    DistrictsManager() = default;
    explicit DistrictsManager(QVector<District> commonVect);

    District* getRandomDistrict();
    District* getRandomHome();
    District* getRandomWork();
    District *getRandomHospital();
    District* getRandomForWork();
    District* getRandomRecreation();
    QVector<District*> getAllDistricts();
};

#endif // DISTRICTSMANAGER_H
