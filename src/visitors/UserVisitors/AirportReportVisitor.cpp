#include "AirportReportVisitor.h"
#include "airplanes/Airplane.h"
#include "operations/Flight.h"

void AirportReportVisitor::process(const Flight &flight) {
    currentTax = flight.getAirportTax();
    if (auto plane = flight.getAirplane()) {
        plane->accept(*this);
    }
}

void AirportReportVisitor::visit(PassengerPlane &) {
    passengerTax += currentTax;
}

void AirportReportVisitor::visit(CargoPlane &) {
    cargoTax += currentTax;
}

void AirportReportVisitor::visit(PrivateJet &) {
    privateTax += currentTax;
}

double AirportReportVisitor::getCargoTax() const {
    return cargoTax;
}

double AirportReportVisitor::getPassengerTax() const {
    return passengerTax;
}

double AirportReportVisitor::getPrivateTax() const {
    return privateTax;
}

double AirportReportVisitor::getTotal() const {
    return passengerTax + cargoTax + privateTax;
}
