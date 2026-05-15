//
// Created by stefko on 5/14/26.
//

#include "PrivateJet.h"

#include <stdexcept>

PrivateJet::PrivateJet(std::string airplaneId, std::string model, const double health,
                       const int capacity) : Airplane(std::move(airplaneId), std::move(model), health), capacity() {
    if (capacity <= 0) throw std::invalid_argument("Capacity can not be less or equal to zero");
}

double PrivateJet::airportFee(const double ticketRevenue) const {
    return 5000.0;
}

bool PrivateJet::canLand(const double length, const bool hasVIPTerminal) const {
    return length >= 1000 || hasVIPTerminal == true;
}

AirplaneType PrivateJet::getAirplaneType() const {
    return AirplaneType::PrivateJet;
}

void PrivateJet::completeFlight() {
    if (!canFly()) throw std::runtime_error("Not enough heath for flying");
    health -= health * 0.25;
}
