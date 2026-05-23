//
// Created by stefko on 5/14/26.
//

#include "Passenger.h"
#include "operations/Flight.h"
#include "operations/FlightStatus.h"
#include "airplanes/AirplaneType.h"
#include "tickets/Ticket.h"
#include "tickets/TicketFactory.h"
#include <algorithm>
#include <format>
#include <print>
#include <stdexcept>

Passenger::Passenger(std::string name, std::string password, const double funds)
    : User(std::move(name), std::move(password)), funds(funds) {
    if (funds < 0)
        throw std::invalid_argument("Initial funds cannot be negative.");
}

UserRole Passenger::getUserRole() const {
    return UserRole::Passenger;
}

void Passenger::logout() const {
    std::println("[System] Logged out successfully.");
}

void Passenger::help() const {
    std::println("[System] Available commands for Passenger:");
    std::println("  add-funds [amount]                    – Add funds to your balance.");
    std::println("  list-flights [destination]            – List Scheduled/Delayed flights to a destination.");
    std::println("  filter-flights [max_price]            – List flights whose base price is below max_price.");
    std::println("  book-ticket [flight_id] [type]        – Buy a ticket: Standard | LastMinute | VIP.");
    std::println("  upgrade-ticket [flight_id] [type]     – Upgrade a Standard ticket to VIP (pay difference).");
    std::println("  add-baggage [flight_id] [weight]      – Add extra baggage at 5 EUR/kg.");
    std::println("  cancel-ticket [flight_id]             – Cancel a refundable ticket (Standard or VIP).");
    std::println("  my-tickets                            – Show all your tickets and their flight status.");
    std::println("  view-profile                          – Show your profile.");
    std::println("  logout                                – Log out.");
}

void Passenger::viewProfile() const {
    std::println("[Profile] User: {} | Role: Passenger | Balance: {:.2f} EUR", name, funds);
}

double Passenger::getFunds() const {
    return funds;
}

void Passenger::addFunds(const double amount) {
    if (amount <= 0)
        throw std::invalid_argument("Amount must be greater than zero.");
    funds += amount;
    std::println("[System] Funds added successfully. New balance: {:.2f} EUR.", funds);
}

void Passenger::bookTicket(Flight &flight, const TicketType ticketType) {
    if (flight.getAirplaneType() == AirplaneType::CargoPlane &&
        ticketType == TicketType::VIPTicket) {
        throw std::runtime_error("You cannot purchase VIP tickets for Cargo flights!");
    }
    if (const FlightStatus status = flight.getFlightStatus();
        status != FlightStatus::Scheduled && status != FlightStatus::Delayed) {
        throw std::runtime_error(
            std::format("Flight {} is not accepting tickets (status must be Scheduled or Delayed).",
                        flight.getFlightId()));
    }
    if (!flight.hasAvailableSeats()) {
        throw std::runtime_error(
            std::format("No available seats on flight {}.", flight.getFlightId()));
    }
    auto newTicket = TicketFactory::createTicket(
        ticketType, name, flight.getFlightId(), flight.getBasePrice());

    const double price = newTicket->getPaidPrice();
    if (price > funds) {
        throw std::runtime_error(
            std::format("Insufficient funds! Your balance: {:.2f} EUR. Ticket price: {:.2f} EUR.",
                        funds, price));
    }
    funds -= price;
    flight.registerSoldTicket(newTicket.get());
    passengerTickets.push_back({std::move(newTicket), &flight});
    if (flight.getAirplaneType() == AirplaneType::CargoPlane) {
        std::println("[Success] Reserved 1 ton of cargo space for {}. Paid: {:.2f} EUR. Current balance: {:.2f} EUR.",
                     flight.getFlightId(), price, funds);
    } else if (ticketType == TicketType::LastMinuteTicket) {
        std::println(
            "[Success] LastMinute ticket booked for {}. Paid: {:.2f} EUR (50% discount). Current balance: {:.2f} EUR.",
            flight.getFlightId(), price, funds);
    } else if (ticketType == TicketType::VIPTicket) {
        std::println("[Success] VIP ticket booked for {}. Paid: {:.2f} EUR. Current balance: {:.2f} EUR.",
                     flight.getFlightId(), price, funds);
    } else {
        std::println("[Success] Standard ticket booked for {}. Paid: {:.2f} EUR. Current balance: {:.2f} EUR.",
                     flight.getFlightId(), price, funds);
    }
}

void Passenger::upgradeTicket(Flight &flight, const TicketType newTicketType) {
    if (newTicketType != TicketType::VIPTicket) {
        throw std::runtime_error("You can only upgrade to VIP class.");
    }
    if (flight.getAirplaneType() == AirplaneType::CargoPlane) {
        throw std::runtime_error("Cargo flights do not support VIP upgrades.");
    }
    auto it = passengerTickets.end();
    bool hasAnyTicket = false;
    for (auto i = passengerTickets.begin(); i != passengerTickets.end(); ++i) {
        if (i->ticket->getFlightId() == flight.getFlightId()) {
            hasAnyTicket = true;
            if (i->ticket->getTicketType() == TicketType::StandardTicket) {
                it = i;
                break;
            }
        }
    }

    if (it == passengerTickets.end()) {
        if (hasAnyTicket) {
            throw std::runtime_error(
                "No upgradeable ticket found for flight " + flight.getFlightId() +
                ". Only Standard tickets can be upgraded.");
        }
        throw std::runtime_error(
            "You do not have a ticket for flight " + flight.getFlightId() + ".");
    }
    const Ticket *oldTicket = it->ticket.get();
    auto newTicket = TicketFactory::createTicket(
        TicketType::VIPTicket, name, flight.getFlightId(), flight.getBasePrice());

    const double priceDifference = newTicket->getPaidPrice() - oldTicket->getPaidPrice();
    if (priceDifference <= 0) {
        throw std::runtime_error("VIP price is not higher than the current ticket price.");
    }
    if (funds < priceDifference) {
        throw std::runtime_error(
            std::format("Insufficient funds! Upgrade costs {:.2f} EUR. Your balance: {:.2f} EUR.",
                        priceDifference, funds));
    }
    funds -= priceDifference;
    flight.replaceSoldTicket(oldTicket, newTicket.get());
    std::println("[Success] Standard ticket upgraded to VIP (+20kg free baggage). "
                 "Paid difference: {:.2f} EUR. Current balance: {:.2f} EUR.",
                 priceDifference, funds);
    it->ticket = std::move(newTicket);
}

