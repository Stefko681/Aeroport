//
// Created by stefko on 5/14/26.
//

#include "Passenger.h"
#include "operations/Flight.h"
#include <print>

#include "tickets/TicketFactory.h"

Passenger::Passenger(std::string name, std::string password, const double funds) : User(std::move(name),
        std::move(password)),
    funds(funds) {
}

UserRole Passenger::getUserRole() const {
    return UserRole::Passenger;
}

void Passenger::logout() const {
}

void Passenger::help() const {
    std::println("add-funds [amount] – Adds funds to the personal balance.");
    std::println(
        "list-flights [destination] – Displays all flights to the destination with Scheduled and Delayed statuses.");
    std::println("filter-flights [max_price] – Displays flights with a base price below the specified amount.");
    std::println(
        "book-ticket [flight_id] [ticket_type] – Purchases a ticket () (if seats are available on the aircraft)."
        " Standard – Price = Base Price. Can be cancelled (100% refund)."
        " LastMinute – 50 % discount, Price = Base Price * 0.5. Non - refundable. "
        " VIP – Price = Base Price * 2. Includes 20 kg of baggage.Can be cancelled.");
    std::println(
        "upgrade-ticket [flight_id] [new_ticket_type] – Pay the difference to upgrade to a higher ticket class.");
    std::println(
        "add-baggage [flight_id] [weight] – Adds excess baggage to a purchased ticket for an additional fee of 5 EUR/kg.");
    std::println(
        "cancel-ticket [flight_id] – Cancels a ticket and refunds the amount according to the ticket's policy.");
    std::println("my-tickets – Displays purchased tickets and their flight statuses.");
}

void Passenger::viewProfile() const {
    std::println("Name: {}, Funds: {}", name, funds);
}

void Passenger::addFunds(double amount) const {
    if (funds < 0) throw std::invalid_argument("Cannot add funds less than zero");
}

void Passenger::bookTicket(Flight &flight, const TicketType ticketType) {
    if (!flight.hasAvailableSeats()) throw std::invalid_argument("Flight has no available seats");
    std::unique_ptr<Ticket> newTicket = TicketFactory::createTicket(ticketType, name, flight.getFlightId(),
                                                                    flight.getBasePrice());
    const double actualPrice = newTicket->getPaidPrice();
    if (actualPrice > funds) throw std::runtime_error("Insufficient funds");
    funds -= actualPrice;
    flight.registerSoldTicket(newTicket.get());
    passengerTickets.push_back(std::move(newTicket));
}

void Passenger::upgradeTicket(Flight &flight, const TicketType newTicketType) {
    const auto it = std::ranges::find_if(passengerTickets, [&flight](
                                     const std::unique_ptr<Ticket> &t) {
                                             return t->getFlightId() == flight.getFlightId();
                                         });
    if (it == passengerTickets.end()) throw std::runtime_error("Passenger do not have a ticket for this flight");
    const Ticket *oldTicket = it->get();
    std::unique_ptr<Ticket> newTicket = TicketFactory::createTicket(newTicketType, name, flight.getFlightId(),
                                                                    flight.getBasePrice());
    const double priceDifference = newTicket->getPaidPrice() - oldTicket->getPaidPrice();
    if (priceDifference <= 0) throw std::runtime_error("Passenger can only upgrade to higher class ticket");
    if (funds < priceDifference) throw std::runtime_error("Insufficient funds");
    funds -= priceDifference;
    flight.replaceSoldTicket(oldTicket, newTicket.get());
    *it = std::move(newTicket);
}

void Passenger::addBaggage(Flight &flight, double extraWeight) {
    if (extraWeight <= 0) throw std::invalid_argument("Extra weight cannot be less or equal to zero");
    const auto it = std::ranges::find_if(passengerTickets, [&flight](const std::unique_ptr<Ticket> &t) {
        return t->getFlightId() == flight.getFlightId();
    });
    if (it == passengerTickets.end()) throw::std::runtime_error("Passenger do not have a ticket for this flight");
    const Ticket *oldTicket = it->get();
    const double baggageFee = 5.0 * extraWeight;
    if (funds < extraWeight)throw std::runtime_error("Insufficient funds");
    funds -= baggageFee;
    (*it)->addExtraBaggage(extraWeight);
}

void Passenger::cancelTicket(Flight &flight) {
    auto ticketToCancel = passengerTickets.end();
    double maxRefundPrice = -1.0;
    bool isNotRefundable = false;
    for (auto it = passengerTickets.begin(); it != passengerTickets.end(); ++it) {
        if ((*it)->getFlightId() == flight.getFlightId()) {
            if ((*it)->isRefundable()) {
                if ((*it)->getPaidPrice() > maxRefundPrice) {
                    maxRefundPrice = (*it)->getPaidPrice();
                    ticketToCancel = it;
                }
            } else isNotRefundable = true;
        }
    }
    if (maxRefundPrice == -1 && ticketToCancel == passengerTickets.end()) throw std::runtime_error
}

void Passenger::printMyTickets() const {
}
