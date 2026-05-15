//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_PASSENGER_H
#define AEROPORT_PASSENGER_H
#include "User.h"
#include "../tickets/Ticket.h"
#include "../operations/Flight.h"
#include <vector>
#include <string>
#include <memory>

class Passenger : public User {
    double funds;
    std::vector<std::unique_ptr<Ticket> > tickets_;

public:
    Passenger(std::string name, std::string password, double funds);

    ~Passenger() override = default;

    void addFunds(double amount);

    void bookTicket(Flight &flight, TicketType &ticketTYpe);


};


#endif //AEROPORT_PASSENGER_H