void Passenger::addBaggage(const Flight &flight, const double extraWeight) {
    if (extraWeight <= 0)
        throw std::invalid_argument("Baggage weight must be greater than zero.");
    const auto it = std::ranges::find_if(passengerTickets, [&](const TicketEntry &e) {
        return e.ticket->getFlightId() == flight.getFlightId();
    });
    if (it == passengerTickets.end()) {
        throw std::runtime_error(
            "You do not have a ticket for flight " + flight.getFlightId() + ".");
    }
    const double fee = 5.0 * extraWeight;
    if (funds < fee) {
        throw std::runtime_error(
            std::format("Insufficient funds! Baggage fee: {:.2f} EUR. Your balance: {:.2f} EUR.",
                        fee, funds));
    }
    funds -= fee;
    it->ticket->addExtraBaggage(extraWeight);
    std::println("[Success] Added {:.0f} kg baggage to {} ticket. Fee: {:.2f} EUR. Current balance: {:.2f} EUR.",
                 extraWeight, flight.getFlightId(), fee, funds);
}

void Passenger::cancelTicket(Flight &flight) {
    auto bestRefundable = passengerTickets.end();
    double maxRefundPrice = -1.0;
    bool hasNonRefundable = false;
    int totalForFlight = 0;
    for (auto it = passengerTickets.begin(); it != passengerTickets.end(); ++it) {
        if (it->ticket->getFlightId() != flight.getFlightId()) continue;
        ++totalForFlight;

        if (it->ticket->isRefundable()) {
            if (it->ticket->getPaidPrice() > maxRefundPrice) {
                maxRefundPrice = it->ticket->getPaidPrice();
                bestRefundable = it;
            }
        } else {
            hasNonRefundable = true;
        }
    }
    if (totalForFlight == 0) {
        throw std::runtime_error(
            "You do not have any tickets for flight " + flight.getFlightId() + ".");
    }
    if (bestRefundable == passengerTickets.end()) {
        throw std::runtime_error(
            "Your remaining ticket for " + flight.getFlightId() +
            " is 'LastMinute' type, which is non-refundable!");
    }
    if (totalForFlight > 1) {
        const std::string typeName = (bestRefundable->ticket->getTicketType() == TicketType::VIPTicket)
                                         ? "VIP"
                                         : "Standard";
        std::println("[System] Multiple tickets found for {}. "
                     "Auto-selecting the highest class refundable ticket ({})...",
                     flight.getFlightId(), typeName);
    }
    const double refundAmount = bestRefundable->ticket->getPaidPrice();
    const std::string typeName = (bestRefundable->ticket->getTicketType() == TicketType::VIPTicket)
                                     ? "VIP"
                                     : "Standard";
    flight.unregisterSoldTicket(bestRefundable->ticket.get());
    funds += refundAmount;
    passengerTickets.erase(bestRefundable);
    std::println("[Success] {} ticket for {} cancelled. Refunded: {:.2f} EUR. Current balance: {:.2f} EUR.",
                 typeName, flight.getFlightId(), refundAmount, funds);
}

void Passenger::printMyTickets() const {
    if (passengerTickets.empty()) {
        std::println("You have no active tickets.");
        return;
    }
    std::println("Your active tickets:");
    int idx = 1;
    for (const auto &[ticket, flight]: passengerTickets) {
        std::string typeStr;
        switch (ticket->getTicketType()) {
            case TicketType::StandardTicket: typeStr = "Standard";
                break;
            case TicketType::LastMinuteTicket: typeStr = "LastMinute";
                break;
            case TicketType::VIPTicket: typeStr = "VIP";
                break;
        }
        std::string statusStr;
        switch (flight->getFlightStatus()) {
            case FlightStatus::Scheduled: statusStr = "Scheduled";
                break;
            case FlightStatus::Boarding: statusStr = "Boarding";
                break;
            case FlightStatus::Delayed: statusStr = "Delayed";
                break;
            case FlightStatus::Departed: statusStr = "Departed";
                break;
            case FlightStatus::Cancelled: statusStr = "Cancelled";
                break;
        }

        std::println("{}. Flight: {} | Type: {} | Paid: {:.2f} EUR | Baggage: {:.0f} kg | Status: {}",
                     idx++,
                     ticket->getFlightId(),
                     typeStr,
                     ticket->getPaidPrice(),
                     ticket->getTotalLuggageWeight(),
                     statusStr);
    }
}

void Passenger::forceRefundTicket(const std::string &flightId, const double amount) {
    const auto newEnd = std::ranges::remove_if(passengerTickets,
                                               [&](const TicketEntry &e) {
                                                   return e.ticket->getFlightId() == flightId;
                                               });
    if (newEnd.begin() == passengerTickets.end()) return;
    passengerTickets.erase(newEnd.begin(), passengerTickets.end());
    funds += amount;
}
