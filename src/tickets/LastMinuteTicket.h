//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_LASTMINUTETICKET_H
#define AEROPORT_LASTMINUTETICKET_H
#include "Ticket.h"

class LastMinuteTicket : public Ticket {
public:
    LastMinuteTicket(std::string passengerName, std::string flightId, double basePrice);

    TicketType getTicketType() const override;

    bool isRefundable() const override;

    double getTotalLuggageWeight() const override;
};


#endif //AEROPORT_LASTMINUTETICKET_H
