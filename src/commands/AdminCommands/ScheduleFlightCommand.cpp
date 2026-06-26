#include "ScheduleFlightCommand.h"

#include <print>
#include "core/Engine.h"
#include "operations/Airline.h"
#include "airplanes/Airplane.h"

namespace {
    std::string shortTypeLabel(const AirplaneType t) {
        switch (t) {
            case AirplaneType::PassengerPlane: return "Passenger";
            case AirplaneType::CargoPlane: return "Cargo";
            case AirplaneType::PrivateJet: return "Private";
        }
        return "Unknown";
    }
}

ScheduleFlightCommand::ScheduleFlightCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole ScheduleFlightCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> ScheduleFlightCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 5)
        return std::unexpected("Usage: schedule-flight [flight_id] [aircraft_id] [destination] [base_price]");
    int aircraftId{0};
    double basePrice{0.0};
    try {
        aircraftId = std::stoi(args[2]);
        basePrice = std::stod(args[4]);
    } catch (...) {
        return std::unexpected("[Error] Invalid aircraft ID or base price.");
    }
    const auto plane = engine.findAirplaneGlobal(aircraftId);
    if (!plane) return std::unexpected("[Error] Aircraft not found.");
    const auto airline = engine.findAirlineOfAircraft(plane);
    if (!airline) return std::unexpected("[Error] Airline not found.");
    auto result = airline->scheduleFlight(args[1], aircraftId, args[3], basePrice);
    if (!result) return std::unexpected(result.error());
    std::println("[System] {} Flight {} to {} is now Scheduled.",
                 shortTypeLabel(plane->getAirplaneType()), args[1], args[3]);
    return {};
}