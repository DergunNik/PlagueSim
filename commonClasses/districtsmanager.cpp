#include "districtsmanager.h"


DistrictsManager::DistrictsManager(QVector<District> commonVect)
{
    _homes.clear();
    _works.clear();
    _recreations.clear();

    for(auto& now : commonVect) {
        switch (now.type()) {
        case WORK:
            _works.push_back(now);
            break;
        case RECREATION:
            _recreations.push_back(now);
            break;
        case HOME:
            _homes.push_back(now);
            break;
        }
    }
}

District *DistrictsManager::getRandomDistrict()
{
    uint sumSize = _homes.size() + _works.size() + _recreations.size();
    uint index = QRandomGenerator::global()->bounded(sumSize);
    if (index < _homes.size()) {
        return &_homes[index];
    } else if (index >= sumSize - _works.size()) {
        return &_works[index - _homes.size() - _recreations.size()];
    } else {
        return &_recreations[index - _homes.size()];
    }
}


District* DistrictsManager::getRandomHome()
{
    return &_homes[QRandomGenerator::global()->bounded(_homes.size())];
}


District* DistrictsManager::getRandomWork()
{
    return &_works[QRandomGenerator::global()->bounded(_works.size())];
}


District *DistrictsManager::getRandomForWork()
{
    float temp = QRandomGenerator::global()->bounded(1.0F);
    if (temp < WORK_PERCENT_FOR_WORK) {
        return getRandomWork();
    } else {
        return getRandomRecreation();
    }
}


District* DistrictsManager::getRandomRecreation()
{
    return &_recreations[QRandomGenerator::global()->bounded(_recreations.size())];
}


QVector<District*> DistrictsManager::getAllDistricts()
{
    QVector<District*> retVec;

    for (auto& now : _homes) {
        retVec.push_back(&now);
    }
    for (auto& now : _works) {
        retVec.push_back(&now);
    }
    for (auto& now : _recreations) {
        retVec.push_back(&now);
    }

    return retVec;
}
