#pragma once

#include <stdexcept>
#include <string>

enum class TicketType {
    StandardTicket,
    LastMinuteTicket,
    VIPTicket
};

[[nodiscard]] std::string ticketTypeToString(TicketType type);

[[nodiscard]] TicketType stringToTicketType(std::string_view str);

class Ticket {
protected:
    std::string passengerName;
    std::string flightId;
    double paidPrice{0.0};
    double extraLuggageWeight{0.0};

public:
    Ticket(std::string passengerName, std::string flightId, double paidPrice);

    virtual ~Ticket() = default;

    [[nodiscard]] const std::string &getPassengerName() const;

    [[nodiscard]] const std::string &getFlightId() const;

    [[nodiscard]] double getPaidPrice() const;

    [[nodiscard]] virtual TicketType getTicketType() const = 0;

    [[nodiscard]] virtual double getTotalLuggageWeight() const = 0;

    [[nodiscard]] virtual bool isRefundable() const = 0;

    void addExtraBaggage(double weight);
};

