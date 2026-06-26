#include "AssignRunwayCommand.h"
#include "core/Engine.h"
#include "airplanes/Airplane.h"
#include <print>

AssignRunwayCommand::AssignRunwayCommand(Engine &engine) : DispatcherCommand(engine) {
}

namespace {
    std::string explainLandingFailure(const Airplane &plane, const Runway &runway) {
        std::string reasons;
        auto addReason = [&](const std::string &r) {
            if (!reasons.empty()) reasons += ". ";
            reasons += r;
        };
        switch (plane.getAirplaneType()) {
            case AirplaneType::CargoPlane: {
                if (runway.getRunwayLength() < 3000.0)
                    addReason(std::format("Length {:.0f}m < 3000m", runway.getRunwayLength()));
                if (!runway.hasHeavyDuty())
                    addReason("Missing HeavyDuty flag");
                break;
            }
            case AirplaneType::PassengerPlane: {
                if (runway.getRunwayLength() < 2000.0)
                    addReason(std::format("Length {:.0f}m < 2000m", runway.getRunwayLength()));
                break;
            }
            case AirplaneType::PrivateJet: {
                if (runway.getRunwayLength() < 1000.0)
                    addReason(std::format("Length {:.0f}m < 1000m", runway.getRunwayLength()));
                if (!runway.hasVIPTerminal())
                    addReason("Missing VIP Terminal");
                break;
            }
        }
        return reasons;
    }
}

std::expected<void, std::string> AssignRunwayCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 3) return std::unexpected("Usage: assign-runway [flight_id] [runway_id]");
    flight = engine.findFlightGlobal(args[1]);
    if (!flight) return std::unexpected("[Error] Flight '" + args[1] + "' not found.");
    runway = engine.findRunway(args[2]);
    if (!runway) return std::unexpected("[Error] Runway '" + args[2] + "' not found.");
    if (runway->getRunwayStatus() == RunwayStatus::Maintenance)
        return std::unexpected("[Error] Runway " + runway->getRunwayId() + " is under Maintenance.");
    if (runway->getRunwayStatus() == RunwayStatus::Occupied)
        return std::unexpected("[Error] Runway " + runway->getRunwayId() + " is currently Occupied by another aircraft!");
    const auto airplane = flight->getAirplane();
    if (!airplane) return std::unexpected("[Error] No airplane attached to flight.");
    if (!airplane->canLand(*runway)) {
        std::string reason = explainLandingFailure(*airplane, *runway);
        return std::unexpected(std::format("Runway {} does not meet aircraft requirements! ({}).", runway->getRunwayId(), reason));
    }
    prevFlightStatus = flight->getFlightStatus();
    if (prevFlightStatus != FlightStatus::Scheduled && prevFlightStatus != FlightStatus::Delayed)
        return std::unexpected("[Error] Flight is not awaiting a runway.");
    runway->assign(flight->getAirplane());
    flight->setFlightStatus(FlightStatus::Boarding);
    if (runway->hasVIPTerminal()) {
        std::println("[Success] Flight {} assigned to {} (VIP Terminal). Status -> Boarding.",flight->getFlightId(), runway->getRunwayId());
    } else {
        std::println("[Success] Flight {} assigned to {}. Status -> Boarding. Runway {} -> Occupied.",flight->getFlightId(), runway->getRunwayId(), runway->getRunwayId());
    }
    return {};
}

void AssignRunwayCommand::undo() {
    if (runway) runway->free();
    if (flight) flight->setFlightStatus(prevFlightStatus);
}

std::string AssignRunwayCommand::description() const {
    if (!flight || !runway) return "assign-runway (failed)";
    return "assign-runway " + flight->getFlightId() + " " + runway->getRunwayId();
}
