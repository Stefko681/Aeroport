//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_FLIGHT_H
#define AEROPORT_FLIGHT_H
#include <memory>
#include "Airline.h"
#include "tickets/Ticket.h"
#include "../infrastructures/flightStatus.h"
#include <string>
#include <vector>

class Flight {
protected:
    std::string flightId;
    Airplane *airplane;
    std::string destination;
    double basePrice;
    std::vector<std::unique_ptr<Ticket> > soldTickets;
    flightStatus flightStatus;

public:
    Flight(std::string flightId, Airplane *airplane, std::string destination, double bestPrice);
};


#endif //AEROPORT_FLIGHT_H
