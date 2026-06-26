#include "SaveAirplaneCapacityVisitor.h"
#include "airplanes/CargoPlane.h"
#include "airplanes/PassengerPlane.h"
#include "airplanes/PrivateJet.h"

SaveAirplaneCapacityVisitor::SaveAirplaneCapacityVisitor(std::ostream &os) : out(os) {
}

void SaveAirplaneCapacityVisitor::visit(PassengerPlane &p) {
    out << p.getAirplaneCapacity();
}

void SaveAirplaneCapacityVisitor::visit(CargoPlane &p) {
    out << p.getAirplaneCapacity();
}

void SaveAirplaneCapacityVisitor::visit(PrivateJet &p) {
    out << p.getAirplaneCapacity();
}
