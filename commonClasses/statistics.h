#ifndef STATISTICS_H
#define STATISTICS_H

#include <plaguebasics.h>

struct CitySituation
{
    uint alive = 0;
    uint infected = 0;
    uint haveSymptoms = 0;
    uint contagious = 0;
    uint vaccinated = 0;
};

class Statistics
{
private:
    QVector<Citizen>* _citizens;
    QVector<CitySituation> _history;

public:
    Statistics() = default;
    explicit Statistics(QVector<Citizen>* citizens);

    void append();
    QVector<CitySituation> history() const;
    void clear();
};

#endif // STATISTICS_H
