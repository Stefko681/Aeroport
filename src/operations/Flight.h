//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_FLIGHT_H
#define AEROPORT_FLIGHT_H
#include <memory>
#include "Airline.h"
#include "FlightStatus.h"
#include <string>
#include <vector>
class Ticket;

class Flight {
protected:
    std::string flightId;
    Airplane *airplane;
    std::string destination;
    double basePrice;
    std::vector<Ticket *> soldTickets;
    FlightStatus flightStatus;

public:
    Flight(std::string flightId, Airplane *airplane, std::string destination, double bestPrice);

    bool hasAvailableSeats() const;

    const std::string getFlightId() const;

    double getBasePrice() const;

    void registerSoldTicket(Ticket *ticket);

    void replaceSoldTicket(const Ticket *oldTicket, Ticket *newTicket);

    void unregisterSoldTicket(Ticket *ticketToRemove);
};


#endif //AEROPORT_FLIGHT_H
