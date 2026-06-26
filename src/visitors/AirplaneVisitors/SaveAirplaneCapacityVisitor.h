#pragma once

#include "AirplaneVisitor.h"
#include <ostream>


class SaveAirplaneCapacityVisitor : public AirplaneVisitor {
    std::ostream &out;

public:
    explicit SaveAirplaneCapacityVisitor(std::ostream &os);

    void visit(PassengerPlane &p) override;

    void visit(CargoPlane &p) override;

    void visit(PrivateJet &p) override;
};
