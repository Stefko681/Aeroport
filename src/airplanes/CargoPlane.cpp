//
// Created by stefko on 5/14/26.
//

#include "CargoPlane.h"
#include <stdexcept>

CargoPlane::CargoPlane(std::string airplaneId, std::string model,
                       const double health, const double maxWeight)
    : Airplane(std::move(airplaneId), std::move(model), health),
      maxWeight(maxWeight) {
    if (maxWeight <= 0)
        throw std::invalid_argument("Max weight must be greater than zero.");
}

AirplaneType CargoPlane::getAirplaneType() const {
    return AirplaneType::CargoPlane;
}

int CargoPlane::getCapacity() const {
    return static_cast<int>(maxWeight);
}

bool CargoPlane::canLand(const Runway &runway) const {
    return runway.getLength() >= 3000.0 && runway.getHasHeavyDuty();
}

double CargoPlane::airportFee(const double) const {
    return 15.0 * maxWeight;
}

std::unique_ptr<Airplane> CargoPlane::clone(std::string newId) const {
    return std::make_unique<CargoPlane>(std::move(newId), model, health, maxWeight);
}

void CargoPlane::completeFlight() {
    if (!canFly()) throw std::runtime_error("Aircraft health too low to complete a flight.");
    health -= 45.0;
}
