#include "CloseRunwayCommand.h"
#include <print>
#include "core/Engine.h"
#include "operations/Flight.h"

CloseRunwayCommand::CloseRunwayCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole CloseRunwayCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> CloseRunwayCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: close-runway [runway_id]");
    const auto r = engine.findRunway(args[1]);
    if (!r) return std::unexpected("[Error] Runway not found.");
    auto result = r->closeForMaintenance();
    if (!result) return std::unexpected(result.error());
    if (const auto plane = *result) {
        for (const auto &airline: engine.getAirlines()) {
            for (const auto &flight: airline->getAllFlights()) {
                if (flight->getFlightStatus() == FlightStatus::Boarding &&
                    flight->getAirplane() == plane) {
                    flight->setFlightStatus(FlightStatus::Scheduled);
                    std::println("[System] Flight {} reassigned to Scheduled.", flight->getFlightId());
                    break;
                    }
            }
        }
    }
    std::println("[System] Runway {} is now closed. Status -> Maintenance.", args[1]);
    return {};
}
