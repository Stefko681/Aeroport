#pragma once

#include "users/Passenger.h"


class AddFundsVisitor : public UserVisitor {
    double amount;

public:
    explicit AddFundsVisitor(double amt);

    void visit(Passenger &passenger) override;
};


