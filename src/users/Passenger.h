//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_PASSENGER_H
#define AEROPORT_PASSENGER_H
#pragma once
#include "User.h"
#include "tickets/TicketType.h"
#include <memory>
#include <string>
#include <vector>

class Ticket;
class Flight;

class Passenger : public User {
    struct TicketEntry {
        std::unique_ptr<Ticket> ticket;
        Flight *flight;
    };

    double funds;
    std::vector<TicketEntry> passengerTickets;

public:
    explicit Passenger(std::string name, std::string password, double funds = 0.0);

    ~Passenger() override = default;

    Passenger(const Passenger &) = delete;

    Passenger &operator=(const Passenger &) = delete;

    Passenger(Passenger &&) noexcept = default;

    Passenger &operator=(Passenger &&) noexcept = default;

    [[nodiscard]] UserRole getUserRole() const override;

    void logout() const override;

    void help() const override;

    void viewProfile() const override;

    void addFunds(double amount);

    void bookTicket(Flight &flight, TicketType ticketType);

    void upgradeTicket(Flight &flight, TicketType newTicketType);

    void addBaggage(const Flight &flight, double extraWeight);

    void cancelTicket(Flight &flight);

    void printMyTickets() const;

    [[nodiscard]] double getFunds() const;

    void forceRefundTicket(const std::string &flightId, double amount);
};

#endif //AEROPORT_PASSENGER_H
