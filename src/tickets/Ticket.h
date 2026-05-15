//
// Created by stefko on 5/13/26.
//

#ifndef AEROPORT_TICKET_H
#define AEROPORT_TICKET_H
#include "TicketType.h"
#include "infrastructures/Flight.h"
#include <string>


class Ticket {
protected:
    std::string passengerName;
    std::string flightId;
    double paidPrice;
    double weight;

public:
    Ticket(std::string passengerName, std::string flightId, double paidPrice, double weight);

    virtual ~Ticket() = default;

    virtual TicketType getTicketType() const = 0;
};


#endif //AEROPORT_TICKET_H
