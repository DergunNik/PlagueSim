#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <statistics.h>
#include <deque>

template<typename T>
class MovingAverage
{
private:
    ushort _windowSize;
    std::deque<T> _tempData;
    T _total;

public:
    explicit MovingAverage(ushort windowSize) : _windowSize(windowSize) {
        _total *= 0;
    };

    T addData(T newData) {
        _tempData.push_back(newData);
        _total += newData;
        if (_tempData.size() > _windowSize) {
            _total -= _tempData.front();
            _tempData.pop_front();
        }

        return calculateMovingAverage();
    }

    T calculateMovingAverage() const {
        if (_tempData.empty()) {
            return T();
        }
        return _total / _tempData.size();
    }
};

#endif // MOVINGAVERAGE_H
