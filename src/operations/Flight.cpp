#include "Flight.h"
#include "airplanes/Airplane.h"
#include <algorithm>
#include <ranges>
#include <stdexcept>
#include "tickets/Ticket.h"

Flight::Flight(std::string flightId, const std::shared_ptr<Airplane> &airplane, std::string destination,
               const double basePrice) : flightId(std::move(flightId)), airplane(airplane),
                                         destination(std::move(destination)), basePrice(basePrice),
                                         flightStatus(FlightStatus::Scheduled) {
    if (!airplane) throw std::invalid_argument("Airplane cannot be null.");
    if (this->flightId.empty()) throw std::invalid_argument("Flight ID cannot be empty.");
    if (this->destination.empty()) throw std::invalid_argument("Destination cannot be empty.");
    if (basePrice <= 0) throw std::invalid_argument("Base price must be greater than zero.");
}

bool Flight::hasAvailableSeats() const {
    if (const auto lockedAirplane = airplane.lock()) {
        const size_t activeTickets = std::ranges::count_if(soldTickets, [](const auto& wt) {
            return !wt.expired();
        });
        return activeTickets < lockedAirplane->getAirplaneCapacity();
    }
    return false;
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

std::shared_ptr<Airplane> Flight::getAirplane() const {
    return airplane.lock();
}

AirplaneType Flight::getAirplaneType() const {
    if (const auto lockedAirplane = airplane.lock()) return lockedAirplane->getAirplaneType();
    throw std::runtime_error("Airplane is no longer available.");
}

const std::vector<std::weak_ptr<Ticket> > &Flight::getSoldTickets() const {
    return soldTickets;
}

double Flight::getTotalTicketRevenue() const {
    double total = 0.0;
    for (const auto &weakTicket: soldTickets) {
        if (const auto ticket = weakTicket.lock()) total += ticket->getPaidPrice();
    }
    return total;
}

double Flight::getAirportTax() const {
    if (const auto lockedAirplane = airplane.lock()) return lockedAirplane->airportFee(getTotalTicketRevenue());
    return 0.0;
}

double Flight::getNetProfit() const {
    return getTotalTicketRevenue() - getAirportTax();
}

void Flight::setFlightStatus(const FlightStatus status) {
    flightStatus = status;
}

void Flight::registerSoldTicket(const std::shared_ptr<Ticket> &ticket) {
    if (!ticket) throw std::invalid_argument("Ticket cannot be null.");
    std::erase_if(soldTickets, [](const auto& wt) { return wt.expired(); });
    soldTickets.push_back(ticket);
}

void Flight::replaceSoldTicket(const std::shared_ptr<Ticket> &oldTicket, const std::shared_ptr<Ticket> &newTicket) {
    if (!newTicket) throw std::invalid_argument("New ticket cannot be null.");
    for (auto &weakTicket: soldTickets) {
        if (weakTicket.lock() == oldTicket) {
            weakTicket = newTicket;
            return;
        }
    }
    throw std::runtime_error("Old ticket not found in flight.");
}

void Flight::unregisterSoldTicket(const std::shared_ptr<Ticket> &ticketToRemove) {
    const auto it = std::ranges::find_if(soldTickets, [&ticketToRemove](const std::weak_ptr<Ticket> &weakTicket) {
        return weakTicket.lock() == ticketToRemove;
    });
    if (it == soldTickets.end()) throw std::runtime_error("Ticket not found in flight.");
    soldTickets.erase(it);
}

std::string flightStatusToString(const FlightStatus status) {
    switch (status) {
        case FlightStatus::Scheduled: return "Scheduled";
        case FlightStatus::Boarding: return "Boarding";
        case FlightStatus::Delayed: return "Delayed";
        case FlightStatus::Departed: return "Departed";
        case FlightStatus::Cancelled: return "Cancelled";
    }
    return "Unknown";
}

FlightStatus stringToFlightStatus(const std::string &str) {
    if (str == "Scheduled") return FlightStatus::Scheduled;
    if (str == "Boarding") return FlightStatus::Boarding;
    if (str == "Delayed") return FlightStatus::Delayed;
    if (str == "Departed") return FlightStatus::Departed;
    if (str == "Cancelled") return FlightStatus::Cancelled;
    throw std::invalid_argument("Invalid FlightStatus string.");
}
