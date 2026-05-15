//
// Created by stefko on 5/14/26.
//

#include "VIPTicket.h"

VIPTicket::VIPTicket(std::string passengerName, std::string flightId, const double basePrice) : Ticket(
    std::move(passengerName), std::move(flightId), basePrice * 2) {
}

TicketType VIPTicket::getTicketType() const {
    return TicketType::VIPTicket;
}

double VIPTicket::getTotalLuggageWeight() const {
    return extraLuggageWeight + 20;
}

bool VIPTicket::isRefundable() const {
    return true;
}
