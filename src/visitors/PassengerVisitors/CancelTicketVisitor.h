#pragma once

#include "users/Passenger.h"


class CancelTicketVisitor : public UserVisitor {
    std::shared_ptr<Flight> flight;

public:
    explicit CancelTicketVisitor(std::shared_ptr<Flight> f);

    void visit(Passenger &passenger) override;
};


