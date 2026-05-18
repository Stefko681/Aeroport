//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_RUNWAY_H
#define AEROPORT_RUNWAY_H
#include "RunwayStatus.h"
#include <string>

class Airplane;

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

    double getLength() const;

    bool getHasVIPTerminal() const;

    bool getHasHeavyDuty() const;
};


#endif //AEROPORT_RUNWAY_H
