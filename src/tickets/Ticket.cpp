//
// Created by stefko on 5/13/26.
//

#include "Ticket.h"

Ticket::Ticket(std::string passengerName, std::string flightId, const double paidPrice) : passengerName(
        std::move(passengerName)), flightId(std::move(flightId)), paidPrice(paidPrice), extraLuggageWeight(0.0) {
    if (passengerName.empty() || flightId.empty())
        throw std::invalid_argument("Name and ID cannot be empty");
    if (paidPrice <= 0) throw std::invalid_argument("Paid price cannot be less or equal to zero");
}
