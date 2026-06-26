#include "Passenger.h"
#include "operations/Flight.h"
#include "airplanes/Airplane.h"
#include "tickets/Ticket.h"
#include "tickets/TicketFactory.h"
#include <algorithm>
#include <format>
#include <print>
#include <stdexcept>

Passenger::Passenger(std::string name, std::string password, const double funds) : User(std::move(name),
    std::move(password)), funds(funds) {
    if (funds < 0)throw std::invalid_argument("Initial funds cannot be negative.");
}

UserRole Passenger::getUserRole() const {
    return UserRole::Passenger;
}

void Passenger::help() const {
    std::println("[System] Available commands for Passenger:");
    std::println("  add-funds [amount]                    - Add funds to your balance.");
    std::println("  list-flights [destination]            - List Scheduled/Delayed flights to a destination.");
    std::println("  filter-flights [max_price]            - List flights whose base price is below max_price.");
    std::println("  book-ticket [flight_id] [type]        - Buy a ticket: Standard | LastMinute | VIP.");
    std::println("  upgrade-ticket [flight_id] [type]     - Upgrade a Standard ticket to VIP (pay difference).");
    std::println("  add-baggage [flight_id] [weight]      - Add extra baggage at 5 EUR/kg.");
    std::println("  cancel-ticket [flight_id]             - Cancel a refundable ticket (Standard or VIP).");
    std::println("  my-tickets                            - Show all your tickets and their flight status.");
    std::println("  view-profile                          - Show your profile.");
    std::println("  logout                                - Log out.");
}

void Passenger::viewProfile() const {
    std::println("[Profile] User: {} | Role: Passenger | Balance: {:.2f} EUR", name, funds);
}

std::expected<void, std::string> Passenger::addFunds(const double amount) {
    if (amount <= 0) return std::unexpected("Amount must be greater than zero.");
    funds += amount;
    std::println("[System] Funds added successfully. New balance: {:.2f} EUR.", funds);
    return {};
}

std::expected<void, std::string> Passenger::bookTicket(const std::shared_ptr<Flight> &flight,
                                                       const TicketType ticketType) {
    if (flight->getAirplaneType() == AirplaneType::CargoPlane && ticketType == TicketType::VIPTicket)
        return std::unexpected("You cannot purchase VIP tickets for Cargo flights!");
    if (const FlightStatus status = flight->getFlightStatus();
        status != FlightStatus::Scheduled && status != FlightStatus::Delayed)
        return std::unexpected(std::format("Flight {} is not accepting tickets.", flight->getFlightId()));
    if (!flight->hasAvailableSeats())
        return std::unexpected(std::format("No available seats on flight {}.", flight->getFlightId()));
    std::shared_ptr<Ticket> newTicket(
        TicketFactory::create(ticketType, name, flight->getFlightId(), flight->getBasePrice()));
    const double price = newTicket->getPaidPrice();
    if (price > funds)
        return std::unexpected(
            std::format("Insufficient funds! Your balance: {:.2f} EUR. Ticket price: {:.2f} EUR.", funds, price));
    funds -= price;
    flight->registerSoldTicket(newTicket);
    passengerTickets.push_back({newTicket, flight});
    if (flight->getAirplaneType() == AirplaneType::CargoPlane) {
        std::println("[Success] Reserved 1 ton of cargo space for {}. Paid: {:.2f} EUR. Current balance: {:.2f} EUR.",
                     flight->getFlightId(), price, funds);
    } else {
        switch (ticketType) {
            case TicketType::StandardTicket:
                std::println("[Success] Standard ticket booked for {}. Paid: {:.2f} EUR. Current balance: {:.2f} EUR.",
                             flight->getFlightId(), price, funds);
                break;
            case TicketType::LastMinuteTicket:
                std::println(
                    "[Success] LastMinute ticket booked for {}. Paid: {:.2f} EUR (50% discount). Current balance: {:.2f} EUR.",
                    flight->getFlightId(), price, funds);
                break;
            case TicketType::VIPTicket:
                std::println(
                    "[Success] VIP ticket booked for {}. Paid: {:.2f} EUR (+20kg free baggage). Current balance: {:.2f} EUR.",
                    flight->getFlightId(), price, funds);
                break;
        }
    }
    return {};
}

