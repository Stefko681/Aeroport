//
// Created by stefko on 5/14/26.
//

#include "CargoPlane.h"
#include <stdexcept>

CargoPlane::CargoPlane(std::string airplaneId, std::string model, const double health,
                       const double maxWeigh) : Airplane(std::move(airplaneId), std::move(model), health),
                                                maxWeigh(maxWeigh) {
    if (maxWeigh <= 0) throw std::invalid_argument("Max Weigh can not be less or equal to zero");
}

AirplaneType CargoPlane::getAirplaneType() const {
    return AirplaneType::CargoPlane;
}

double CargoPlane::airportFee(const double ticketRevenue) const {
    return maxWeigh;
}

void CargoPlane::completeFlight() {
    if (!canFly()) throw std::runtime_error("Not enough heath for flying");
    health -= (0.45 * health);
}

bool CargoPlane::canLand(const double length, bool hasVIPTerminal) const {
    return length >= 3000;
}
