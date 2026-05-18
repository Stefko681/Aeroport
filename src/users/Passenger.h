//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_PASSENGER_H
#define AEROPORT_PASSENGER_H
#include "User.h"
#include "tickets/TicketType.h"
#include <vector>
#include <string>
#include <memory>

class Ticket;
class Flight;

class Passenger : public User {
    double funds;
    std::vector<std::unique_ptr<Ticket> > passengerTickets;

public:
    Passenger(std::string name, std::string password, double funds = 0.0);

    ~Passenger() override = default;

    Passenger(const Passenger &other) = delete;

    Passenger &operator=(const Passenger &other) = delete;

    Passenger(Passenger &&other) noexcept = default;

    Passenger &operator=(Passenger &&) noexcept = default;

    [[nodiscard]] UserRole getUserRole() const override;

    void logout() const override;

    void help() const override;

    void viewProfile() const override;

    void addFunds(double amount) const;

    void bookTicket(Flight &flight, TicketType ticketType);

    void upgradeTicket(Flight &flight, TicketType newTicketType);

    void addBaggage(Flight &flight, double extraWeight);

    void cancelTicket(Flight &flight);

    void printMyTickets() const;
};


#endif //AEROPORT_PASSENGER_H
