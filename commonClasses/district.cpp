#include <plaguebasics.h>


District::District(DistrictType type, float size, QPair<uint8_t, uint8_t> pos) :
    _type(type),
    _size(size),
    _pos(pos)
{}


void District::addCitizen(Citizen *citizen)
{
    _curCitizens.push_back(citizen);
    if (!citizen->isInfected()) {
        ++_proportion.notInfected;
    } else if (citizen->hasSyptoms()) {
        ++_proportion.explicitlyInf;
    } else {
        ++_proportion.asymptomaticallyInf;
    }
}


void District::setCitizens(QVector<Citizen *> citizens)
{
    resetCitizens();
    for (auto now : citizens) {
        addCitizen(now);
    }
}


void District::resetCitizens()
{
    _proportion = {0, 0, 0};
    _curCitizens.clear();
}


// getters and setters //************************************************************************************

CitizensProportion District::proportion() const
{
    return _proportion;
}

QVector<Citizen *> District::citizens() const
{
    return _curCitizens;
}

DistrictType District::type() const
{
    return _type;
}

float District::size() const
{
    return _size;
}

QPair<uint8_t, uint8_t> District::pos() const
{
    return _pos;
}
