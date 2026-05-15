//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_VIPTICKET_H
#define AEROPORT_VIPTICKET_H
#include "Ticket.h"

class VIPTicket : public Ticket {
public:
    VIPTicket(std::string passengerName, std::string flightId, double basePrice);

    TicketType getTicketType() const override;

    bool isRefundable() const override;

    double getTotalLuggageWeight() const override;
};


#endif //AEROPORT_VIPTICKET_H
