#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <declarations.h>

#include "qtypes.h"


class Schedule
{
private:
    DistrictsManager* _districtManager = nullptr;
    District* _home = nullptr;
    District* _work = nullptr;

public:
    Schedule() = default;
    Schedule(DistrictsManager* districtManager, District* home = nullptr, District* work = nullptr);

    District* goTo(uint time);

    District* home() const;
    District* recreation() const;
    District* work() const;
    void setHome(District *newHome);
    void setWork(District *newWork);
    DistrictsManager *districtManager() const;
    void setDistrictManager(DistrictsManager *newDistrictManager);
};

#endif // SCHEDULE_H
