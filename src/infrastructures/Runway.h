//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_RUNWAY_H
#define AEROPORT_RUNWAY_H
#include "RunwayStatus.h"
#include "Airline.h"
#include <string>

class Runway {
protected:
    std::string runwayId;
    double length;
    RunwayStatus runwayStatus;
    bool hasILS;
    bool hasVIPTerminal;
    bool hasHeavyDuty;

    Airplane *airplane{nullptr};

public:
    Runway(std::string runwayId, double length, bool hasILS = false,
           bool hasVIPTerminal = false,
           bool hasHeavyDuty = false);

    virtual ~Runway() = default;
};


#endif //AEROPORT_RUNWAY_H
