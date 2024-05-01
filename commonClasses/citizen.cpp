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
    _halfdaysBeforeVacBoost = AVERAGE_VAC_TIME - 1 + QRandomGenerator::global()->bounded(3);
}


void Citizen::update()
{
    if (!_isVaccinated && _responsibility != IRRESPONSIBLE && !_hasSyptoms &&
        QRandomGenerator::global()->bounded(1.0F) < VACCINATION_PROBABILITY) {
        getVaccinated();
    }

    if (_halfdayBeforeSyptoms == 0) {
        _hasSyptoms = true;
    }
    if (_halfdayBeforeСоntagious == 0) {
        _isCоntagious = true;
    }
    if (_halfdayBeforeRecovery == 0) {
        _isInfected = false;
        _hasSyptoms = false;
        _isCоntagious = false;

        _halfdayBeforeSyptoms = -1;
        _halfdayBeforeСоntagious = -1;

        if (QRandomGenerator::global()->bounded(_disease->lethality) > _physicalHealth) {
            _isAlive = false;
        } else {
            _immunity += RECOVERY_BOOST;
            _immunity = normalize(_immunity);
        }
    }
    if (_halfdaysBeforeVacBoost == 0) {
        _immunity *= 2;
        _immunity += VACCINATION_BOOST;
        _immunity = normalize(_immunity);
    }

    _halfdayBeforeSyptoms -= (_halfdayBeforeSyptoms >= 0 ? 1 : 0);
    _halfdayBeforeСоntagious -= (_halfdayBeforeСоntagious >= 0 ? 1 : 0);
    _halfdayBeforeRecovery -= (_halfdayBeforeRecovery >= 0 ? 1 : 0);
    _halfdaysBeforeVacBoost -= (_halfdaysBeforeVacBoost >= 0 ? 1 : 0);
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
    _halfdayBeforeRecovery =  _disease->recoveryDays * 2 + MIN_DELTA_HALFDAYS;
    _halfdayBeforeСоntagious = (_disease->latentDays * 2 > MIN_DELTA_HALFDAYS ? _disease->latentDays * 2 - MIN_DELTA_HALFDAYS : 0);
    _halfdayBeforeSyptoms = _disease->incubationDays * 2 + MIN_DELTA_HALFDAYS;
}


void Citizen::goTo(int time)
{
    auto aimDistr = _schedule.goTo(time);
    if (aimDistr != nullptr && _isAlive) {
        if ((_hasSyptoms && _responsibility != IRRESPONSIBLE) || _isOnSelfIsolation) {
            aimDistr = _schedule.home();
        }
        if (_isInHospital) {
            aimDistr = _schedule.hospital();
        }

        aimDistr->addCitizen(this);
    }
}


void Citizen::getInfected(bool throuhgMask)
{
    if (QRandomGenerator::global()->bounded(1.0F) + throuhgMask * MASK_PROTECTION < _disease->contagiousness &&
        QRandomGenerator::global()->bounded(1.0F) > _immunity) {
        _isInfected = true;

        ushort delta = qMax(MIN_DELTA_HALFDAYS, static_cast<ushort>(_disease->recoveryDays * 2 * DELTA_PART));
        _halfdayBeforeRecovery =  _disease->recoveryDays * 2 +
                             (QRandomGenerator::global()->bounded(delta * 2 + 1) - delta);
        if (_halfdayBeforeRecovery < 1 && _disease->recoveryDays > 0) {
            _halfdayBeforeRecovery = 1;
        }

        delta = qMax(MIN_DELTA_HALFDAYS, static_cast<ushort>(_disease->latentDays * 2 * DELTA_PART));
        _halfdayBeforeСоntagious = _disease->latentDays * 2 +
                               (QRandomGenerator::global()->bounded(delta * 2 + 1) - delta);
        if (_halfdayBeforeСоntagious < 1 && _disease->recoveryDays > 1 && _disease->latentDays > 0) {
            _halfdayBeforeСоntagious = 1;
        }

         delta = qMax(MIN_DELTA_HALFDAYS, static_cast<ushort>(_disease->incubationDays * 2 * DELTA_PART));
        _halfdayBeforeSyptoms = _disease->incubationDays * 2 +
                             (QRandomGenerator::global()->bounded(delta * 2 + 1) - delta);
         if (_halfdayBeforeSyptoms < 1 && _disease->recoveryDays > 1 && _disease->incubationDays > 0) {
            _halfdayBeforeSyptoms = 1;
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

bool Citizen::isInHospital() const
{
    return _isInHospital;
}

void Citizen::setIsInHospital(bool newIsInHospital)
{
    _isInHospital = newIsInHospital;
}
