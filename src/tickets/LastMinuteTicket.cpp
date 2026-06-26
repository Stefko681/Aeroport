#include "LastMinuteTicket.h"

LastMinuteTicket::LastMinuteTicket(std::string passengerName, std::string flightId, const double basePrice) : Ticket(
    std::move(passengerName), std::move(flightId), basePrice * 0.5) {
}

TicketType LastMinuteTicket::getTicketType() const {
    return TicketType::LastMinuteTicket;
}

double LastMinuteTicket::getTotalLuggageWeight() const {
    return extraLuggageWeight;
}

bool LastMinuteTicket::isRefundable() const {
    return false;
}
