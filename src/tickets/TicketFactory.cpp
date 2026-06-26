#include "TicketFactory.h"
#include "StandardTicket.h"
#include "LastMinuteTicket.h"
#include "VIPTicket.h"

std::unique_ptr<Ticket> TicketFactory::create(const TicketType ticketType, std::string passengerName,
                                              std::string flightId, double paidPrice) {
    switch (ticketType) {
        case(TicketType::StandardTicket): return std::make_unique<StandardTicket>(
                std::move(passengerName), std::move(flightId), paidPrice);
        case (TicketType::LastMinuteTicket): return std::make_unique<LastMinuteTicket>(
                std::move(passengerName), std::move(flightId), paidPrice);
        case(TicketType::VIPTicket): return std::make_unique<VIPTicket>(std::move(passengerName), std::move(flightId),
                                                                        paidPrice);
        default: throw std::invalid_argument("Unknown ticket type");
    }
}
