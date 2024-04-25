#ifndef BASICSTRUCTS_H
#define BASICSTRUCTS_H

#include "qtypes.h"


struct Disease
{
    float contagiousness;
    uint recoveryDays;
    float lethality;
    uint latentDays;
    uint incubationDays;
};

struct StartSettings
{
    float initialVaccination;
    float responsiblePercent;
    float semiresponsiblePercent;
    float irresponsiblePercent;
    uint districtsNumber;
    uint populationNumber;
    uint clinicCapacity;
    Disease disease;
};

#endif // BASICSTRUCTS_H
