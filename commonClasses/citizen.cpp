#include <plaguebasics.h>


Citizen::Citizen(float immunity, float physicalHealth, float sociability,
                 Responsibility responsibility, bool vaccinStatus, uint familyNumber) :
    _immunity(immunity),
    _physicalHealth(physicalHealth),
    _sociability(sociability),
    _responsibility(responsibility),
    _isVaccinated(vaccinStatus),
    _familyNumber(familyNumber)
{}


void Citizen::getVaccinated()
{
    _immunity /= 2;
    _daysBeforeVacBoost = AVERAGE_VAC_TIME - 1 + QRandomGenerator::global()->bounded(3);
}


void Citizen::update()
{
    if (!_isVaccinated && _responsibility != IRRESPONSIBLE && !_hasSyptoms &&
        QRandomGenerator::global()->bounded(1.0f) < VACCINATION_PROBABILITY) {
        getVaccinated();
    }

    if (_dayBeforeSyptoms == 0) {
        _hasSyptoms = true;
    }
    if (_dayBeforeСоntagious == 0) {
        _isCоntagious = true;
    }
    if (_dayBeforeRecovery == 0) {
        _isInfected = false;
        _hasSyptoms = false;
        _isCоntagious = false;

        if (QRandomGenerator::global()->bounded(_disease->lethality) > _physicalHealth) {
            _isAlive = false;
        } else {
            _immunity += RECOVERY_BOOST;
            _immunity = normalize(_immunity);
        }
    }
    if (_daysBeforeVacBoost == 0) {
        _immunity *= 2;
        _immunity += VACCINATION_BOOST;
        _immunity = normalize(_immunity);
    }

    _dayBeforeSyptoms -= (_dayBeforeSyptoms >= 0 ? 1 : 0);
    _dayBeforeСоntagious -= (_dayBeforeСоntagious >= 0 ? 1 : 0);
    _dayBeforeRecovery -= (_dayBeforeRecovery >= 0 ? 1 : 0);
    _daysBeforeVacBoost -= (_daysBeforeVacBoost >= 0 ? 1 : 0);
}


float Citizen::normalize(float value)
{
    if (value > 1) {
        value = 1;
    } else if (value < 0) {
        value = 0;
    }
    return value;
}


void Citizen::makeZeroParient()
{
    _isInfected = true;
    _dayBeforeRecovery =  _disease->recoveryDays * (T_MIN_SIZE + T_DELTA);
    _dayBeforeСоntagious = _disease->latentDays * (T_MIN_SIZE + T_DELTA);
    _dayBeforeSyptoms = _disease->incubationDays * (T_MIN_SIZE + T_DELTA);
}


void Citizen::goTo(int time)
{
    auto aimDistr = _schedule.goTo(time);
    if (aimDistr != nullptr && _isAlive) {
        if ((_hasSyptoms && _responsibility != IRRESPONSIBLE) || _isOnSelfIsolation) {
            aimDistr = _schedule.home();
        }

        aimDistr->addCitizen(this);
    }
}


void Citizen::getInfected(bool throuhgMask)
{
    if (QRandomGenerator::global()->bounded(1.0F) + throuhgMask * MASK_PROTECTION < _disease->contagiousness &&
        QRandomGenerator::global()->bounded(1.0F) > _immunity) {
        _isInfected = true;
        _dayBeforeRecovery =  _disease->recoveryDays *
                             (T_MIN_SIZE + QRandomGenerator::global()->bounded(T_DELTA));
        if (_dayBeforeRecovery < 1 && _disease->recoveryDays > 0) {
            _dayBeforeRecovery = 1;
        }
        _dayBeforeСоntagious = _disease->latentDays *
                               (T_MIN_SIZE + QRandomGenerator::global()->bounded(T_DELTA));
        if (_dayBeforeСоntagious < 1 && _disease->recoveryDays > 1 && _disease->latentDays > 0) {
            _dayBeforeСоntagious = 1;
        }
        _dayBeforeSyptoms = _disease->incubationDays *
                            (T_MIN_SIZE + QRandomGenerator::global()->bounded(T_DELTA));
        if (_dayBeforeSyptoms < 1 && _disease->recoveryDays > 1 && _disease->incubationDays > 0) {
            _dayBeforeSyptoms = 1;
        }
    }
}


// getters and setters //************************************************************************************

uint Citizen::familyNumber() const
{
    return _familyNumber;
}

Schedule Citizen::schedule() const
{
    return _schedule;
}

void Citizen::setSchedule(const Schedule &newSchedule)
{
    _schedule = newSchedule;
}

float Citizen::immunity() const
{
    return _immunity;
}

void Citizen::setImmunity(float newImmunity)
{
    _immunity = newImmunity;
    _immunity = normalize(_immunity);
}


float Citizen::physicalHealth() const
{
    return _physicalHealth;
}

void Citizen::setPhysicalHealth(float newPhysicalHealth)
{
    _physicalHealth = newPhysicalHealth;
    _physicalHealth = normalize(_physicalHealth);
}

float Citizen::sociability() const
{
    return _sociability;
}

void Citizen::setSociability(float newSociability)
{
    _sociability = newSociability;
    _sociability = normalize(_sociability);
}

Responsibility Citizen::responsibility() const
{
    return _responsibility;
}

void Citizen::setResponsibility(Responsibility newResponsibility)
{
    _responsibility = newResponsibility;
}

bool Citizen::isVaccinated() const
{
    return _isVaccinated;
}

bool Citizen::isInfected() const
{
    return _isInfected;
}

bool Citizen::hasSyptoms() const
{
    return _hasSyptoms;
}

bool Citizen::isContagious() const
{
    return _isCоntagious;
}

void Citizen::setDisease(Disease *newDisease)
{
    _disease = newDisease;
}

bool Citizen::isAlive() const
{
    return _isAlive;
}

bool Citizen::isWearingMask() const
{
    return _isWearingMask;
}

void Citizen::setIsWearingMask(bool newIsWearingMask)
{
    _isWearingMask = newIsWearingMask;
}

bool Citizen::isOnSelfIsolation() const
{
    return _isOnSelfIsolation;
}

void Citizen::setIsOnSelfIsolation(bool newIsOnSelfIsolation)
{
    _isOnSelfIsolation = newIsOnSelfIsolation;
}
