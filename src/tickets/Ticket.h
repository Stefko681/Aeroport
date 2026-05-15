//
// Created by stefko on 5/13/26.
//

#ifndef AEROPORT_TICKET_H
#define AEROPORT_TICKET_H
#include "TicketType.h"
#include "../operations/Flight.h"
#include <string>


class Ticket {
protected:
    std::string passengerName;
    std::string flightId;
    double paidPrice;
    double extraLuggageWeight;

public:
    Ticket(std::string passengerName, std::string flightId, double paidPrice);

    virtual ~Ticket() = default;

    virtual TicketType getTicketType() const = 0;

    virtual bool isRefundable() const = 0;

    virtual double getTotalLuggageWeight() const = 0;

    void addExtraLuaggage(double weight);
};


#endif //AEROPORT_TICKET_H
