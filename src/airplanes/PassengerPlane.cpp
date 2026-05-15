//
// Created by stefko on 5/14/26.
//

#include "PassengerPlane.h"

#include <stdexcept>

PassengerPlane::PassengerPlane(std::string airplaneId, std::string model, const int health,
                               const int maxPassengers) : Airplane(std::move(airplaneId), std::move(model), health),
                                                          maxPassengers(maxPassengers) {
    if (maxPassengers <= 0) throw std::invalid_argument("Max Passengers can not be less or equal to 0");
}

void PassengerPlane::completeFlight() {
    if (!canFly()) throw std::runtime_error("Not enough health for flying");
    health -= 0.35;
}

bool PassengerPlane::canLand(const Runway &runway) const {
    return runway.getLength() >= 2000;
}

double PassengerPlane::airportFee(const double ticketRevenue) const {
    return (0.10 * ticketRevenue);
}

AirplaneType PassengerPlane::getAirplaneType() const {
    return AirplaneType::PassengerPlane;
}
