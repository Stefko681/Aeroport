#include "ListFleetCommand.h"
#include "core/Engine.h"
#include "operations/Airline.h"

ListFleetCommand::ListFleetCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole ListFleetCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> ListFleetCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: list-fleet [airline]");
    const auto airline = engine.findAirline(args[1]);
    if (!airline) return std::unexpected("[Error] Airline not found.");
    airline->printFleet();
    return {};
}
