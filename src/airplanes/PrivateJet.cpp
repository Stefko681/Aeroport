#include "PrivateJet.h"
#include "core/Engine.h"
#include "facilities/Runway.h"
#include "../visitors/AirplaneVisitors/AirplaneVisitor.h"

PrivateJet::PrivateJet(std::string model, const double health) : Airplane(std::move(model), health) {
}

AirplaneType PrivateJet::getAirplaneType() const {
    return AirplaneType::PrivateJet;
}

size_t PrivateJet::getAirplaneCapacity() const {
    return CAPACITY;
}

bool PrivateJet::canLand(const Runway &runway) const {
    return runway.getRunwayLength() >= 1000.0 && runway.hasVIPTerminal();
}

double PrivateJet::airportFee(const double) const {
    return 5000.0;
}

std::unique_ptr<Airplane> PrivateJet::clone() const {
    return std::make_unique<PrivateJet>(airplaneModel, airplaneHealth);
}

void PrivateJet::completeFlight() {
    if (!canFly()) throw std::runtime_error("Aircraft health too low to complete a flight.");
    airplaneHealth -= 25.0;
}

void PrivateJet::accept(AirplaneVisitor &visitor) {
    visitor.visit(*this);
}

