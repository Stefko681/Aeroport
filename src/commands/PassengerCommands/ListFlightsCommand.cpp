#include "ListFlightsCommand.h"
#include <print>
#include "core/Engine.h"
#include "operations/Flight.h"

ListFlightsCommand::ListFlightsCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole ListFlightsCommand::getRequiredRole() const {
    return CommandRole::Passenger;
}

std::expected<void, std::string> ListFlightsCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: list-flights [destination]");
    const std::string &dest = args[1];
    bool found = false;
    std::println("Available flights to {}:", dest);
    int idx = 1;
    for (const auto &airline: engine.getAirlines()) {
        for (const auto &flight: airline->getAllFlights()) {
            if (flight->getDestination() == dest && (
                    flight->getFlightStatus() == FlightStatus::Scheduled || flight->getFlightStatus() ==
                    FlightStatus::Delayed)) {
                std::println("{}. {} Status: {}  Base Price: {:.2f} EUR",
                             idx++, flight->getFlightId(),
                             (flight->getFlightStatus() == FlightStatus::Delayed ? "Delayed" : "Scheduled"),
                             flight->getBasePrice());
                found = true;
            }
        }
    }
    if (!found) std::println("No available flights found to {}.", dest);
    return {};
}
