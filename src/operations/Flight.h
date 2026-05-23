//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_FLIGHT_H
#define AEROPORT_FLIGHT_H
#include "FlightStatus.h"
#include "airplanes/AirplaneType.h"
#include <string>
#include <vector>

class Ticket;
class Airplane;

class Flight {
protected:
    std::string flightId;
    Airplane *airplane;
    std::string destination;
    double basePrice;
    std::vector<Ticket *> soldTickets;
    FlightStatus flightStatus;

public:
    Flight(std::string flightId, Airplane *airplane,
           std::string destination, double basePrice);

    [[nodiscard]] bool hasAvailableSeats() const;

    [[nodiscard]] const std::string &getFlightId() const;

    [[nodiscard]] const std::string &getDestination() const;

    [[nodiscard]] double getBasePrice() const;

    [[nodiscard]] FlightStatus getFlightStatus() const;

    [[nodiscard]] AirplaneType getAirplaneType() const;

    [[nodiscard]] Airplane *getAirplane() const;

    [[nodiscard]] const std::vector<Ticket *> &getSoldTickets() const;

    [[nodiscard]] double getTotalTicketRevenue() const;

    [[nodiscard]] double getAirportTax() const;

    [[nodiscard]] double getNetProfit() const;

    void setFlightStatus(FlightStatus status);

    void registerSoldTicket(Ticket *ticket);

    void replaceSoldTicket(const Ticket *oldTicket, Ticket *newTicket);

    void unregisterSoldTicket(Ticket *ticketToRemove);
};


#endif //AEROPORT_FLIGHT_H
