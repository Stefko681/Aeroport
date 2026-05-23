//
// Created by stefko on 5/14/26.
//

#include "PrivateJet.h"
#include <stdexcept>

PrivateJet::PrivateJet(std::string airplaneId, std::string model, const double health)
    : Airplane(std::move(airplaneId), std::move(model), health) {
}

AirplaneType PrivateJet::getAirplaneType() const {
    return AirplaneType::PrivateJet;
}

int PrivateJet::getCapacity() const {
    return CAPACITY;
}

bool PrivateJet::canLand(const Runway &runway) const {
    return runway.getLength() >= 1000.0 && runway.getHasVIPTerminal();
}

double PrivateJet::airportFee(const double) const {
    return 5000.0;
}

std::unique_ptr<Airplane> PrivateJet::clone(std::string newId) const {
    return std::make_unique<PrivateJet>(std::move(newId), model, health);
}

void PrivateJet::completeFlight() {
    if (!canFly()) throw std::runtime_error("Aircraft health too low to complete a flight.");
    health -= 25.0;
}
