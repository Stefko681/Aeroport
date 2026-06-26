#include "RetrieveFromHangarCommand.h"
#include <print>
#include "core/Engine.h"
#include "facilities/Hangar.h"

RetrieveFromHangarCommand::RetrieveFromHangarCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole RetrieveFromHangarCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> RetrieveFromHangarCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: retrieve-from-hangar [aircraft_id]");
    int aircraftId;
    try {
        aircraftId = std::stoi(args[1]);
    } catch (...) {
        return std::unexpected("[Error] Invalid aircraft ID.");
    }
    auto plane = engine.findAirplaneGlobal(aircraftId);
    if (!plane) return std::unexpected("[Error] Aircraft not found.");
    auto hangar = engine.findHangarOf(plane);
    if (!hangar) return std::unexpected("[Error] Aircraft is not in a hangar.");
    std::string hangarId = hangar->getHangarId();
    hangar->release(plane);
    plane->restoreAirplaneHealth();
    std::println("[Success] Aircraft ID: {} retrieved from Hangar {}. Health restored to {:.0f}%.",
                 plane->getAirplaneId(), hangarId, plane->getAirplaneHealth());
    return {};
}
