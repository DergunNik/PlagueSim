#ifndef GENERATIONS_H
#define GENERATIONS_H

#include <plaguebasics.h>
#include <districtsmanager.h>
#include <basicstructs.h>

#include <QRandomGenerator>
#include <QVector>
#include <QtMath>

const float RECREATION_PROBABILITY = 0.4;
const float WORK_PROBABILITY = 0.3;
const float MIN_FAMILY_PROBABILITY = 0.1;
const float MAX_BASIC_IMMUNITY = 0.5;
const float MIN_BASIC_SOCIABILITY = 0.3;
const float MAX_BASIC_HEALTH = 0.5;


class CityManager;


class GenHandler
{
private:
    StartSettings _settings;
    DistrictsManager _districtsManager;
    QVector<District> _districts = {};
    QVector<Citizen> _citizens = {};

    void extracted(int &districtCnt);
    void generateDistricts();
    void generateCitizens();
    void generateSchedules();

    DistrictType getDistrictType();
    Responsibility getResponsibility();

public:
    GenHandler() = default;
    explicit GenHandler(StartSettings settings);

    QVector<Citizen> citizens() const;
    DistrictsManager districtsManager() const;

    friend CityManager;
};

#endif // GENERATIONS_H
