//
// Created by stefko on 5/14/26.
//

#include "PrivateJet.h"

#include <stdexcept>

PrivateJet::PrivateJet(std::string airplaneId, std::string model, const double health) : Airplane(std::move(airplaneId),
    std::move(model), health) {
}

double PrivateJet::airportFee(const double ticketRevenue) const {
    return 5000.0;
}

bool PrivateJet::canLand(const Runway &runway) const {
    return runway.getLength() >= 1000 && runway.getHasVIPTerminal() == true;
}

AirplaneType PrivateJet::getAirplaneType() const {
    return AirplaneType::PrivateJet;
}

void PrivateJet::completeFlight() {
    if (!canFly()) throw std::runtime_error("Not enough heath for flying");
    health -= 25;
}
