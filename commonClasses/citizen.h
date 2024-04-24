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

const uint8_t AVERAGE_VAC_TIME = 3;
const float VACCINATION_PROBABILITY = 0.02;
const float VACCINATION_BOOST = 0.4;
const float RECOVERY_BOOST = 0.4;
const float T_MIN_SIZE = 0.8;
const float T_DELTA = 0.4;
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
    uint _familyNumber = -1;
    Schedule _schedule;
    Disease* _disease = nullptr;

    int16_t _dayBeforeSyptoms = -1;
    int16_t _dayBeforeСоntagious = -1;
    int16_t _dayBeforeRecovery = -1;
    int16_t _daysBeforeVacBoost = -1;

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
};

#endif // CITIZEN_H
