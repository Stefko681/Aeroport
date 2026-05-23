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
    Runway(std::string runwayId, double length,
           bool hasILS = false, bool hasVIPTerminal = false, bool hasHeavyDuty = false);

    virtual ~Runway() = default;

    [[nodiscard]] const std::string &getRunwayId() const;

    [[nodiscard]] double getLength() const;

    [[nodiscard]] RunwayStatus getStatus() const;

    [[nodiscard]] bool getHasILS() const;

    [[nodiscard]] bool getHasVIPTerminal() const;

    [[nodiscard]] bool getHasHeavyDuty() const;

    [[nodiscard]] Airplane *getAirplane() const;
};


#endif //AEROPORT_RUNWAY_H
