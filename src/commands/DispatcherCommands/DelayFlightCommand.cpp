#include "DelayFlightCommand.h"
#include "core/Engine.h"
#include <print>

DelayFlightCommand::DelayFlightCommand(Engine &engine) : DispatcherCommand(engine) {
}

std::expected<void, std::string> DelayFlightCommand::execute(const std::vector<std::string> &args) {
    if (args.size() < 2) return std::unexpected("Usage: delay-flight [flight_id] [\"reason\"]");
    flight = engine.findFlightGlobal(args[1]);
    if (!flight) return std::unexpected("[Error] Flight '" + args[1] + "' not found.");
    reason.clear();
    for (size_t i = 2; i < args.size(); ++i) {
        if (!reason.empty()) reason += ' ';
        reason += args[i];
    }
    prevStatus = flight->getFlightStatus();
    if (prevStatus == FlightStatus::Departed || prevStatus == FlightStatus::Cancelled)
        return std::unexpected("[Error] Flight is already Departed/Cancelled.");
    if (prevStatus == FlightStatus::Delayed)return std::unexpected("[Error] Flight is already Delayed.");
    flight->setFlightStatus(FlightStatus::Delayed);
    std::println("[System] Flight {} status changed to Delayed. Notification dispatched to passengers.",flight->getFlightId());
    return {};
}

void DelayFlightCommand::undo() {
    if (flight) {
        flight->setFlightStatus(prevStatus);
        std::println("[System] Flight {} delay reverted.", flight->getFlightId());
    }
}

std::string DelayFlightCommand::description() const {
    if (!flight) return "delay-flight (failed)";
    return "delay-flight " + flight->getFlightId();
}
