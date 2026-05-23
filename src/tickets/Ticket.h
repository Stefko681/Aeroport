//
// Created by stefko on 5/13/26.
//

#ifndef AEROPORT_TICKET_H
#define AEROPORT_TICKET_H
#pragma once
#include "TicketType.h"
#include <string>

class Ticket {
protected:
    std::string passengerName;
    std::string flightId;
    double paidPrice;
    double extraLuggageWeight;

public:
    Ticket(std::string passengerName, std::string flightId, double paidPrice);

    virtual ~Ticket() = default;

    [[nodiscard]] virtual TicketType getTicketType() const = 0;

    [[nodiscard]] virtual bool isRefundable() const = 0;

    [[nodiscard]] virtual double getTotalLuggageWeight() const = 0;

    void addExtraBaggage(double weight);

    [[nodiscard]] double getPaidPrice() const;

    [[nodiscard]] const std::string &getFlightId() const;

    [[nodiscard]] const std::string &getPassengerName() const;
};

#endif //AEROPORT_TICKET_H
