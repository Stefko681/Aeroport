//
// Created by stefko on 5/14/26.
//

#include "PassengerPlane.h"
#include <stdexcept>

PassengerPlane::PassengerPlane(std::string airplaneId, std::string model,
                               const double health, const int maxPassengers)
    : Airplane(std::move(airplaneId), std::move(model), health),
      maxPassengers(maxPassengers) {
    if (maxPassengers <= 0)
        throw std::invalid_argument("Max passengers must be greater than zero.");
}

AirplaneType PassengerPlane::getAirplaneType() const {
    return AirplaneType::PassengerPlane;
}

int PassengerPlane::getCapacity() const {
    return maxPassengers;
}

bool PassengerPlane::canLand(const Runway &runway) const {
    return runway.getLength() >= 2000.0;
}

double PassengerPlane::airportFee(const double ticketRevenue) const {
    return ticketRevenue * 0.10;
}

std::unique_ptr<Airplane> PassengerPlane::clone(std::string newId) const {
    return std::make_unique<PassengerPlane>(std::move(newId), model, health, maxPassengers);
}

void PassengerPlane::completeFlight() {
    if (!canFly()) throw std::runtime_error("Aircraft health too low to complete a flight.");
    health -= 35.0;
}
