//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_AIRCRAFT_H
#define AEROPORT_AIRCRAFT_H
#include <string>
#include "AirplaneType.h"

class Airplane {
protected:
    std::string airplaneId;
    std::string model;
    double health;

public:
    Airplane(std::string airplaneId, std::string model, double health);

    virtual ~Airplane() = default;

    [[nodiscard]] virtual AirplaneType getAirplaneType() const = 0;

    [[nodiscard]] virtual bool canLand(double length, bool hasVIPTerminal) const = 0;

    virtual void completeFlight() = 0;

    [[nodiscard]] virtual double airportFee(double ticketRevenue) const = 0;

    [[nodiscard]] bool canFly() const;
};


#endif //AEROPORT_AIRCRAFT_H
