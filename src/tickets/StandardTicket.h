#pragma once

#include "Ticket.h"

class StandardTicket final : public Ticket {
public:
    StandardTicket(std::string passengerName, std::string flightId, double basePrice);

    [[nodiscard]] TicketType getTicketType() const override;

    [[nodiscard]] double getTotalLuggageWeight() const override;

    [[nodiscard]] bool isRefundable() const override;
};


