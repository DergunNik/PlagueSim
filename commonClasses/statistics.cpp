#include "statistics.h"

Statistics::Statistics(QVector<Citizen>* citizens) :
    _citizens(citizens)
{}

void Statistics::append()
{
    _history.emplaceBack();
    for (auto now : *_citizens) {
        _history.back().dead += !now.isAlive();
        _history.back().alive += now.isAlive();
        _history.back().infected += now.isInfected();
        _history.back().haveSymptoms += now.hasSyptoms();
        _history.back().contagious += now.isContagious();
        _history.back().vaccinated += now.isVaccinated();
        _history.back().immunity += now.immunity();
    }
    _history.back().immunity /= _citizens->size();
}

QVector<CitySituation> Statistics::history() const
{
    return _history;
}

void Statistics::clear()
{
    _history.clear();
}


// struct's operators //************************************************************************************

CitySituation CitySituation::operator+(const CitySituation &other) const {
    return {dead + other.dead,
            alive + other.alive,
            infected + other.infected,
            haveSymptoms + other.haveSymptoms,
            contagious + other.contagious,
            vaccinated + other.vaccinated,
            immunity + other.immunity};
}

CitySituation CitySituation::operator-(const CitySituation &other) const {
    return {dead - other.dead,
            alive - other.alive,
            infected - other.infected,
            haveSymptoms - other.haveSymptoms,
            contagious - other.contagious,
            vaccinated - other.vaccinated,
            immunity - other.immunity};
}

CitySituation &CitySituation::operator+=(const CitySituation &other) {
    *this = *this + other;
    return *this;
}

CitySituation &CitySituation::operator-=(const CitySituation &other) {
    *this = *this - other;
    return *this;
}

CitySituation CitySituation::operator/(const uint value) const
{
    return {dead / value,
            alive / value,
            infected / value,
            haveSymptoms / value,
            contagious / value,
            vaccinated / value,
            immunity / value};
}

CitySituation CitySituation::operator*(const uint value) const
{
    return {dead * value,
            alive * value,
            infected * value,
            haveSymptoms * value,
            contagious * value,
            vaccinated * value,
            immunity * value};
}

CitySituation &CitySituation::operator/=(const uint value)
{
    *this = *this / value;
    return *this;
}

CitySituation &CitySituation::operator*=(const uint value)
{
    *this = *this * value;
    return *this;
}

uint CitySituation::operator[](const size_t i) const
{
    switch (i) {
    case 0:
        return this->dead;
    case 1:
        return this->alive;
    case 2:
        return this->infected;
    case 3:
        return this->haveSymptoms;
    case 4:
        return this->contagious;
    case 5:
        return this->vaccinated;
    default:
        return this->immunity * 100;
    };
}
