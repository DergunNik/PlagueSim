#include "citymanager.h"


CityManager::CityManager(GenHandler &&genHandler) :
    _settings(genHandler._settings),
    _districtsManager(std::move(genHandler._districtsManager)),
    _citizens(std::move(genHandler._citizens))
{}

// getters and setters
QVector<Citizen>& CityManager::citizens()
{
    return _citizens;
}

void CityManager::setCitizens(const QVector<Citizen> &newCitizens)
{
    _citizens = newCitizens;
}

StartSettings& CityManager::settings()
{
    return _settings;
}

void CityManager::setSettings(const StartSettings &newSettings)
{
    _settings = newSettings;
}

DistrictsManager& CityManager::districtsManager()
{
    return _districtsManager;
}

void CityManager::setDistrictsManager(const DistrictsManager &newDistrictsManager)
{
    _districtsManager = newDistrictsManager;
}

