#include "ListAirspaceCommand.h"
#include "core/Engine.h"
#include "operations/Airline.h"
#include "operations/Flight.h"
#include "airplanes/Airplane.h"
#include <print>

ListAirspaceCommand::ListAirspaceCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole ListAirspaceCommand::getRequiredRole() const {
    return CommandRole::Dispatcher;
}

std::expected<void, std::string> ListAirspaceCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 1) return std::unexpected("Usage: list-airspace");
    std::println("[Error] Pending Airspace Traffic (Scheduled / Delayed):");
    int idx = 1;
    for (const auto &airline: engine.getAirlines()) {
        for (const auto &flight: airline->getAllFlights()) {
            if (const auto status = flight->getFlightStatus();
                status != FlightStatus::Scheduled && status != FlightStatus::Delayed) {
                continue;
            }
            std::string typeStr;
            switch (flight->getAirplaneType()) {
                case AirplaneType::PassengerPlane: typeStr = "PassengerPlane";
                    break;
                case AirplaneType::CargoPlane: typeStr = "CargoPlane";
                    break;
                case AirplaneType::PrivateJet: typeStr = "PrivateJet";
                    break;
            }
            std::println("{}. {} [{}] - {}",
                         idx++, flight->getFlightId(), typeStr, flight->getDestination());
        }
    }
    if (idx == 1) {
        std::println("  (no pending flights)");
    }
    return {};
}
