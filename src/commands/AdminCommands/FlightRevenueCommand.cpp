#include "FlightRevenueCommand.h"
#include "core/Engine.h"
#include "operations/Airline.h"

FlightRevenueCommand::FlightRevenueCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole FlightRevenueCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> FlightRevenueCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: flight-revenue [flight_id]");
    auto flight = engine.findFlightGlobal(args[1]);
    if (!flight) return std::unexpected("[Error] Flight not found.");
    auto airline = engine.findAirlineOfFlight(flight);
    if (!airline) return std::unexpected("[Error] Airline not found.");
    airline->printFlightRevenue(args[1]);
    return {};
}
