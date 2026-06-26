#pragma once

#include "users/Passenger.h"


class MyTicketsVisitor : public UserVisitor {
public:
    void visit(Passenger &passenger) override;
};


