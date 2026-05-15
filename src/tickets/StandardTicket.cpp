//
// Created by stefko on 5/14/26.
//

#include "StandardTicket.h"

StandardTicket::StandardTicket(std::string passengerName, std::string flightId, const double basePrice) : Ticket(
    std::move(passengerName), std::move(flightId), basePrice) {
}

TicketType StandardTicket::getTicketType() const {
    return TicketType::StandardTicket;
}

double StandardTicket::getTotalLuggageWeight() const {
    return extraLuggageWeight;
}

bool StandardTicket::isRefundable() const {
    return true;
}
