#include "Ticket.h"
#include <stdexcept>

Ticket::Ticket(std::string passengerName, std::string flightId, const double paidPrice) : passengerName(
        std::move(passengerName)), flightId(std::move(flightId)), paidPrice(paidPrice) {
    if (this->passengerName.empty()) throw std::invalid_argument("Passenger name cannot be empty.");
    if (this->flightId.empty()) throw std::invalid_argument("Flight ID cannot be empty");
    if (paidPrice < 0) throw std::invalid_argument("Paid price cannot be negative.");
}

double Ticket::getPaidPrice() const {
    return paidPrice;
}

const std::string &Ticket::getFlightId() const {
    return flightId;
}

const std::string &Ticket::getPassengerName() const {
    return passengerName;
}

void Ticket::addExtraBaggage(const double weight) {
    if (weight <= 0) throw std::invalid_argument("Baggage weight must be positive.");
    extraLuggageWeight += weight;
}

std::string ticketTypeToString(TicketType type) {
    switch (type) {
        case TicketType::StandardTicket: return "Standard";
        case TicketType::LastMinuteTicket: return "LastMinute";
        case TicketType::VIPTicket: return "VIP";
    }
    return "Unknown";
}

TicketType stringToTicketType(std::string_view str) {
    if (str == "Standard") return TicketType::StandardTicket;
    if (str == "LastMinute") return TicketType::LastMinuteTicket;
    if (str == "VIP") return TicketType::VIPTicket;
    throw std::invalid_argument("Invalid TicketType string.");
}
