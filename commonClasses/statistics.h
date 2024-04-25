#ifndef STATISTICS_H
#define STATISTICS_H

#include <plaguebasics.h>

struct CitySituation
{
    uint dead = 0;
    uint alive = 0;
    uint infected = 0;
    uint haveSymptoms = 0;
    uint contagious = 0;
    uint vaccinated = 0;
    float immunity = 0;

    CitySituation operator+(const CitySituation& other) const;
    CitySituation operator-(const CitySituation& other) const;
    CitySituation& operator+=(const CitySituation& other);
    CitySituation& operator-=(const CitySituation& other);
    CitySituation operator/(const uint value) const;
    CitySituation operator*(const uint value) const;
    CitySituation& operator/=(const uint value);
    CitySituation& operator*=(const uint value);

    uint operator[](const size_t i) const;
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
