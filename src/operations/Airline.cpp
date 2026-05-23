//
// Created by stefko on 5/15/26.
//

#include "Airline.h"
#include "Flight.h"
#include <airplanes/Airplane.h>
#include <print>
#include <algorithm>

Airline::Airline(std::string name, const double balance) : name(std::move(name)), balance(balance) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (balance < 0) throw std::invalid_argument("Balance cannot be less than zero");
}

std::string Airline::getName() const {
    return name;
}

double Airline::getBalance() const {
    return balance;
}

int Airline::getAircraftCount() const {
    return static_cast<int>(airplanes.size());
}

Airplane *Airline::purchaseAircraft(std::unique_ptr<Airplane> plane) {
    if (!plane) throw std::invalid_argument("Airplane cannot be null");
    if (balance < AIRCRAFT_PRICE)
        throw std::runtime_error(std::format(
            "Insufficient balance to purchase aircraft. " "Required: {:.2f} EUR, Available {:.2f} EUR.", AIRCRAFT_PRICE,
            balance));
    balance -= AIRCRAFT_PRICE;
    airplanes.emplace_back(std::move(plane));
    return airplanes.back().get();
}

Airplane *Airline::cloneAircraft(const std::string &sourceId, const std::string &newId) {
    Airplane *source = findAirplane(sourceId);
    if (!source) throw std::runtime_error("Aircraft ID: " + sourceId + "not found in fleet");
    if (balance < AIRCRAFT_PRICE)
        throw std::runtime_error(std::format(
            "Insufficient balance to clone aircraft. ""Required: {:.2f} EUR, Available: {:.2f} EUR.", AIRCRAFT_PRICE,
            balance));
    balance -= AIRCRAFT_PRICE;
    auto cloned = source->clone(newId);
    airplanes.emplace_back(std::move(cloned));
    return airplanes.back().get();
}

Airplane *Airline::findAirplane(const std::string &id) const {
    for (const auto &airplane: airplanes) {
        if (airplane->getAirplaneId() == id) {
            return airplane.get();
        }
    }
    return nullptr;
}

std::vector<Airplane *> Airline::getFleet() const {
    std::vector<Airplane *> result;
    for (const auto &airplane: airplanes) {
        result.emplace_back(airplane.get());
    }
    return result;
}

void Airline::deductBalance(double amount) {
    if (amount <= 0) throw std::invalid_argument("Deduction amount must be positive");
    if (balance < amount)
        throw std::runtime_error(
            std::format("Insufficient airline balance. ""Required: {:.2f} EUR, Available: {:.2f} EUR.", amount,
                        balance));
    balance -= amount;
}

void Airline::applyFlightProfit(double netAmount) {
    balance += netAmount;
}

Flight *Airline::scheduleFlight(const std::string &flightId, const std::string &aircraftId,
                                const std::string &destination, double basePrice) {
    if (findFlight(flightId)) throw std::runtime_error("Flight ID '" + flightId + "' already exists.");
    Airplane *plane = findAirplane(aircraftId);
    if (!plane) throw std::runtime_error("Aircraft ID " + aircraftId + " not found in this airline's fleet.");
    if (plane->isInHangar())
        throw std::runtime_error(
            std::format("Aircraft {} is currently in a hangar and cannot be scheduled.", aircraftId));
    if (!plane->canFly())
        throw std::runtime_error(std::format(
            "Aircraft {} health is {:.0f}% (<=20%%). ""Send it to a hangar before scheduling.", aircraftId,
            plane->getHealth()));
    for (const auto &flight: flights) {
        if (flight->getAirplane() == plane) {
            const auto status = flight->getFlightStatus();
            if (status == FlightStatus::Scheduled || status == FlightStatus::Boarding || status ==
                FlightStatus::Delayed)
                throw std::runtime_error(std::format("Aircraft {} is already assigned to active flight {}.", aircraftId,
                                                     flight->getFlightId()));
        }
    }
    auto flight = std::make_unique<Flight>(flightId, plane, destination, basePrice);
    flights.emplace_back(std::move(flight));
    return flights.back().get();
}

Flight *Airline::findFlight(const std::string &flightId) const {
    for (const auto &flight: flights) {
        if (flight->getFlightId() == flightId) {
            return flight.get();
        }
    }
    return nullptr;
}

std::vector<Flight *> Airline::getAllFlights() const {
    std::vector<Flight *> result;
    for (const auto &flight: flights) {
        result.emplace_back(flight.get());
    }
    return result;
}

void Airline::cancelFlight(const std::string &flightId) const {
    Flight *flight = findFlight(flightId);
    if (!flight)throw std::runtime_error("Flight '" + flightId + "' not found.");
    if (flight->getFlightStatus() == FlightStatus::Departed)
        throw std::runtime_error(
            "Flight " + flightId + " has already Departed. It cannot be cancelled.");
    if (flight->getFlightStatus() == FlightStatus::Cancelled)
        throw std::runtime_error(
            "Flight " + flightId + " is already cancelled.");
    flight->setFlightStatus(FlightStatus::Cancelled);
}

namespace {
    std::string airplaneTypeLabel(const AirplaneType type) {
        switch (type) {
            case AirplaneType::PassengerPlane: return "Passenger plane";
            case AirplaneType::CargoPlane: return "Cargo plane";
            case AirplaneType::PrivateJet: return "Private jet";
        }
        return "Unknown";
    }
}

void Airline::printFleet() const {
    std::println("Fleet overview for {}:", name);
    if (airplanes.empty()) {
        std::println(" (no aircraft)");
        return;
    }
    int idx = 1;
    for (const auto &airplane: airplanes) {
        std::string extra;
        if (airplane->isInHangar()) extra = " [IN HANGAR]";
        std::println("{}. {} (ID: {}) - Health: {:.0f}%{}", idx++, airplaneTypeLabel(airplane->getAirplaneType()),
                     airplane->getAirplaneId(), airplane->getHealth(), extra);
    }
}

void Airline::printFlightRevenue(const std::string &flightId) const {
    const Flight *flight = findFlight(flightId);
    if (!flight) throw std::runtime_error("Flight '" + flightId + "' not found.");
    const double revenue = flight->getTotalTicketRevenue();
    const double tax = flight->getAirportTax();
    const double net = flight->getNetProfit();
    std::println("=== Flight Revenue Report: {} ===", flightId);
    std::println("Total Ticket Revenue: {:.2f} EUR", revenue);
    std::println("Airport Tax Deducted: {:.2f} EUR", tax);
    std::println("Net Profit for Airline: {:.2f} EUR", net);
}

void Airline::printAuditReport() const {
    std::println("=== Airline Audit Report: {} ===", name);
    std::println("Total Owned Aircraft: {}", airplanes.size());
    std::println("Completed Flights (Departed): {}", getDepartedCount());
    std::println("Cancelled Flights: {}", getCancelledCount());
    std::println("Current Corporate Balance: {:.2f} EUR", balance);
}

int Airline::getDepartedCount() const {
    return static_cast<int>(std::ranges::count_if(flights, [](const auto &f) {
        return f->getFlightStatus() == FlightStatus::Departed;
    }));
}

int Airline::getCancelledCount() const {
    return static_cast<int>(std::ranges::count_if(flights, [](const auto &f) {
        return f->getFlightStatus() == FlightStatus::Cancelled;
    }));
}
