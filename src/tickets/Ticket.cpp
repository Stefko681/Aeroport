//
// Created by stefko on 5/13/26.
//

#include "Ticket.h"
#include <stdexcept>

Ticket::Ticket(std::string passengerName, std::string flightId, const double paidPrice)
    : passengerName(std::move(passengerName)),
      flightId(std::move(flightId)),
      paidPrice(paidPrice),
      extraLuggageWeight(0.0) {
    if (this->passengerName.empty() || this->flightId.empty())
        throw std::invalid_argument("Passenger name and flight ID cannot be empty.");
    if (paidPrice <= 0)
        throw std::invalid_argument("Paid price must be greater than zero.");
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
    if (weight <= 0)
        throw std::invalid_argument("Baggage weight must be greater than zero.");
    extraLuggageWeight += weight;
}
