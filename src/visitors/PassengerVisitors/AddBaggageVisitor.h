#pragma once

#include "users/Passenger.h"


class AddBaggageVisitor : public UserVisitor {
    std::shared_ptr<Flight> flight;
    double weight;

public:
    AddBaggageVisitor(std::shared_ptr<Flight> f, double w);

    void visit(Passenger &passenger) override;
};


