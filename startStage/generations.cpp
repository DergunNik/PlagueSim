#include "generations.h"
#include "startmenu.h"

#include <cmath>


GenHandler::GenHandler(StartSettings settings) : _settings(settings)
{
    generateDistricts();
    generateCitizens();
    generateSchedules();
}


QVector<Citizen> GenHandler::citizens() const
{
    return _citizens;
}

DistrictsManager GenHandler::districtsManager() const
{
    return _districtsManager;
}

void GenHandler::generateDistricts()
{
    const uint districtCnt = _settings.districtsNumber;
    const uint matrixSize = qSqrt(districtCnt) + 1;

    QPair<uint8_t, uint8_t> pos;
    DistrictType type = HOME;
    float size = NAN;
    uint i = 0;

    for (; i < 4; ++i) {
        type = static_cast<DistrictType>(i);
        pos = QPair<uint8_t, uint8_t>(i / matrixSize, i % matrixSize);
        size = DISCRICT_MIN_SIZE + QRandomGenerator::global()->bounded(DISTRICT_DELTA);
        if (i == static_cast<uint>(HOSPITAL)) {
            size *= (1 + HOSPITAL_PERCENT_FOR_WORK + _settings.clinicCapacity / static_cast<float>(DISTRICT_CAPACITY)) / 2;
        }
        _districts.emplaceBack(type, size, pos);
    }

    for (; i < districtCnt; ++i) {
        type = getDistrictType();
        size = DISCRICT_MIN_SIZE + QRandomGenerator::global()->bounded(DISTRICT_DELTA);
        pos = QPair<uint8_t, uint8_t>(i / matrixSize, i % matrixSize);
        _districts.emplaceBack(type, size, pos);
    }

    _districtsManager = DistrictsManager(_districts);
    _districts.clear();
}


void GenHandler::generateCitizens()
{
    Responsibility responsibility = IRRESPONSIBLE;
    bool vaccinStatus = false;
    float immunity = 0;
    float physicalHealth = 0;
    float sociability = 0;
    uint familyNumber = 0;
    uint familyCntr = 0;

    float probability = MIN_FAMILY_PROBABILITY;

    for (uint i = 0; i < _settings.populationNumber; ++i) {
        if (probability != MIN_FAMILY_PROBABILITY &&
            QRandomGenerator::global()->bounded(1.0F) < probability) {
            probability = MIN_FAMILY_PROBABILITY;
            familyNumber = ++familyCntr;
        } else {
            probability *= 2;
            familyNumber = familyCntr;
        }

        vaccinStatus =
            QRandomGenerator::global()->bounded(1.0F) < _settings.initialVaccination;

        responsibility = getResponsibility();
        immunity = QRandomGenerator::global()->bounded(MAX_BASIC_IMMUNITY);
        physicalHealth = QRandomGenerator::global()->bounded(MAX_BASIC_HEALTH);
        sociability = MIN_BASIC_SOCIABILITY + QRandomGenerator::global()->bounded(1 - MIN_BASIC_SOCIABILITY);

        _citizens.emplaceBack(immunity, physicalHealth, sociability,
                              responsibility, vaccinStatus, familyNumber);
    }
}


void GenHandler::generateSchedules()
{
    uint lastFamily = 0;
    District* lastHomeDistrict = _districtsManager.getRandomHome();
    for (auto& now : _citizens) {
        if (now.familyNumber() != lastFamily) {
            lastFamily = now.familyNumber();
            lastHomeDistrict = _districtsManager.getRandomHome();
        }
        Schedule schedule(&_districtsManager, lastHomeDistrict,
                          _districtsManager.getRandomForWork(),
                          _districtsManager.getRandomHospital());
        now.setSchedule(schedule);
    }
}


DistrictType GenHandler::getDistrictType()
{
    float temp = QRandomGenerator::global()->bounded(1.0F);
    if (temp < RECREATION_PROBABILITY) {
        return RECREATION;
    } else if (temp > 1 - WORK_PROBABILITY) {
        return WORK;
    } else {
        return HOME;
    }
}


Responsibility GenHandler::getResponsibility()
{
    float temp = QRandomGenerator::global()->bounded(1.0F);
    if (temp < _settings.irresponsiblePercent) {
        return IRRESPONSIBLE;
    } else if (temp > 1 - _settings.responsiblePercent) {
        return RESPONSIBLE;
    } else {
        return SEMIRESPONSIBLE;
    }
}
