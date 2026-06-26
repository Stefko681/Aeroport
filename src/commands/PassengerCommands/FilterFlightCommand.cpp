#include "FilterFlightCommand.h"
#include <print>
#include <string>
#include "core/Engine.h"
#include "operations/Flight.h"

class Engine;

FilterFlightsCommand::FilterFlightsCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole FilterFlightsCommand::getRequiredRole() const {
    return CommandRole::Passenger;
}

std::expected<void, std::string> FilterFlightsCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: filter-flights [max_price]");
    double maxPrice = 0;
    try {
        maxPrice = std::stod(args[1]);
    } catch (...) {
        return std::unexpected("[Error] Invalid price format.");
    }
    bool found = false;
    std::println("Filtered flights (Price < {:.2f} EUR):", maxPrice);
    int idx = 1;
    for (const auto &airline: engine.getAirlines()) {
        for (const auto &flight: airline->getAllFlights()) {
            if (flight->getBasePrice() <= maxPrice &&
                (flight->getFlightStatus() == FlightStatus::Scheduled || flight->getFlightStatus() ==
                 FlightStatus::Delayed)) {
                std::println("{}. {} ({}) - {:.2f} EUR", idx++, flight->getFlightId(), flight->getDestination(),
                             flight->getBasePrice());
                found = true;
            }
        }
    }
    if (!found) std::println("No flights found matching the criteria.");
    return {};
}
