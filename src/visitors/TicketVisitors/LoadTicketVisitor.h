#pragma once

#include <memory>

#include "operations/Flight.h"
#include "tickets/Ticket.h"
#include "../UserVisitors/UserVisitor.h"


class LoadTicketVisitor : public UserVisitor {
    TicketType type;
    std::shared_ptr<Flight> flight;
    double paid;
    double baggage;

public:
    LoadTicketVisitor(TicketType t, std::shared_ptr<Flight> f, double p, double b);

    void visit(Passenger &p) override;
};


