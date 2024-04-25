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
    District* _hospital = nullptr;

public:
    Schedule() = default;
    Schedule(DistrictsManager* districtManager, District* home, District* work, District* hospital);

    District* goTo(uint time);

    District* home() const;
    District* recreation() const;
    District* work() const;
    void setHome(District *newHome);
    void setWork(District *newWork);
    DistrictsManager *districtManager() const;
    void setDistrictManager(DistrictsManager *newDistrictManager);
    District *hospital() const;
    void setHospital(District *newHospital);
};

#endif // SCHEDULE_H
