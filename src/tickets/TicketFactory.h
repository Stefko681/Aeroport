//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_TICKETFACTORY_H
#define AEROPORT_TICKETFACTORY_H
#include <memory>
#include "Ticket.h"
#include "StandardTicket.h"
#include "LastMinuteTicket.h"
#include "VIPTicket.h"


class TicketFactory {
public:
    static std::unique_ptr<Ticket> createTicket(TicketType ticketType, std::string passengerName, std::string flightId,
                                                double paidPrice);
};


#endif //AEROPORT_TICKETFACTORY_H
