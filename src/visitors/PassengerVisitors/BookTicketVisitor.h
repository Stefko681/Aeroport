#pragma once

#include "users/Passenger.h"


class BookTicketVisitor : public UserVisitor {
    std::shared_ptr<Flight> flight;
    TicketType type;

public:
    BookTicketVisitor(std::shared_ptr<Flight> f, TicketType t);

    void visit(Passenger &passenger) override;
};

