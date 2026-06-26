#include "Airline.h"
#include "Flight.h"
#include <airplanes/Airplane.h>
#include <print>
#include <algorithm>

class Engine;

Airline::Airline(std::string name, const double balance) : name(std::move(name)), balance(balance) {
    if (this->name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (balance < 0) throw std::invalid_argument("Balance cannot be less than zero");
}

const std::string &Airline::getName() const {
    return name;
}

double Airline::getBalance() const {
    return balance;
}

int Airline::getAirplanesCount() const {
    return static_cast<int>(airplanes.size());
}

std::expected<std::shared_ptr<Airplane>, std::string> Airline::purchaseAircraft(std::shared_ptr<Airplane> plane) {
    if (!plane) return std::unexpected("Airplane cannot be null");
    if (balance < AIRCRAFT_PRICE)
        return std::unexpected(std::format(
            "Insufficient balance to purchase aircraft. Required: {:.2f} EUR, Available {:.2f} EUR.", AIRCRAFT_PRICE,
            balance));
    balance -= AIRCRAFT_PRICE;
    airplanes.push_back(plane);
    return plane;
}

std::expected<std::shared_ptr<Airplane>, std::string> Airline::cloneAircraft(const int sourceId) {
    const auto source = findAirplane(sourceId);
    if (!source) return std::unexpected("Aircraft ID: " + std::to_string(sourceId) + " not found in fleet");
    if (balance < AIRCRAFT_PRICE)
        return std::unexpected(std::format(
            "Insufficient balance to clone aircraft. Required: {:.2f} EUR, Available: {:.2f} EUR.", AIRCRAFT_PRICE,
            balance));
    balance -= AIRCRAFT_PRICE;
    std::shared_ptr<Airplane> cloned(source->clone());
    airplanes.push_back(cloned);
    return cloned;
}


std::shared_ptr<Airplane> Airline::findAirplane(const int id) const {
    const auto it = std::ranges::find_if(airplanes, [id](const auto &airplane) {
        return airplane->getAirplaneId() == id;
    });
    if (it != airplanes.end()) return *it;
    return nullptr;
}

std::shared_ptr<Flight> Airline::findFlight(const std::string &flightId) const {
    const auto it = std::ranges::find_if(flights, [&flightId](const auto &flight) {
        return flight->getFlightId() == flightId;
    });
    if (it != flights.end()) return *it;
    return nullptr;
}

std::vector<std::shared_ptr<Airplane> > Airline::getFleet() const {
    return airplanes;
}

std::expected<void, std::string> Airline::deductBalance(const double amount) {
    if (balance < amount) return std::unexpected("Insufficient funds.");
    balance -= amount;
    return {};
}

void Airline::applyFlightProfitDelta(const double delta) {
    balance += delta;
}

std::expected<std::shared_ptr<Flight>, std::string> Airline::scheduleFlight(
    const std::string &flightId, const int aircraftId, const std::string &destination, double basePrice) {
    if (findFlight(flightId)) return std::unexpected("Flight ID '" + flightId + "' already exists.");
    auto plane = findAirplane(aircraftId);
    if (!plane)
        return std::unexpected(
            "Aircraft ID " + std::to_string(aircraftId) + " not found in this airline's fleet.");
    if (plane->isInHangar())
        return std::unexpected(
            std::format("Aircraft {} is currently in a hangar and cannot be scheduled.", aircraftId));
    if (!plane->canFly())
        return std::unexpected(std::format(
            "Aircraft {} health is {:.0f}% (<=20%). Send it to a hangar before scheduling.", aircraftId,
            plane->getAirplaneHealth()));
    for (const auto &flight: flights) {
        if (flight->getAirplane() == plane) {
            if (const auto status = flight->getFlightStatus();
                status == FlightStatus::Scheduled || status == FlightStatus::Boarding || status ==
                FlightStatus::Delayed)
                return std::unexpected(std::format("Aircraft {} is already assigned to active flight {}.", aircraftId,
                                                   flight->getFlightId()));
        }
    }
    auto flight = std::make_shared<Flight>(flightId, plane, destination, basePrice);
    flights.push_back(flight);
    return flight;
}

std::vector<std::shared_ptr<Flight> > Airline::getAllFlights() const {
    return flights;
}

std::expected<void, std::string> Airline::cancelFlight(const std::string &flightId) const {
    const auto flight = findFlight(flightId);
    if (!flight) return std::unexpected("Flight '" + flightId + "' not found.");
    if (flight->getFlightStatus() == FlightStatus::Departed)
        return std::unexpected(
            "Flight '" + flightId + "' has already Departed. It cannot be cancelled.");
    if (flight->getFlightStatus() == FlightStatus::Cancelled)
        return std::unexpected(
            "Flight '" + flightId + "' is already cancelled.");
    flight->setFlightStatus(FlightStatus::Cancelled);
    return {};
}

namespace {
    std::string airplaneTypeLabel(const AirplaneType type) {
        switch (type) {
            case AirplaneType::PassengerPlane: return "PassengerPlane";
            case AirplaneType::CargoPlane: return "CargoPlane";
            case AirplaneType::PrivateJet: return "PrivateJet";
        }
        return "Unknown";
    }
}

void Airline::printFleet() const {
    std::println("Fleet Overview for {}:", name);
    if (airplanes.empty()) {
        std::println(" (no aircraft)");
        return;
    }
    int idx = 1;
    for (const auto &airplane: airplanes) {
        std::string extra;
        if (airplane->isInHangar()) extra = " [IN HANGAR]";
        std::println("{}. {} (ID: {}) - Health: {:.0f}%{}", idx++, airplaneTypeLabel(airplane->getAirplaneType()),
                     airplane->getAirplaneId(), airplane->getAirplaneHealth(), extra);
    }
}

void Airline::printFlightRevenue(const std::string &flightId) const {
    const auto flight = findFlight(flightId);
    if (!flight) throw std::runtime_error("Flight '" + flightId + "' not found.");
    std::println("=== Flight Revenue Report: {} ===", flightId);
    std::println("Total Ticket Revenue: {:.2f} EUR", flight->getTotalTicketRevenue());
    std::println("Airport Tax Deducted: {:.2f} EUR", flight->getAirportTax());
    std::println("Net Profit for Airline: {:.2f} EUR", flight->getNetProfit());
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

std::expected<std::shared_ptr<Airplane>, std::string> Airline::loadAircraft(std::shared_ptr<Airplane> plane) {
    if (!plane) return std::unexpected("Airplane cannot be null.");
    airplanes.push_back(plane);
    return plane;
}

std::expected<std::shared_ptr<Flight>, std::string> Airline::loadFlight(const std::string &flightId,
                                                                        const std::shared_ptr<Airplane> &aircraft,
                                                                        const std::string &destination,
                                                                        const double basePrice) {
    if (!aircraft) return std::unexpected("Airplane cannot be null.");
    auto flight = std::make_shared<Flight>(flightId, aircraft, destination, basePrice);
    flights.push_back(flight);
    return flight;
}
