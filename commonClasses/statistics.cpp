#include "statistics.h"

Statistics::Statistics(QVector<Citizen>* citizens) :
    _citizens(citizens)
{}

void Statistics::append()
{
    _history.emplaceBack();
    for (auto now : *_citizens) {
        _history.back().alive += now.isAlive();
        _history.back().infected += now.isInfected();
        _history.back().haveSymptoms += now.hasSyptoms();
        _history.back().contagious += now.isContagious();
        _history.back().vaccinated += now.isVaccinated();
    }
}

QVector<CitySituation> Statistics::history() const
{
    return _history;
}

void Statistics::clear()
{
    _history.clear();
}
