#pragma once

#include <memory>
#include <vector>
#include "WeatherObserver.h"

class WeatherSubject {
    std::vector<std::weak_ptr<WeatherObserver> > observers;

public:
    void subscribe(std::shared_ptr<WeatherObserver> obs);

    void unsubscribe(const std::shared_ptr<WeatherObserver> &obs);

    void notifyAll(WeatherCondition condition) const;
};


