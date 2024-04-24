#ifndef CITYMANAGER_H
#define CITYMANAGER_H

#include <generations.h>

class CityManager
{
    StartSettings _settings;
    DistrictsManager _districtsManager;
    QVector<Citizen> _citizens = {};

public:
    CityManager() = default;
    explicit CityManager(GenHandler&& genHandler);

    StartSettings& settings();
    void setSettings(const StartSettings &newSettings);
    DistrictsManager& districtsManager();
    void setDistrictsManager(const DistrictsManager &newDistrictsManager);
    QVector<Citizen>& citizens();
    void setCitizens(const QVector<Citizen> &newCitizens);
};

#endif // CITYMANAGER_H
