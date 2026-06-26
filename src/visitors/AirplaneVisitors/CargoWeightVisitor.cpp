#include "CargoWeightVisitor.h"
#include "airplanes/CargoPlane.h"

void CargoWeightVisitor::visit(CargoPlane &plane) {
    weight = plane.getAirplaneCapacity();
}

void CargoWeightVisitor::visit(PassengerPlane &plane) {
}

void CargoWeightVisitor::visit(PrivateJet &plane) {
}

size_t CargoWeightVisitor::getWeight() const {
    return weight;
}
