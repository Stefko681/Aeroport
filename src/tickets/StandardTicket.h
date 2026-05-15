//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_STANDARDTICKET_H
#define AEROPORT_STANDARDTICKET_H
#include "Ticket.h"

class StandardTicket : public Ticket {
public:
    StandardTicket(std::string passengerName, std::string flightId, double basePrice);

    TicketType getTicketType() const override;

    bool isRefundable() const override;

    double getTotalLuggageWeight() const override;
};


#endif //AEROPORT_STANDARDTICKET_H
