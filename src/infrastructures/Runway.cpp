//
// Created by stefko on 5/15/26.
//

#include "Runway.h"
#include <stdexcept>

Runway::Runway(std::string runwayId, const double length,
               const bool hasILS, const bool hasVIPTerminal, const bool hasHeavyDuty)
    : runwayId(std::move(runwayId)),
      length(length),
      runwayStatus(RunwayStatus::Free),
      hasILS(hasILS),
      hasVIPTerminal(hasVIPTerminal),
      hasHeavyDuty(hasHeavyDuty),
      airplane(nullptr) {
    if (this->runwayId.empty())
        throw std::invalid_argument("Runway ID cannot be empty.");
    if (length <= 0)
        throw std::invalid_argument("Runway length must be positive.");
}

const std::string &Runway::getRunwayId() const {
    return runwayId;
}

double Runway::getLength() const {
    return length;
}

RunwayStatus Runway::getStatus() const {
    return runwayStatus;
}

bool Runway::getHasILS() const {
    return hasILS;
}

bool Runway::getHasVIPTerminal() const {
    return hasVIPTerminal;
}

bool Runway::getHasHeavyDuty() const {
    return hasHeavyDuty;
}

Airplane *Runway::getAirplane() const {
    return airplane;
}
