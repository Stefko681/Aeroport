#include "WeatherSubject.h"
#include <algorithm>
#include <ranges>

void WeatherSubject::subscribe(std::shared_ptr<WeatherObserver> obs) {
    if (!obs) return;
    auto it = std::ranges::find_if(observers, [&obs](const std::weak_ptr<WeatherObserver> &weakObs) {
        return weakObs.lock() == obs;
    });
    if (it == observers.end()) observers.push_back(obs);
}

void WeatherSubject::unsubscribe(const std::shared_ptr<WeatherObserver> &obs) {
    if (!obs) return;
    std::erase_if(observers, [&obs](const std::weak_ptr<WeatherObserver> &weakObs) {
        return weakObs.expired() || weakObs.lock() == obs;
    });
}

void WeatherSubject::notifyAll(const WeatherCondition condition) const {
    const auto snapshot = observers;
    for (const auto &weakObs: snapshot) {
        if (auto o = weakObs.lock()) {
            o->onWeatherChanged(condition);
        }
    }
}
