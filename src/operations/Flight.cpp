//
// Created by stefko on 5/15/26.
//
#include "Flight.h"
#include "airplanes/Airplane.h"
#include <algorithm>
#include <ranges>
#include <stdexcept>
#include "tickets/Ticket.h"

Flight::Flight(std::string flightId, Airplane *airplane,
               std::string destination, const double basePrice)
    : flightId(std::move(flightId)),
      airplane(airplane),
      destination(std::move(destination)),
      basePrice(basePrice),
      flightStatus(FlightStatus::Scheduled) {
    if (!airplane)
        throw std::invalid_argument("Airplane cannot be null.");
    if (this->flightId.empty())
        throw std::invalid_argument("Flight ID cannot be empty.");
    if (this->destination.empty())
        throw std::invalid_argument("Destination cannot be empty.");
    if (basePrice <= 0)
        throw std::invalid_argument("Base price must be greater than zero.");
}

bool Flight::hasAvailableSeats() const {
    return static_cast<int>(soldTickets.size()) < airplane->getCapacity();
}

const std::string &Flight::getFlightId() const {
    return flightId;
}

const std::string &Flight::getDestination() const {
    return destination;
}

double Flight::getBasePrice() const {
    return basePrice;
}

FlightStatus Flight::getFlightStatus() const {
    return flightStatus;
}

Airplane *Flight::getAirplane() const {
    return airplane;
}

AirplaneType Flight::getAirplaneType() const {
    return airplane->getAirplaneType();
}

const std::vector<Ticket *> &Flight::getSoldTickets() const {
    return soldTickets;
}

double Flight::getTotalTicketRevenue() const {
    double total = 0.0;
    for (const auto &ticket: soldTickets) {
        total += ticket->getPaidPrice();
    }
    return total;
}

double Flight::getAirportTax() const {
    return airplane->airportFee(getTotalTicketRevenue());
}

double Flight::getNetProfit() const {
    return getTotalTicketRevenue() - getAirportTax();
}

void Flight::setFlightStatus(const FlightStatus status) {
    flightStatus = status;
}

void Flight::registerSoldTicket(Ticket *ticket) {
    if (!ticket)
        throw std::invalid_argument("Ticket cannot be null.");
    soldTickets.push_back(ticket);
}

void Flight::replaceSoldTicket(const Ticket *oldTicket, Ticket *newTicket) {
    for (auto &ticket: soldTickets) {
        if (ticket == oldTicket) {
            ticket = newTicket;
            return;
        }
    }
    throw std::runtime_error("Old ticket not found in flight.");
}

void Flight::unregisterSoldTicket(Ticket *ticketToRemove) {
    const auto it = std::ranges::find(soldTickets, ticketToRemove);
    if (it == soldTickets.end())
        throw std::runtime_error("Ticket not found in flight.");
    soldTickets.erase(it);
}
