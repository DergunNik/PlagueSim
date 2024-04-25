#include <plaguebasics.h>
#include <districtsmanager.h>


Schedule::Schedule(DistrictsManager* districtManager, District* home, District* work, District* hospital) :
    _districtManager(districtManager),
    _home(home),
    _work(work),
    _hospital(hospital)
{}


District *Schedule::goTo(uint time)
{
    if (time % 2 == 0) {
        return home();
    } else {
        time = (time + 1) / 2;
        if (time % 7 == 5 || time % 7 == 6) {
            return recreation();
        } else {
            return work();
        }
    }
}


District *Schedule::recreation() const
{
    return _districtManager->getRandomRecreation();
}


// getters and setters //************************************************************************************

District *Schedule::work() const
{
    return _work;
}

void Schedule::setWork(District *newWork)
{
    _work = newWork;
}

District *Schedule::home() const
{
    return _home;
}

void Schedule::setHome(District *newHome)
{
    _home = newHome;
}

DistrictsManager *Schedule::districtManager() const
{
    return _districtManager;
}

void Schedule::setDistrictManager(DistrictsManager *newDistrictManager)
{
    _districtManager = newDistrictManager;
}

District *Schedule::hospital() const
{
    return _hospital;
}

void Schedule::setHospital(District *newHospital)
{
    _hospital = newHospital;
}
