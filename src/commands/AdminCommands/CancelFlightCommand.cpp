#include "CancelFlightCommand.h"
#include <print>
#include "core/Engine.h"
#include "operations/Airline.h"
#include "operations/Flight.h"

CancelFlightCommand::CancelFlightCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole CancelFlightCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> CancelFlightCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: cancel-flight [flight_id]");
    const auto flight = engine.findFlightGlobal(args[1]);
    if (!flight) return std::unexpected("[Error] Flight not found.");
    if (flight->getFlightStatus() == FlightStatus::Departed)
        return std::unexpected(std::format("[Error] Flight {} has already Departed. It cannot be cancelled.", flight->getFlightId()));
    const auto airline = engine.findAirlineOfFlight(flight);
    if (!airline) return std::unexpected("[Error] Airline not found.");
    airline->cancelFlight(args[1]);
    engine.refundAllPassengersForFlight(args[1]);
    std::println("[System] Flight {} Cancelled. Passengers auto-refunded.", args[1]);
    return {};
}
