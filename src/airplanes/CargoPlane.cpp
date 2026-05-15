//
// Created by stefko on 5/14/26.
//

#include "CargoPlane.h"
#include <stdexcept>

CargoPlane::CargoPlane(std::string airplaneId, std::string model, const double health,
                       const double maxWeight) : Airplane(std::move(airplaneId), std::move(model), health),
                                                 maxWeight(maxWeight) {
    if (maxWeight <= 0) throw std::invalid_argument("Max Weigh can not be less or equal to zero");
}

AirplaneType CargoPlane::getAirplaneType() const {
    return AirplaneType::CargoPlane;
}

double CargoPlane::airportFee(const double ticketRevenue) const {
    return 15 * maxWeight;
}

void CargoPlane::completeFlight() {
    if (!canFly()) throw std::runtime_error("Not enough heath for flying");
    health -= 45;
}

bool CargoPlane::canLand(const Runway &runway) const {
    return runway.getLength() >= 3000 && runway.getHasHeavyDuty();
}
