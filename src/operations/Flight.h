#pragma once

#include "airplanes/Airplane.h"
#include <string>
#include <vector>

class Ticket;
class Airplane;

enum class FlightStatus {
    Scheduled,
    Boarding,
    Delayed,
    Departed,
    Cancelled
};

std::string flightStatusToString(FlightStatus status);

[[nodiscard]] FlightStatus stringToFlightStatus(const std::string &str);

class Flight {
protected:
    std::string flightId;
    std::weak_ptr<Airplane> airplane;
    std::string destination;
    double basePrice{0};
    std::vector<std::weak_ptr<Ticket> > soldTickets;
    FlightStatus flightStatus;

public:
    Flight(std::string flightId, const std::shared_ptr<Airplane> &airplane, std::string destination, double basePrice);

    [[nodiscard]] const std::string &getFlightId() const;

    [[nodiscard]] const std::string &getDestination() const;

    [[nodiscard]] double getBasePrice() const;

    [[nodiscard]] FlightStatus getFlightStatus() const;

    [[nodiscard]] std::shared_ptr<Airplane> getAirplane() const;

    [[nodiscard]] AirplaneType getAirplaneType() const;

    [[nodiscard]] const std::vector<std::weak_ptr<Ticket> > &getSoldTickets() const;

    [[nodiscard]] double getTotalTicketRevenue() const;

    [[nodiscard]] double getAirportTax() const;

    [[nodiscard]] double getNetProfit() const;

    [[nodiscard]] bool hasAvailableSeats() const;


    void setFlightStatus(FlightStatus status);

    void registerSoldTicket(const std::shared_ptr<Ticket> &ticket);

    void replaceSoldTicket(const std::shared_ptr<Ticket> &oldTicket, const std::shared_ptr<Ticket> &newTicket);

    void unregisterSoldTicket(const std::shared_ptr<Ticket> &ticketToRemove);
};
