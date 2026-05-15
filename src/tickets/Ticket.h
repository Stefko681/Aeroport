//
// Created by stefko on 5/13/26.
//

#ifndef AEROPORT_TICKET_H
#define AEROPORT_TICKET_H
#include <ranges>

#include "TicketType.h"
#include "infrastructures/Flight.h"
#include <string>

class Ticket {
protected:
    std::string passengerName;
    Flight flight;
    TicketType ticketType;
    double paidPrice;
    double weight;

public:
    Ticket(std::string &passengerName, Flight &flight, TicketType &ticketType, double paidPrice, double weight);
};


#endif //AEROPORT_TICKET_H
