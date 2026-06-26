#pragma once

#include "WeatherObserver.h"

class Engine;

class StormObserver final : public WeatherObserver {
    Engine& engine;

public:
    explicit StormObserver(Engine& engine);
    void onWeatherChanged(WeatherCondition newCondition) override;

};


