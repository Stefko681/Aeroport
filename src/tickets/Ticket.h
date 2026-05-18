//
// Created by stefko on 5/13/26.
//

#ifndef AEROPORT_TICKET_H
#define AEROPORT_TICKET_H
#include "TicketType.h"
#include "../operations/Flight.h"
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

    const std::string getFlightId() const;

    double getPaidPrice() const;
};


#endif //AEROPORT_TICKET_H