std::expected<void, std::string> Passenger::upgradeTicket(std::shared_ptr<Flight> flight,
                                                          const TicketType newTicketType) {
    if (newTicketType != TicketType::VIPTicket) return std::unexpected("You can only upgrade to VIP class.");
    if (flight->getAirplaneType() == AirplaneType::CargoPlane)
        return std::unexpected(
            "Cargo flights do not support VIP upgrades.");
    auto it = std::ranges::find_if(passengerTickets, [&](const TicketEntry &e) {
        return e.ticket->getFlightId() == flight->getFlightId() && e.ticket->
               getTicketType() == TicketType::StandardTicket;
    });
    if (it == passengerTickets.end()) return std::unexpected("No upgradeable ticket found.");
    const Ticket *oldTicket = it->ticket.get();
    std::shared_ptr<Ticket> newTicket(
        TicketFactory::create(TicketType::VIPTicket, name, flight->getFlightId(), flight->getBasePrice()));
    const double priceDifference = newTicket->getPaidPrice() - oldTicket->getPaidPrice();
    if (priceDifference <= 0) return std::unexpected("VIP price is not higher than the current ticket price.");
    if (funds < priceDifference) return std::unexpected("Insufficient funds! Upgrade costs too much.");
    funds -= priceDifference;
    flight->replaceSoldTicket(it->ticket, newTicket);
    std::println(
        "[Success] Standard ticket upgraded to VIP (+20kg free baggage). Paid difference: {:.2f} EUR. Current balance: {:.2f} EUR.",
        priceDifference, funds);
    it->ticket = newTicket;
    return {};
}

std::expected<void, std::string> Passenger::addBaggage(std::shared_ptr<Flight> flight, const double extraWeight) {
    if (extraWeight <= 0) return std::unexpected("Baggage weight must be greater than zero.");
    const auto it = std::ranges::find_if(passengerTickets, [&](const TicketEntry &e) {
        return e.ticket->getFlightId() == flight->getFlightId();
    });
    if (it == passengerTickets.end())
        return std::unexpected(
            "You do not have a ticket for flight " + flight->getFlightId() + ".");
    const double fee = 5.0 * extraWeight;
    if (funds < fee) return std::unexpected(std::format("Insufficient funds! Baggage fee: {:.2f} EUR.", fee));
    funds -= fee;
    it->ticket->addExtraBaggage(extraWeight);
    std::println("[Success] Added {:.0f} kg baggage to {} ticket. Fee: {:.2f} EUR. Current balance: {:.2f} EUR.",
                 extraWeight, flight->getFlightId(), fee, funds);
    return {};
}

std::expected<void, std::string> Passenger::cancelTicket(const std::shared_ptr<Flight> &flight) {
    int matchCount = 0;
    auto bestRefundable = passengerTickets.end();
    double maxRefundPrice = -1.0;
    Ticket *nonRefundableTicket = nullptr;
    for (auto it = passengerTickets.begin(); it != passengerTickets.end(); ++it) {
        if (it->ticket->getFlightId() != flight->getFlightId()) continue;
        ++matchCount;
        if (it->ticket->isRefundable()) {
            if (it->ticket->getPaidPrice() > maxRefundPrice) {
                maxRefundPrice = it->ticket->getPaidPrice();
                bestRefundable = it;
            }
        } else {
            nonRefundableTicket = it->ticket.get();
        }
    }
    if (bestRefundable == passengerTickets.end()) {
        if (nonRefundableTicket) {
            const char *typeLabel = (nonRefundableTicket->getTicketType() == TicketType::LastMinuteTicket)
                                        ? "LastMinute"
                                        : "Unknown";
            return std::unexpected(std::format("Your remaining ticket for {} is '{}' type, which is non-refundable!",
                                               flight->getFlightId(), typeLabel));
        }
        return std::unexpected("No refundable ticket found.");
    }
    if (matchCount > 1) {
        const char *typeLabel = (bestRefundable->ticket->getTicketType() == TicketType::VIPTicket) ? "VIP" : "Standard";
        std::println(
            "[System] Multiple tickets found for {}. Auto-selecting the highest class refundable ticket ({})...",
            flight->getFlightId(), typeLabel);
    }
    const double refundAmount = bestRefundable->ticket->getPaidPrice();
    const char *typeLabel = (bestRefundable->ticket->getTicketType() == TicketType::VIPTicket) ? "VIP" : "Standard";
    flight->unregisterSoldTicket(bestRefundable->ticket);
    funds += refundAmount;
    passengerTickets.erase(bestRefundable);
    std::println("[Success] {} ticket for {} cancelled. Refunded: {:.2f} EUR. Current balance: {:.2f} EUR.", typeLabel,
                 flight->getFlightId(), refundAmount, funds);
    return {};
}

