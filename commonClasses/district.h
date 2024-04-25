#ifndef DISTRICT_H
#define DISTRICT_H

#include <declarations.h>

#include <QVector>


enum DistrictType
{
    WORK = 0,
    RECREATION,
    HOME,
    HOSPITAL
};


struct CitizensProportion
{
    ushort notInfected;
    ushort explicitlyInf;
    ushort asymptomaticallyInf;
};


const float DISCRICT_MIN_SIZE = 0.8;
const float DISTRICT_DELTA = 0.2;


class District
{
private:
    DistrictType _type;
    float _size;
    QPair<uint8_t, uint8_t> _pos;
    QVector<Citizen*> _curCitizens;
    CitizensProportion _proportion = {0, 0, 0};

public:
    District() = delete;
    District(DistrictType type, float size, QPair<uint8_t, uint8_t> pos);

    void setCitizens(QVector<Citizen*> citizens);
    void addCitizen(Citizen* citizen);
    QVector<Citizen*> citizens() const;
    void resetCitizens();

    CitizensProportion proportion() const;
    DistrictType type() const;
    float size() const;
    QPair<uint8_t, uint8_t> pos() const;
};

#endif // DISTRICT_H
