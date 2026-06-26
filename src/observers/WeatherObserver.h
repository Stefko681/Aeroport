#pragma once


enum class WeatherCondition {
    Sunny,
    Raining,
    Storm
};

class WeatherObserver {
public:
    virtual ~WeatherObserver() = default;

    virtual void onWeatherChanged(WeatherCondition newCondition) = 0;
};