void Passenger::printMyTickets() const {
    if (passengerTickets.empty()) {
        std::println("You have no active tickets.");
        return;
    }
    std::println("Your active tickets:");
    int idx = 1;
    for (const auto &[ticket, weakFlight]: passengerTickets) {
        if (auto flight = weakFlight.lock()) {
            const char *typeLabel = "Standard";
            switch (ticket->getTicketType()) {
                case TicketType::StandardTicket: typeLabel = "Standard";
                    break;
                case TicketType::LastMinuteTicket: typeLabel = "LastMinute";
                    break;
                case TicketType::VIPTicket: typeLabel = "VIP";
                    break;
            }
            const char *statusLabel = "Scheduled";
            switch (flight->getFlightStatus()) {
                case FlightStatus::Scheduled: statusLabel = "Scheduled";
                    break;
                case FlightStatus::Boarding: statusLabel = "Boarding";
                    break;
                case FlightStatus::Delayed: statusLabel = "Delayed";
                    break;
                case FlightStatus::Departed: statusLabel = "Departed";
                    break;
                case FlightStatus::Cancelled: statusLabel = "Cancelled";
                    break;
            }
            std::println("{}. Flight: {} | Type: {} | Paid: {:.2f} EUR | Baggage: {:.0f} kg | Status: {}", idx++,
                         ticket->getFlightId(), typeLabel, ticket->getPaidPrice(), ticket->getTotalLuggageWeight(),
                         statusLabel);
        }
    }
}

double Passenger::refundAllTicketsForFlight(const std::string &flightId) {
    double total = 0.0;
    for (auto it = passengerTickets.begin(); it != passengerTickets.end();) {
        if (it->ticket->getFlightId() == flightId) {
            total += it->ticket->getPaidPrice();
            if (auto flight = it->flight.lock()) flight->unregisterSoldTicket(it->ticket);
            it = passengerTickets.erase(it);
        } else {
            ++it;
        }
    }
    funds += total;
    return total;
}

std::vector<TicketSnapshot> Passenger::getTicketSnapshot() const {
    std::vector<TicketSnapshot> out;
    for (const auto &[ticket, flight]: passengerTickets) {
        const double total = ticket->getTotalLuggageWeight();
        const double extra = (ticket->getTicketType() == TicketType::VIPTicket) ? (total - 20.0) : total;
        out.push_back({ticket->getFlightId(), ticket->getTicketType(), ticket->getPaidPrice(), extra});
    }
    return out;
}

std::expected<void, std::string> Passenger::loadTicket(const TicketType type, std::shared_ptr<Flight> flight,
                                                       double paid, double baggage) {
    double baseForFactory = paid;
    switch (type) {
        case TicketType::LastMinuteTicket: baseForFactory = paid * 2;
            break;
        case TicketType::VIPTicket: baseForFactory = paid / 2;
            break;
        default: break;
    }
    std::shared_ptr<Ticket> ticket(TicketFactory::create(type, name, flight->getFlightId(), baseForFactory));
    if (baggage > 0.0) ticket->addExtraBaggage(baggage);
    flight->registerSoldTicket(ticket);
    passengerTickets.push_back({ticket, flight});
    return {};
}

void Passenger::accept(UserVisitor &visitor) {
    visitor.visit(*this);
}

double Passenger::getFunds() const {
    return funds;
}
