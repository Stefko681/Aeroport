#pragma once

#include <expected>
#include "User.h"
#include "tickets/Ticket.h"
#include <memory>
#include <string>
#include <vector>

class Ticket;
class Flight;


struct TicketEntry {
    std::shared_ptr<Ticket> ticket;
    std::weak_ptr<Flight> flight;
};

struct TicketSnapshot {
    std::string flightId;
    TicketType type;
    double paid;
    double baggage;
};

class Passenger final : public User {
    double funds{0.0};
    std::vector<TicketEntry> passengerTickets;

public:
    Passenger(std::string name, std::string password, double funds = 0.0);

    Passenger(const Passenger &other) = delete;

    Passenger &operator=(const Passenger &other) = delete;

    Passenger(Passenger &&other) noexcept = default;

    Passenger &operator=(Passenger &&other) noexcept = default;

    ~Passenger() override = default;

    [[nodiscard]] double getFunds() const;

    [[nodiscard]] UserRole getUserRole() const override;

    [[nodiscard]] std::vector<TicketSnapshot> getTicketSnapshot() const;

    void help() const override;

    void viewProfile() const override;

    void printMyTickets() const;

    std::expected<void, std::string> addFunds(double amount);

    std::expected<void, std::string> addBaggage(std::shared_ptr<Flight> flight, double extraWeight);

    std::expected<void, std::string> bookTicket(const std::shared_ptr<Flight>& flight, TicketType ticketType);

    std::expected<void, std::string> upgradeTicket(std::shared_ptr<Flight> flight, TicketType newTicketType);

    std::expected<void, std::string> cancelTicket(const std::shared_ptr<Flight>& flight);

    double refundAllTicketsForFlight(const std::string &flightId);

    std::expected<void, std::string> loadTicket(TicketType type, std::shared_ptr<Flight> flight, double paid,
                                                double baggage);

    void accept(UserVisitor &visitor) override;
};

