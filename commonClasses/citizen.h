#ifndef CITIZEN_H
#define CITIZEN_H

#include <basicstructs.h>
#include <declarations.h>
#include <schedule.h>

#include <cstdint>
#include <QRandomGenerator>


enum Responsibility
{
    IRRESPONSIBLE = 0,
    SEMIRESPONSIBLE,
    RESPONSIBLE
};


const uint8_t AVERAGE_VAC_TIME = 5;
const float VACCINATION_PROBABILITY = 0.05;
const float VACCINATION_BOOST = 0.4;
const float RECOVERY_BOOST = 0.4;
const ushort MIN_DELTA_HALFDAYS = 2;
const float DELTA_PART = 0.25;
const float MASK_PROTECTION = 0.1;


class Citizen
{
private:
    float _immunity = 0;
    float _physicalHealth = 0;
    float _sociability = 0;
    Responsibility _responsibility = IRRESPONSIBLE;
    bool _isAlive = true;
    bool _isVaccinated = false;
    bool _isInfected = false;
    bool _hasSyptoms = false;
    bool _isCоntagious = false;
    bool _isWearingMask = false;
    bool _isOnSelfIsolation = false;
    bool _isInHospital = false;
    uint _familyNumber = -1;
    Schedule _schedule;
    Disease* _disease = nullptr;

    int16_t _halfdayBeforeSyptoms = -1;
    int16_t _halfdayBeforeСоntagious = -1;
    int16_t _halfdayBeforeRecovery = -1;
    int16_t _halfdaysBeforeVacBoost = -1;

    void updateInfection();
    void recover();
    float normalize(float value);

public:
    Citizen() = default;
    Citizen(float immunity, float physicalHealth, float sociability,
            Responsibility responsibility, bool vaccinStatus, uint familyNumber);

    void goTo(int time);
    void getInfected(bool throuhgMask = false);
    void getVaccinated();
    void update();

    void makeZeroParient();

    // getters and setters
    Responsibility responsibility() const;
    Schedule schedule() const;
    bool isVaccinated() const;
    float immunity() const;
    float physicalHealth() const;
    float sociability() const;
    uint familyNumber() const;
    void setImmunity(float newImmunity);
    void setPhysicalHealth(float newPhysicalHealth);
    void setResponsibility(Responsibility newResponsibility);
    void setSchedule(const Schedule &newSchedule);
    void setSociability(float newSociability);
    bool isInfected() const;
    bool hasSyptoms() const;
    bool isContagious() const;
    void setDisease(Disease *newDisease);
    bool isAlive() const;
    bool isWearingMask() const;
    void setIsWearingMask(bool newIsWearingMask);
    bool isOnSelfIsolation() const;
    void setIsOnSelfIsolation(bool newIsOnSelfIsolation);
    bool isInHospital() const;
    void setIsInHospital(bool newIsInHospital);
};

#endif // CITIZEN_H
