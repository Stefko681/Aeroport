#include "CargoPlane.h"
#include "core/Engine.h"
#include "facilities/Runway.h"
#include "../visitors/AirplaneVisitors/AirplaneVisitor.h"

CargoPlane::CargoPlane(std::string model, const double health,
                       const size_t maxWeight) : Airplane(std::move(model), health),
                                                 maxWeight(maxWeight) {
    if (maxWeight == 0) throw std::invalid_argument("Max weight must be greater than zero.");
}

AirplaneType CargoPlane::getAirplaneType() const {
    return AirplaneType::CargoPlane;
}

size_t CargoPlane::getAirplaneCapacity() const {
    return maxWeight;
}

bool CargoPlane::canLand(const Runway &runway) const {
    return runway.getRunwayLength() >= 3000.0 && runway.hasHeavyDuty();
}

double CargoPlane::airportFee(const double ticketRevenue) const {
    return 15.0 * static_cast<double>(maxWeight);
}

std::unique_ptr<Airplane> CargoPlane::clone() const {
    return std::make_unique<CargoPlane>(airplaneModel, airplaneHealth, maxWeight);
}

void CargoPlane::completeFlight() {
    if (!canFly()) throw std::runtime_error("Aircraft health too low to complete a flight.");
    airplaneHealth -= 45.0;
}


void CargoPlane::accept(AirplaneVisitor &visitor) {
    visitor.visit(*this);
}
