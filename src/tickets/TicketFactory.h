#pragma once

#include <memory>
#include "Ticket.h"


class TicketFactory {
public:
    static std::unique_ptr<Ticket> create(TicketType ticketType, std::string passengerName, std::string flightId,
                                          double paidPrice);
};


