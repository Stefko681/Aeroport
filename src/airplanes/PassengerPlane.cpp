#include "PassengerPlane.h"
#include <stdexcept>
#include "core/Engine.h"
#include "facilities/Runway.h"
#include "../visitors/AirplaneVisitors/AirplaneVisitor.h"
PassengerPlane::PassengerPlane(std::string model, const double health,
                               const size_t maxPassengers) : Airplane(std::move(model), health),
                                                          maxPassengers(maxPassengers) {
    if (maxPassengers == 0) throw std::invalid_argument("Max passengers must be greater than zero.");
}

AirplaneType PassengerPlane::getAirplaneType() const {
    return AirplaneType::PassengerPlane;
}

size_t PassengerPlane::getAirplaneCapacity() const {
    return maxPassengers;
}

bool PassengerPlane::canLand(const Runway &runway) const {
    return runway.getRunwayLength() >= 2000.0;
}

double PassengerPlane::airportFee(const double ticketRevenue) const {
    return ticketRevenue * 0.10;
}

std::unique_ptr<Airplane> PassengerPlane::clone() const {
    return std::make_unique<PassengerPlane>(airplaneModel, airplaneHealth, maxPassengers);
}

void PassengerPlane::completeFlight() {
    if (!canFly()) throw std::runtime_error("Aircraft health too low to complete a flight.");
    airplaneHealth -= 35.0;
}

void PassengerPlane::accept(AirplaneVisitor &visitor) {
    visitor.visit(*this);
}
