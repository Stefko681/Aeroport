#pragma once

#include "users/Passenger.h"


class UpgradeTicketVisitor : public UserVisitor {
    std::shared_ptr<Flight> flight;
    TicketType type;

public:
    UpgradeTicketVisitor(std::shared_ptr<Flight> f, TicketType t);

    void visit(Passenger &passenger) override;
};


